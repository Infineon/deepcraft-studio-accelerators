/*
* ImagiNet Compiler 5.6.3669+7d9ef301c112a741a83f89b4172d12e96546f4bc
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 11/15/2025 03:48:54 UTC. Any changes will be lost.
* 
* Model ID  cd869360-623d-4714-8617-c480ee397309
* 
* Memory    Size                      Efficiency
* Buffers   24 bytes (RAM)            100 %
* 
* Exported functions:
* 
*  @param datain Input features. Input float[2,3].
*  @param dataout Output buffer. It will have the same shape as the input. Output float[6].
*  void IMU_P_compute(const float *datain, float *dataout);
* 
*  @description: Closes and flushes streams, free any heap allocated memory.
*  void IMU_P_finalize(void);
* 
*  @description: Initializes buffers to initial state.
*  void IMU_P_init(void);
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#include <stdint.h>
#include "arm_math.h"

#include "IMUPrep.h"

#ifdef __GNUC__
	#define ALIGNED(x) __attribute__((aligned(x)))
#else
	#define ALIGNED(x) __declspec(align(x))
#endif

#if defined(__GNUC__) || defined(__clang__)
	#define ATTRIB_WEAK  __attribute__((weak))
#else
	#define ATTRIB_WEAK 
#endif

// Working memory
static ALIGNED(16) int8_t _buffer[24];

// Memory mapped buffers
#define _K1              ((float *)(_buffer + 0x00000000))   // f32[6] (24 bytes)

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

static inline void clip_cmsis_f32(const float* restrict input, int count, float min, float max, float* restrict output)
{
	arm_clip_f32(input, output, min, max, count);
}

static inline void addi_cmsis_f32(
	const float* restrict x,
	int count,
	float immediate,
	float* restrict output)
{
	arm_offset_f32(x, immediate, output, count);
}

#ifndef __CLOSE_HOOKS
	#define __CLOSE_HOOKS() do { } while(0)
#endif
#define __RETURN_ERROR(_exp) do { int __ret = (_exp); if(__ret < 0) { __CLOSE_HOOKS(); return __ret; } } while(0)
#define __RETURN_ALWAYS(_exp) __CLOSE_HOOKS(); return (_exp)
#define __RETURN_ERROR_BREAK_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) break; if(__ret < 0) { __CLOSE_HOOKS(); return __ret; } }
#define __RETURN_ERROR_BREAK_EMPTY_END(_exp) {  int __ret = (_exp); if(__ret == -1 || __ret == -3) break; if(__ret < 0) { __CLOSE_HOOKS(); return __ret; } }
#define __RETURN_ERROR_CANCEL_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) { __CLOSE_HOOKS(); return 0; } if(__ret < 0) { __CLOSE_HOOKS(); return __ret; } }
#define __BREAK_ERROR(_exp) {  int __ret = (_exp); if(__ret < 0) break; }

/*
*  @param datain Input features. Input float[2,3].
*  @param dataout Output buffer. It will have the same shape as the input. Output float[6].
*/
void IMU_P_compute(const float *restrict datain, float *restrict dataout) {    
    clip_cmsis_f32(datain, 6, -40, 40, _K1);
    addi_cmsis_f32(_K1, 6, 40, dataout);
}

/*
* Closes and flushes streams, free any heap allocated memory.
* 
*/
void IMU_P_finalize(void) {    
}

/*
* Initializes buffers to initial state.
* 
*/
void IMU_P_init(void) {    
}

#ifdef IMU_P_REFLECTION

static IMU_P_api_def _IMU_P_api_def = {
    api_ver: 1,
    id: {0x60, 0x93, 0x86, 0xcd, 0x3d, 0x62, 0x14, 0x47, 0x86, 0x17, 0xc4, 0x80, 0xee, 0x39, 0x73, 0x09},
    api_type: IMU_P_API_TYPE_FUNCTION,
    prefix: "IMU_P_",
    buffer_mem: {
        size: 24,
        peak_usage: 24,
    },
    static_mem: {
        size: 0,
        peak_usage: 0,
    },
    readonly_mem: {
        size: 0,
        peak_usage: 0,
    },
    func_count: 3,
    func_list: (IMU_P_func_def[]) {
        {
            name: "IMU_P_compute",
            description: "",
            fn_ptr: IMU_P_compute,
            attrib: 2,
            param_count: 2,
            param_list: (IMU_P_param_def[]) {
                {
                    name: "datain",
                    attrib: IMU_P_PARAM_INPUT,
                    rank: 2,
                    shape: (IMU_P_shape_dim[]) {
                        {
                            name: "Axis",
                            size: 3,
                            labels: (label_text_t[]) { "X","Y","Z" },
                        },
                        {
                            name: "Sensor",
                            size: 2,
                            labels: (label_text_t[]) { "Accel","Gyro" },
                        },
                    },
                    count: 6,
                    type_id: IMAGINET_TYPES_FLOAT32,
                    frequency: 100,
                    shift: 0,
                    scale: 1,
                    offset: 0,
                },
                {
                    name: "dataout",
                    attrib: IMU_P_PARAM_OUTPUT,
                    rank: 1,
                    shape: (IMU_P_shape_dim[]) {
                        {
                            name: "",
                            size: 6,
                        },
                    },
                    count: 6,
                    type_id: IMAGINET_TYPES_FLOAT32,
                    frequency: 100,
                    shift: 0,
                    scale: 1,
                    offset: 0,
                },
            },
        },
        {
            name: "IMU_P_finalize",
            description: "Closes and flushes streams, free any heap allocated memory.",
            fn_ptr: IMU_P_finalize,
            attrib: 10,
            param_count: 0,
            param_list: (IMU_P_param_def[]) {
            },
        },
        {
            name: "IMU_P_init",
            description: "Initializes buffers to initial state.",
            fn_ptr: IMU_P_init,
            attrib: 6,
            param_count: 0,
            param_list: (IMU_P_param_def[]) {
            },
        },
    },
};

IMU_P_api_def *IMU_P_api(void) {
    return &_IMU_P_api_def;
}

#endif /* IMU_P_REFLECTION */

