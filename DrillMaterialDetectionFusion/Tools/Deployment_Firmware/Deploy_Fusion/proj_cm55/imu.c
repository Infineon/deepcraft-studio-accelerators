/******************************************************************************
* File Name:   imu.c
*
* Description: This file implements the interface with the BMI270 motion sensor.
*              The configurations of the motion sensor are specified in the
*              config.h file.
*
* Related Document: See README.md
*
*
********************************************************************************
* (c) 2024-2025, Infineon Technologies AG, or an affiliate of Infineon
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
*******************************************************************************/
#include "cybsp.h"
#include "mtb_bmi270.h"
#include "bmi2.h"

#include "config.h"
#include "imu.h"

extern uint32_t _imu_count, _imu_overflow;

/*******************************************************************************
* External variables
*******************************************************************************/
float _imu_p_buffer[IMU_P_BUFF_SIZE][IMU_P_DATA_SIZE];
uint16_t _imu_p_buffer_IndexI = 0;
uint16_t _imu_p_buffer_IndexO = 0;

/*******************************************************************************
* Macros
*******************************************************************************/
#if IMU_SAMPLE_RANGE == BMI2_ACC_RANGE_2G
#define IMU_ACC_DIVIDE     0x4000
#elif IMU_SAMPLE_RANGE == BMI2_ACC_RANGE_4G
#define IMU_ACC_DIVIDE     0x2000
#elif IMU_SAMPLE_RANGE == BMI2_ACC_RANGE_8G
#define IMU_ACC_DIVIDE     0x1000
#elif IMU_SAMPLE_RANGE == BMI2_ACC_RANGE_16G
#define IMU_ACC_DIVIDE     0x800
#endif /* IMU_SAMPLE_RANGE */

#if IMU_GYRO_SAMPLE_RANGE == BMI2_GYR_RANGE_125
#define IMU_GYRO_DIVIDE    262.0f
#elif IMU_GYRO_SAMPLE_RANGE == BMI2_GYR_RANGE_250
#define IMU_GYRO_DIVIDE    131.0f
#elif IMU_GYRO_SAMPLE_RANGE == BMI2_GYR_RANGE_500
#define IMU_GYRO_DIVIDE    65.5f
#elif IMU_GYRO_SAMPLE_RANGE == BMI2_GYR_RANGE_1000
#define IMU_GYRO_DIVIDE    32.8f
#elif IMU_GYRO_SAMPLE_RANGE == BMI2_GYR_RANGE_2000
#define IMU_GYRO_DIVIDE    16.4f
#endif /* IMU_GYRO_SAMPLE_RANGE */

#if defined(IMU_ACC) && defined(IMU_GYR)
#define IMU_NUM_AXIS                (6U)
#else
#define IMU_NUM_AXIS                (3U)
#endif /* IMU_ACC && IMU_GYR */
#define IMU_INTERRUPT_PRIORITY      (2U)
#define IMU_INTR_MASK               (0x00000001UL << CYBSP_IMU_INT1_PORT_NUM)
#define MASKED_TRUE                 (1U)

/* Number of frames to skip before sending data for processing. */
#define NUM_IMU_FRAMES_TO_SKIP      (0U)

#define ACC_INDEX                     (0U)
#define GYRO_INDEX                    (1U)
#define IMU_NUM_SENSORS             (2U)


/*******************************************************************************
* Global Variables
*******************************************************************************/
static mtb_hal_i2c_t CYBSP_I2C_CONTROLLER_0_hal_obj;
static cy_stc_scb_i2c_context_t CYBSP_I2C_CONTROLLER_0_context;

/* Instance of BMI270 sensor structure */
mtb_bmi270_t bmi270;
/* Number of bytes of FIFO data */
static uint8_t fifo_data[BMI2_FIFO_RAW_DATA_BUFFER_SIZE] = { 0 };

#ifdef IMU_ACC 
/* Array of accelerometer frames */
static struct bmi2_sens_axes_data fifo_accel_data[BMI2_FIFO_ACCEL_FRAME_COUNT] = { { 0 } };
#endif /* IMU_ACC */

#ifdef IMU_GYR 
/* Array of gyroscope frames */
static struct bmi2_sens_axes_data fifo_gyro_data[BMI2_FIFO_GYRO_FRAME_COUNT] = { { 0 } };
#endif /* IMU_GYR */

/* Initialize FIFO frame structure. */
struct bmi2_fifo_frame fifoframe = { 0 };

/* Flag to check if the data from IMU is ready for processing. */
static volatile bool imu_flag;

/* Number of frames to skip before sending data for processing. */
static uint8_t imu_skip_frames = NUM_IMU_FRAMES_TO_SKIP;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
static void imu_interrupt_handler(void);
static cy_rslt_t imu_fifo_init(void);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
/*******************************************************************************
* Function Name: imu_init
********************************************************************************
* Summary:
*  A function used to initialize the IMU (BMI270). Starts a timer that
*  triggers an interrupt at at the sample rate specified in config.h.
*
* Parameters:
*  None
*
* Return:
*  The status of the initialization.
*
*******************************************************************************/
cy_rslt_t imu_init(void)
{
    cy_rslt_t result;

    /* Initialize the I2C master interface for BMI270 motion sensor */
    result = Cy_SCB_I2C_Init(CYBSP_I2C_CONTROLLER_HW,
                             &CYBSP_I2C_CONTROLLER_config,
                             &CYBSP_I2C_CONTROLLER_0_context);

    if(CY_RSLT_SUCCESS != result)
    {
        printf(" Error : I2C initialization failed !!\r\n");
        CY_ASSERT(0);
    }

    Cy_SCB_I2C_Enable(CYBSP_I2C_CONTROLLER_HW);

    /* Configure the I2C master interface with the desired clock frequency */
    result = mtb_hal_i2c_setup(&CYBSP_I2C_CONTROLLER_0_hal_obj,
                               &CYBSP_I2C_CONTROLLER_hal_config,
                               &CYBSP_I2C_CONTROLLER_0_context,
                              NULL);

    if(CY_RSLT_SUCCESS != result)
    {
        printf(" Error : I2C setup failed !!\r\n");
        CY_ASSERT(0);
    }

    /* Initialize the BMI270 motion sensor */
    result = mtb_bmi270_init_i2c(&bmi270, &CYBSP_I2C_CONTROLLER_0_hal_obj, MTB_BMI270_ADDRESS_DEFAULT);
    if(CY_RSLT_SUCCESS != result)
    {
        printf(" Error : IMU sensor init failed !!\r\n");
        CY_ASSERT(0);
    }

    result = mtb_bmi270_config_default(&bmi270);
    if(CY_RSLT_SUCCESS != result)
    {
        printf(" Error : IMU sensor config failed !!\r\n");
        CY_ASSERT(0);
    }

    struct bmi2_sens_config acc_cfg = {0};
    acc_cfg.type = BMI2_ACCEL;
    bmi2_get_sensor_config(&acc_cfg, 1, &bmi270.sensor);
    acc_cfg.cfg.acc.odr = IMU_SAMPLE_RATE;
    acc_cfg.cfg.acc.range = IMU_SAMPLE_RANGE;
    acc_cfg.cfg.acc.bwp = BMI2_ACC_OSR4_AVG1;
    acc_cfg.cfg.acc.filter_perf = BMI2_PERF_OPT_MODE;
    result = bmi2_set_sensor_config(&acc_cfg, 1, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to set sensor config\n");
        CY_ASSERT(0);
    }

    /* Configure gyroscope if enabled */
    struct bmi2_sens_config gyr_cfg = {0};
    gyr_cfg.type = BMI2_GYRO;
    bmi2_get_sensor_config(&gyr_cfg, 1, &bmi270.sensor);
    gyr_cfg.cfg.gyr.odr = IMU_GYRO_SAMPLE_RATE;
    gyr_cfg.cfg.gyr.range = IMU_GYRO_SAMPLE_RANGE;
    gyr_cfg.cfg.gyr.bwp = BMI2_GYR_NORMAL_MODE;
    gyr_cfg.cfg.gyr.noise_perf = BMI2_POWER_OPT_MODE;
    gyr_cfg.cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
    result = bmi2_set_sensor_config(&gyr_cfg, 1, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to set sensor config\n");
        CY_ASSERT(0);
    }

    result = imu_fifo_init();
    if (BMI2_OK != result)
    {
        CY_ASSERT(0);
    }

    imu_flag = false;

    /* Initialize IMU FIFO Index */
	_imu_p_buffer_IndexI = 0;
	_imu_p_buffer_IndexO = 0;

    return result;
}

/*******************************************************************************
* Function Name: imu_fifo_init
********************************************************************************
* Summary:
*  A function used to initialize the FIFO related configurations for the
*  BMI270 IMU.
*
* Parameters:
*  None
*
* Return:
*  The status of the initialization.
*
*******************************************************************************/
static cy_rslt_t imu_fifo_init(void)
{
    cy_rslt_t result;

    /* Accel and gyro sensor are listed in array. */
    uint8_t sensor_sel[] =
    { 
        BMI2_ACCEL, 
        BMI2_GYRO,
    };


    /* Interrupt config structure for IMU interrupt */
    static cy_stc_sysint_t intrCfg =
    {
        CYBSP_IMU_INT1_IRQ,       /* Interrupt source */
        IMU_INTERRUPT_PRIORITY    /* Interrupt priority */
    };

    /* Interrupt pin configuration */
    static struct bmi2_int_pin_config pin_config = { 0 };


    /* Sensors must be enabled after setting configurations */
    result = bmi270_sensor_enable(sensor_sel, (sizeof(sensor_sel) /
                                  sizeof(sensor_sel[0])), &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to enable sensor\n");
        return result;
    }

    /* Before setting FIFO, disable the advance power save mode. */
    result = bmi2_set_adv_power_save(BMI2_DISABLE, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to disable advance power save mode\n");
        return result;
    }

    /* Initially disable all configurations in fifo. */
    result = bmi2_set_fifo_config(BMI2_FIFO_ALL_EN, BMI2_DISABLE, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to disable all FIFO configurations\n");
        return result;
    }

    /* Mapping the buffer to store the fifo data. */
    fifoframe.data = fifo_data;

    /* Length of FIFO frame. */
    fifoframe.length = BMI2_FIFO_RAW_DATA_BUFFER_SIZE;

    /* Set FIFO configuration by enabling accelerometer */
    result = bmi2_set_fifo_config(BMI2_FIFO_ACC_EN, BMI2_ENABLE, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to enable FIFO configuration\n");
        return result;
    }

    /* Set FIFO configuration by enabling gyroscope */
    result = bmi2_set_fifo_config(BMI2_FIFO_GYR_EN, BMI2_ENABLE, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to enable FIFO configuration\n");
        return result;
    }

    /* To enable headerless mode, disable the header. */
    result = bmi2_set_fifo_config(BMI2_FIFO_HEADER_EN, BMI2_DISABLE, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to disable FIFO header\n");
        return result;
    }

    /* Interrupt pin configuration */
    pin_config.pin_type = BMI2_INT1;
    pin_config.pin_cfg[0].input_en = BMI2_INT_INPUT_DISABLE;
    pin_config.pin_cfg[0].output_en = BMI2_INT_OUTPUT_ENABLE;
    pin_config.pin_cfg[0].lvl = BMI2_INT_ACTIVE_LOW;
    pin_config.pin_cfg[0].od = BMI2_INT_PUSH_PULL;
    pin_config.int_latch = BMI2_INT_NON_LATCH;

    /* Set Hardware interrupt pin configuration */
    result = bmi2_set_int_pin_config(&pin_config, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to set interrupt pin configuration\n");
        return result;
    }

    /* FIFO water-mark interrupt is enabled. */
    fifoframe.data_int_map = BMI2_FWM_INT;

    /* Map water-mark interrupt to the required interrupt pin. */
    result = bmi2_map_data_int(fifoframe.data_int_map, BMI2_INT1, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to map data interrupt\n");
        return result;
    }

    /* Flush the FIFO before setting the watermark level. */
    result = bmi2_set_command_register(BMI2_FIFO_FLUSH_CMD, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to flush FIFO\n");
        return result;
    }

    /* Set the watermark level. */
    fifoframe.wm_lvl = BMI2_FIFO_WATERMARK_LEVEL;
    fifoframe.length = BMI2_FIFO_RAW_DATA_BUFFER_SIZE;

    /* Set the water-mark level if water-mark interrupt is mapped. */
    result = bmi2_set_fifo_wm(fifoframe.wm_lvl, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to set FIFO watermark level\n");
        return result;
    }

    /* Clear GPIO and NVIC interrupt before initializing to avoid false
     * triggering.
     */
    Cy_GPIO_ClearInterrupt(CYBSP_IMU_INT1_PORT, CYBSP_IMU_INT1_PIN);
    NVIC_ClearPendingIRQ(CYBSP_IMU_INT1_IRQ);

    /* Initialize the interrupt and register interrupt callback */
    Cy_SysInt_Init(&intrCfg, &imu_interrupt_handler);

    /* Enable the interrupt in the NVIC */
    NVIC_EnableIRQ(intrCfg.intrSrc);

    return result;
}


/*******************************************************************************
* Function Name: imu_interrupt_handler
********************************************************************************
* Summary:
*  Handler for the IMU interrupt. Sets the flag for the processing in the main
*  loop.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void imu_interrupt_handler(void)
{
static int led = 0;
    /* Get interrupt cause */
    uint32_t intrSrc = Cy_GPIO_GetInterruptCause0();

    /* Check if the interrupt was from the user button's port and pin */
    if((IMU_INTR_MASK == (intrSrc & IMU_INTR_MASK)) &&
       (MASKED_TRUE == Cy_GPIO_GetInterruptStatusMasked(CYBSP_IMU_INT1_PORT,
               CYBSP_IMU_INT1_PIN)))
    {
        /* Clear the interrupt */
        Cy_GPIO_ClearInterrupt(CYBSP_IMU_INT1_PORT, CYBSP_IMU_INT1_PIN);
        NVIC_ClearPendingIRQ(CYBSP_IMU_INT1_IRQ);

        /* The flag is set to true, meaning data is ready to be processed */
        imu_flag = true;
    }
	Cy_GPIO_Write(CYBSP_USER_LED1_PORT, CYBSP_USER_LED1_PIN, led );
	led ^= 0x01;
}


/*******************************************************************************
* Function Name: imu_data_process
********************************************************************************
* Summary:
*  This function checks for the IMU interrupt status, reads the FIFO data from
*  the IMU, feeds the data to the DEEPCRAFT pre-processor, and prints the
*  processed results.
*
* Parameters:
*  None
*
* Return:
*  CY_RSLT_SUCCESS if successful, otherwise an error code indicating failure.
*******************************************************************************/

cy_rslt_t imu_data_process(void)
{
    /* Variables required to get the IMU data and process the results. */
    cy_rslt_t result = CY_RSLT_SUCCESS;

    uint16_t fifo_length = 0;
    uint16_t accel_frame_length;
    uint16_t gyro_frame_length;
    uint16_t int_status = 0;
    uint16_t watermark = 0;
    uint16_t index = 0;
    float imu_buffer[IMU_NUM_SENSORS][3];

    /* Check if IMU Data is ready to be processed */
    if (!imu_flag)
    {
        result = IMU_DATA_NOT_READY;
        return result;
    }

    /* Reset the flag to false, indicating that the data is being processed */
    imu_flag = false;

    /* Read FIFO data on interrupt. */
    result = bmi2_get_int_status(&int_status, &bmi270.sensor);
    if (BMI2_OK != result)
    {
        printf(" Error: Failed to get interrupt status\n");
        return result;
    }

    /* To check the status of FIFO watermark interrupt. */
    if (int_status & BMI2_FWM_INT_STATUS_MASK)
    {
        /* Turn user led on.*/
//        Cy_GPIO_Write(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, CYBSP_LED_STATE_ON);

        result = bmi2_get_fifo_wm(&watermark, &bmi270.sensor);
        if (BMI2_OK != result)
        {
            printf(" Error: Failed to get FIFO watermark level\n");
            return result;
        }
        
        result = bmi2_get_fifo_length(&fifo_length, &bmi270.sensor);
        if (BMI2_OK != result)
        {
            printf(" Error: Failed to get FIFO length\n");
            return result;
        }

        /* Updating FIFO length to be read based on available length and dummy byte updation */
        fifoframe.length = fifo_length + bmi270.sensor.dummy_byte;

        /* Read FIFO data. */
        result = bmi2_read_fifo_data(&fifoframe, &bmi270.sensor);
        if (BMI2_OK != result)
        {
            printf(" Error: Failed to read FIFO data\n");
            return result;
        }

        /* Read FIFO data on interrupt. */
        result = bmi2_get_int_status(&int_status, &bmi270.sensor);
        if (BMI2_OK != result)
        {
            printf(" Error: Failed to get interrupt status\n");
            return result;
        }

        /* Skip frames if needed */
        if (imu_skip_frames > 0)
        {
            imu_skip_frames--;
            Cy_GPIO_Write(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, CYBSP_LED_STATE_OFF);
            return result;
        }

        /* Parse the FIFO data to extract accelerometer data from the FIFO buffer. */
        accel_frame_length = BMI2_FIFO_ACCEL_FRAME_COUNT;
        (void)bmi2_extract_accel(fifo_accel_data, &accel_frame_length, &fifoframe, &bmi270.sensor);
        if (BMI2_FIFO_ACCEL_FRAME_COUNT != accel_frame_length)
        {
            printf("Error: Expected number of Accelerometer frames not received %d\n",accel_frame_length);
            result = IMU_FIFO_INSUFFICIENT_DATA;
            return result;
        }
        /* Parse FIFO data to extract gyroscope data from the FIFO buffer. */
        gyro_frame_length = BMI2_FIFO_GYRO_FRAME_COUNT;
        (void)bmi2_extract_gyro(fifo_gyro_data, &gyro_frame_length, &fifoframe, &bmi270.sensor);
        if (BMI2_FIFO_GYRO_FRAME_COUNT != gyro_frame_length)
        {
            printf("Error: Expected number of Gyroscope frames not received %d\r\n",gyro_frame_length);
            result = IMU_FIFO_INSUFFICIENT_DATA;
            return result;
        }

		for (index = 0; index < accel_frame_length; index++){
			imu_buffer[ACC_INDEX][0]  = fifo_accel_data[index].x / (float)IMU_ACC_DIVIDE;
			imu_buffer[ACC_INDEX][1]  = fifo_accel_data[index].y / (float)IMU_ACC_DIVIDE;
			imu_buffer[ACC_INDEX][2]  = fifo_accel_data[index].z / (float)IMU_ACC_DIVIDE;
			imu_buffer[GYRO_INDEX][0] = fifo_gyro_data[index].x / (float)IMU_GYRO_DIVIDE;
			imu_buffer[GYRO_INDEX][1] = fifo_gyro_data[index].y / (float)IMU_GYRO_DIVIDE;
			imu_buffer[GYRO_INDEX][2] = fifo_gyro_data[index].z / (float)IMU_GYRO_DIVIDE;

			if((( _imu_p_buffer_IndexI - _imu_p_buffer_IndexO ) & (IMU_P_BUFF_SIZE - 1)) == (IMU_P_BUFF_SIZE - 1)){
				_imu_overflow++;
				break;
			}
			IMU_P_compute( &imu_buffer[0][0], &_imu_p_buffer[_imu_p_buffer_IndexI][0] );
			_imu_p_buffer_IndexI = (_imu_p_buffer_IndexI + 1) & (IMU_P_BUFF_SIZE - 1);
			_imu_count++;
		}

    }

    return result;
}


/* [] END OF FILE */
