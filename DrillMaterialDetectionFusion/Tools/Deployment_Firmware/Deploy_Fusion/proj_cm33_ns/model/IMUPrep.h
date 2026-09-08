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

#include <stdbool.h>
#include <stdint.h>
#define IMU_P_API_FUNCTION

typedef int8_t q7_t;         // 8-bit fractional data type in Q1.7 format.
typedef int16_t q15_t;       // 16-bit fractional data type in Q1.15 format.
typedef int32_t q31_t;       // 32-bit fractional data type in Q1.31 format.
typedef int64_t q63_t;       // 64-bit fractional data type in Q1.63 format.

// Model GUID (16 bytes)
#define IMU_P_MODEL_ID {0x60, 0x93, 0x86, 0xcd, 0x3d, 0x62, 0x14, 0x47, 0x86, 0x17, 0xc4, 0x80, 0xee, 0x39, 0x73, 0x09}


// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_Q7	(0x31)
#define IMAGINET_TYPES_Q15	(0x32)
#define IMAGINET_TYPES_Q31	(0x34)
#define IMAGINET_TYPES_BOOL	(0x41)
#define IMAGINET_TYPES_STRING	(0x54)
#define IMAGINET_TYPES_D8	(0x61)
#define IMAGINET_TYPES_D16	(0x62)
#define IMAGINET_TYPES_D32	(0x64)
#define IMAGINET_TYPES_UINT8	(0x71)
#define IMAGINET_TYPES_UINT16	(0x72)
#define IMAGINET_TYPES_UINT32	(0x74)
#define IMAGINET_TYPES_UINT64	(0x78)

// datain [2,3] (24 bytes)
#define IMU_P_DATAIN_RANK (2)
#define IMU_P_DATAIN_SHAPE (((int[]){3, 2})
#define IMU_P_DATAIN_COUNT (6)
#define IMU_P_DATAIN_TYPE float
#define IMU_P_DATAIN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMU_P_DATAIN_SHIFT 0
#define IMU_P_DATAIN_OFFSET 0
#define IMU_P_DATAIN_SCALE 1
#define IMU_P_DATAIN_SYMBOLS {"X", "Y", "Z"}

// dataout [6] (24 bytes)
#define IMU_P_DATAOUT_RANK (1)
#define IMU_P_DATAOUT_SHAPE (((int[]){6})
#define IMU_P_DATAOUT_COUNT (6)
#define IMU_P_DATAOUT_TYPE float
#define IMU_P_DATAOUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMU_P_DATAOUT_SHIFT 0
#define IMU_P_DATAOUT_OFFSET 0
#define IMU_P_DATAOUT_SCALE 1
#define IMU_P_DATAOUT_SYMBOLS { }

#define IMU_P_KEY_MAX (2)

// Return codes
#define IMU_P_RET_SUCCESS 0
#define IMU_P_RET_NODATA -1
#define IMU_P_RET_ERROR -2
#define IMU_P_RET_STREAMEND -3

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

// Exported methods
void IMU_P_compute(const float *restrict datain, float *restrict dataout);
void IMU_P_finalize(void);
void IMU_P_init(void);

// Profiling regions
#define IMU_P_REGIONS_COUNT 0
#define IMU_P_REGIONS_NAMES {}
typedef enum {IMU_P_REGIONS_EMPTY} IMU_P_Region_t;

#ifdef IMU_P_REFLECTION

typedef enum {
    IMU_P_PARAM_UNDEFINED = 0,
    IMU_P_PARAM_INPUT = 1,
    IMU_P_PARAM_OUTPUT = 2,
    IMU_P_PARAM_REFERENCE = 3,
    IMU_P_PARAM_HANDLE = 7,
} IMU_P_param_attrib;

typedef char *label_text_t;

typedef struct {
    char* name;
    int size;
    label_text_t *labels;
} IMU_P_shape_dim;

typedef struct {
    char* name;
    IMU_P_param_attrib attrib;
    int32_t rank;
    IMU_P_shape_dim *shape;
    int32_t count;
    int32_t type_id;
    float frequency;
    int shift;
    float scale;
    long offset;
} IMU_P_param_def;

typedef enum {
    IMU_P_FUNC_ATTRIB_NONE = 0,
    IMU_P_FUNC_ATTRIB_CAN_FAIL = 1,
    IMU_P_FUNC_ATTRIB_PUBLIC = 2,
    IMU_P_FUNC_ATTRIB_INIT = 4,
    IMU_P_FUNC_ATTRIB_DESTRUCTOR = 8,
} IMU_P_func_attrib;

typedef struct {
    char* name;
    char* description;
    void* fn_ptr;
    IMU_P_func_attrib attrib;
    int32_t param_count;
    IMU_P_param_def *param_list;
} IMU_P_func_def;

typedef struct {
    uint32_t size;
    uint32_t peak_usage;
} IMU_P_mem_usage;

typedef enum {
    IMU_P_API_TYPE_UNDEFINED = 0,
    IMU_P_API_TYPE_FUNCTION = 1,
    IMU_P_API_TYPE_QUEUE = 2,
    IMU_P_API_TYPE_QUEUE_TIME = 3,
    IMU_P_API_TYPE_USER_DEFINED = 4,
} IMU_P_api_type;

typedef struct {
    uint32_t api_ver;
    uint8_t id[16];
    IMU_P_api_type api_type;
    char* prefix;
    IMU_P_mem_usage buffer_mem;
    IMU_P_mem_usage static_mem;
    IMU_P_mem_usage readonly_mem;
    int32_t func_count;
    IMU_P_func_def *func_list;
} IMU_P_api_def;

IMU_P_api_def *IMU_P_api(void);
#endif /* IMU_P_REFLECTION */

