/******************************************************************************
* File Name:   config.h
*
* Description: This file contains the configuration for running the IMU based
*              model.
*
* Related Document: See README.md
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
#ifndef CONFIG_H
#define CONFIG_H

#include "bmi2_defs.h"
/******************************************************************************
 * Constants
 *****************************************************************************/

#ifdef IMU_ACC
/* Set IMU_SAMPLE_RATE to one of the following
 * BMI2_ACC_ODR_400HZ
 * BMI2_ACC_ODR_200HZ
 * BMI2_ACC_ODR_100HZ
 * BMI2_ACC_ODR_50HZ */
#define IMU_SAMPLE_RATE BMI2_ACC_ODR_100HZ
//#define IMU_SAMPLE_RATE BMI2_ACC_ODR_200HZ

/* Set IMU_SAMPLE_RANGE to one of the following
 * BMI2_ACC_RANGE_16G
 * BMI2_ACC_RANGE_8G
 * BMI2_ACC_RANGE_4G
 * BMI2_ACC_RANGE_2G */
#define IMU_SAMPLE_RANGE BMI2_ACC_RANGE_2G

/* Accelerometer Frame Count for each interrupt
 *  Calculation:
 *    IMU Sample Rate =  100 Hz
 *    Desired IMU interrupt interval = 100 ms = 0.1 sec
 *    Accelerometer Frame Count = (0.1 sec * 100 Hz) = 10 frames
 */
#define BMI2_FIFO_ACCEL_FRAME_COUNT     UINT8_C(10)

#endif /* IMU_ACC */

#ifdef IMU_GYR
/* Gyroscope sample rate and range */

/* Set IMU_GYRO_SAMPLE_RATE to one of the following
 * BMI2_GYR_ODR_200HZ
 * BMI2_GYR_ODR_100HZ
 * BMI2_GYR_ODR_50HZ
 * BMI2_GYR_ODR_25HZ */
#define IMU_GYRO_SAMPLE_RATE   BMI2_GYR_ODR_100HZ
//#define IMU_GYRO_SAMPLE_RATE   BMI2_GYR_ODR_200HZ

/* Set IMU_GYRO_SAMPLE_RATE to one of the following
 * BMI2_GYR_RANGE_2000
 * BMI2_GYR_RANGE_1000
 * BMI2_GYR_RANGE_500
 * BMI2_GYR_RANGE_250
 * BMI2_GYR_RANGE_125 */
#define IMU_GYRO_SAMPLE_RANGE  BMI2_GYR_RANGE_500

/* Gyroscope Frame Count for each interrupt
 *  Calculation:
 *    IMU Sample Rate =  100 Hz
 *    Desired IMU interrupt interval = 100 ms = 0.1 sec
 *    Gyroscope Frame Count = (0.1 sec * 100 Hz) = 10 frames
 */
#define BMI2_FIFO_GYRO_FRAME_COUNT     UINT8_C(10)
#endif /* IMU_GYR */

#if defined(IMU_ACC) && defined(IMU_GYR)
/* Buffer size allocated to store raw FIFO data */
#define BMI2_FIFO_RAW_DATA_BUFFER_SIZE  UINT16_C(600)


/* Watermark level for the IMU HW FIFO
 *  Calculation:
 *    Accelerometer Frame Count = 10 frames
 *    Gyroscope Frame Count = 10 frames
 *    Length of 1 Accelerometer Frame = (3 * 2 bytes) = 6 bytes
 *    Length of 1 Gyroscope Frame = (3 * 2 bytes) = 6 bytes
 *    FIFO Watermark Level = (10 frames * (6 bytes + 6 bytes) ) = 120 bytes
 */
#define BMI2_FIFO_WATERMARK_LEVEL       UINT16_C(120)

#else 

/* Buffer size allocated to store raw FIFO data */
#define BMI2_FIFO_RAW_DATA_BUFFER_SIZE  UINT16_C(100)


/* Watermark level for the IMU HW FIFO
 *  Calculation:
 *    Sensor Frame Count = 10 frames
 *    Length of 1 Sensor Frame = (3 * 2 bytes) = 6 bytes
 *    FIFO Watermark Level = (10 frames * 6 bytes) = 60 bytes
 */
#define BMI2_FIFO_WATERMARK_LEVEL       UINT16_C(60)
#endif /* IMU_ACC and IMU_GYR */

#endif /* CONFIG_H */

/* [] END OF FILE */
