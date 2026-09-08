/*****************************************************************************
* File Name        : main.c
*
* Description      : This is the source code for DEEPCRAFT Deploy Audio Example.
*
* Related Document : See README.md
*
******************************************************************************
* (c) 2025, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
* 
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*****************************************************************************/

/*******************************************************************************
* Header File
*******************************************************************************/

#include "cybsp.h"

#ifdef ML_DEEPCRAFT_CM55
#include "stdlib.h"
#include "retarget_io_init.h"

#include "audio.h"
#include "imu.h"
#include "model.h"

#include "mtb_bmi270.h"
#include "bmi2.h"

#define OUTPUT_THRESHOLD_SCORE                  (0.6f)

// Define it for output to QtGraph(Python Script); comment out the definition for console(TeraTerm etc.) output.
//#define OUTPUT_QtGraph

/*******************************************************************************
* Global Variable Definitions
*******************************************************************************/
float _model_input_data[PDM_P_DATA_SIZE+IMU_P_DATA_SIZE];
uint32_t _pdm_count,_imu_count,_imai_count,_pdm_overflow,_imu_overflow;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
static cy_rslt_t system_init(void);
static void cm55_ml_deepcraft_task(void);

#endif /* ML_DEEPCRAFT_CM55 */

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  This is the main function. It initializes the system on the CM55 CPU.
*  If the model inferencing is set to CM55 + U55, it starts the Deploy Audio
*  application, else, it enters Deepsleep mode.
*
* Parameters:
*  None
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

#ifdef ML_DEEPCRAFT_CM55
    /* If ML_DEEPCRAFT_CPU is set as CM55, start the task */
    cm55_ml_deepcraft_task();
#else

    for (;;)
    {
        /* If ML_DEEPCRAFT_CPU is set as CM33, put the CM55 to sleep */
        Cy_SysPm_CpuEnterDeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
#endif /* ML_DEEPCRAFT_CM55 */
}

#ifdef ML_DEEPCRAFT_CM55
/*******************************************************************************
* Function Name: system_init
********************************************************************************
* Summary:
*  Initializes the neural network based on the DEEPCRAFT model and the
*  DEEPCRAFT pre-processor and initializes the PDM PCM block.
*
* Parameters:
*  None
*
* Returns:
*  The status of the initialization.
*
*******************************************************************************/
static cy_rslt_t system_init(void)
{
    cy_rslt_t result;

	// ------------------------------------------------------------------------
	// IMU
	// ------------------------------------------------------------------------
    /* Initialize DEEPCRAFT pre-processing library */
	IMU_P_init();

    /* Initialize the IMU and related interrupt handling code */
    result = imu_init();
	if(result != BMI2_OK) return result;

	//Debug
	_pdm_count  = 0;
	_pdm_overflow = 0;

	// ------------------------------------------------------------------------
	// PDM(MIC)
	// ------------------------------------------------------------------------
    /* Initialize DEEPCRAFT pre-processing library */
	MIC_P_init();

    /* Configure PDM, PDM clocks, and PDM event */
    result = pdm_init();
	if(result != CY_PDM_PCM_SUCCESS) return result;

	//Debug
	_imu_count  = 0;
	_imu_overflow = 0;

	// ------------------------------------------------------------------------
	// Larning Model
	// ------------------------------------------------------------------------
    /* Initialize DEEPCRAFT pre-processing library */
    IMAI_init();

	//Debug
	_imai_count = 0;

    return result;
}


/*******************************************************************************
* Function Name: cm55_ml_deepcraft_task
********************************************************************************
* Summary:
*  Contains the main loop for the application. It sets up the UART for
*  logs and initialises the system (DEEPCRAFT pre-processor and PDM/PCM block
*  for audio input). It then invokes the PDM Data Processing function that
*  sends the data for pre-processing, inferencing, and prints in the results
*  when enough data is received.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
static void cm55_ml_deepcraft_task(void)
{
    cy_rslt_t result;
    int16_t best_label = 0;
    float max_score = 0.0f;
    float label_scores[IMAI_DATA_OUT_COUNT];
    char *label_text[] = IMAI_SYMBOL_MAP;
#ifdef OUTPUT_QtGraph
int interval = 0;
#endif


    /* Initialize retarget-io middleware */
    init_retarget_io();

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
//    printf("\x1b[2J\x1b[;H");

    /* Initialize inference engine and sensors */
    result = system_init();

    /* Initialization failed */
    if(CY_RSLT_SUCCESS != result)
    {
        /* Failed to initialize properly */
        printf("System initialization fail\r\n");
        while(1);
    }


	for (;;){
		imu_data_process();
		pdm_data_process();

		if((( _pdm_p_buffer_IndexI - _pdm_p_buffer_IndexO ) & (PDM_P_BUFF_SIZE - 1)) == 0) continue;
		if((( _imu_p_buffer_IndexI - _imu_p_buffer_IndexO ) & (IMU_P_BUFF_SIZE - 1)) == 0) continue;

		for (int n = 0; n < PDM_P_DATA_SIZE; n++){
			_model_input_data[n] = _pdm_p_buffer[_pdm_p_buffer_IndexO][n];
		}
		_pdm_p_buffer_IndexO = (_pdm_p_buffer_IndexO + 1) & (PDM_P_BUFF_SIZE - 1);

		for (int n = 0; n < IMU_P_DATA_SIZE; n++){
			_model_input_data[PDM_P_DATA_SIZE+n] = _imu_p_buffer[_imu_p_buffer_IndexO][n];
		}
		_imu_p_buffer_IndexO = (_imu_p_buffer_IndexO + 1) & (IMU_P_BUFF_SIZE - 1);

		result = IMAI_enqueue( &_model_input_data[0] );
		CY_ASSERT(IMAI_RET_SUCCESS == result);

		best_label = 0;
		max_score = -1000.0f;

		/* Check if there is any model output to process */
		switch(IMAI_dequeue(label_scores)){
		case IMAI_RET_SUCCESS:      /* We have data, display it */
#ifdef OUTPUT_QtGraph
			if(interval++ > 2){
				printf("DATA");

				for(int i = 0; i < IMAI_DATA_OUT_COUNT; i++){
					printf(",%s,%.4f", label_text[i], label_scores[i]);
				}
				printf("\r\n");
				interval = 0;
			}
#else	// OUTPUT_QtGraph

			/* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
			printf("\x1b[2J\x1b[;H");
			/* Move cursor home */
			printf("DEEPCRAFT Studio Deploy Fusion Example - CM55\r\n\n");

			for(int i = 0; i < IMAI_DATA_OUT_COUNT; i++){
				printf("label: %-11s: score: %.4f\r\n", label_text[i], label_scores[i]);
				if (label_scores[i] > max_score){
					max_score = label_scores[i];
					best_label = i;
				}
			}

			if(max_score >= OUTPUT_THRESHOLD_SCORE){
				printf("\n\nOutput: %-10s\r\n", label_text[best_label]);
			}else{
				printf("\n\nOutput: %-10s\r\n", "");
			}
#endif	// OUTPUT_QtGraph
			break;

		case IMAI_RET_NODATA:   /* No new output, continue with sampling */
			break;
		case IMAI_RET_NOMEM:    /* Abort on error */
			CY_ASSERT(0);
			break;
		}
	}
}
#endif /* ML_DEEPCRAFT_CM55 */

/* [] END OF FILE */
