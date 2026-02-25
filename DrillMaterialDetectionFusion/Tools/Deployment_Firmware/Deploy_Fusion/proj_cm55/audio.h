/******************************************************************************
* File Name:   audio.h
*
* Description: This file contains the function prototypes and constants used
*   in audio.c.
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

#ifndef AUDIO_H_
#define AUDIO_H_

#include "cy_result.h"
#include "stdbool.h"
#include "MICPrep.h"

/******************************************************************************
 * Constants
 *****************************************************************************/
/* Define how many samples in an audio frame */
#define FRAME_SIZE                  (1<<10)

/* Error type for data processing code when PDM PCM data is not available. */
#define PDM_PCM_DATA_NOT_READY      (-1L)

#define PDM_P_BUFF_SIZE             (1<<7)
#define PDM_P_DATA_SIZE             (40)


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
cy_rslt_t pdm_init(void);
cy_rslt_t pdm_data_process(void);

/*******************************************************************************
* External variables
*******************************************************************************/
extern float _pdm_p_buffer[PDM_P_BUFF_SIZE][PDM_P_DATA_SIZE];
extern uint16_t _pdm_p_buffer_IndexI;
extern uint16_t _pdm_p_buffer_IndexO;

#endif /* AUDIO_H_ */
