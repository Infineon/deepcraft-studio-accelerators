/*
* ImagiNet Compiler 5.6.3669+7d9ef301c112a741a83f89b4172d12e96546f4bc
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 11/15/2025 03:49:38 UTC. Any changes will be lost.
* 
* Model ID  9b6296f9-9412-4c37-a1ef-77dd78d9d698
* 
* Memory    Size                      Efficiency
* Buffers   14360 bytes (RAM)         86 %
* State     2304 bytes (RAM)          100 %
* Readonly  4032 bytes (Flash)        100 %
* 
* Exported functions:
* 
*  @description: Try read data from model.
*  @param dataout Output buffer. It will have the same shape as the input. Output float[40].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int MIC_P_dequeue(float *dataout);
* 
*  @description: Try write data to model.
*  @param datain Input features. Input float[1].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int MIC_P_enqueue(const float *datain);
* 
*  @description: Closes and flushes streams, free any heap allocated memory.
*  void MIC_P_finalize(void);
* 
*  @description: Initializes buffers to initial state.
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int MIC_P_init(void);
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
#define MIC_P_API_QUEUE

typedef int8_t q7_t;         // 8-bit fractional data type in Q1.7 format.
typedef int16_t q15_t;       // 16-bit fractional data type in Q1.15 format.
typedef int32_t q31_t;       // 32-bit fractional data type in Q1.31 format.
typedef int64_t q63_t;       // 64-bit fractional data type in Q1.63 format.

// Model GUID (16 bytes)
#define MIC_P_MODEL_ID {0xf9, 0x96, 0x62, 0x9b, 0x12, 0x94, 0x37, 0x4c, 0xa1, 0xef, 0x77, 0xdd, 0x78, 0xd9, 0xd6, 0x98}


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

// dataout [40] (160 bytes)
#define MIC_P_DATAOUT_RANK (1)
#define MIC_P_DATAOUT_SHAPE (((int[]){40})
#define MIC_P_DATAOUT_COUNT (40)
#define MIC_P_DATAOUT_TYPE float
#define MIC_P_DATAOUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define MIC_P_DATAOUT_SHIFT 3
#define MIC_P_DATAOUT_OFFSET 0
#define MIC_P_DATAOUT_SCALE 1
#define MIC_P_DATAOUT_SYMBOLS { }

// datain [1] (4 bytes)
#define MIC_P_DATAIN_RANK (1)
#define MIC_P_DATAIN_SHAPE (((int[]){1})
#define MIC_P_DATAIN_COUNT (1)
#define MIC_P_DATAIN_TYPE float
#define MIC_P_DATAIN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define MIC_P_DATAIN_SHIFT 0
#define MIC_P_DATAIN_OFFSET 0
#define MIC_P_DATAIN_SCALE 1
#define MIC_P_DATAIN_SYMBOLS {"Mono"}

#define MIC_P_KEY_MAX (23)

// Return codes
#define MIC_P_RET_SUCCESS 0
#define MIC_P_RET_NODATA -1
#define MIC_P_RET_ERROR -2
#define MIC_P_RET_STREAMEND -3

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

// Exported methods
int MIC_P_dequeue(float *restrict dataout);
int MIC_P_enqueue(const float *restrict datain);
void MIC_P_finalize(void);
int MIC_P_init(void);

// Profiling regions
#define MIC_P_REGIONS_COUNT 0
#define MIC_P_REGIONS_NAMES {}
typedef enum {MIC_P_REGIONS_EMPTY} MIC_P_Region_t;

#ifdef MIC_P_REFLECTION

typedef enum {
    MIC_P_PARAM_UNDEFINED = 0,
    MIC_P_PARAM_INPUT = 1,
    MIC_P_PARAM_OUTPUT = 2,
    MIC_P_PARAM_REFERENCE = 3,
    MIC_P_PARAM_HANDLE = 7,
} MIC_P_param_attrib;

typedef char *label_text_t;

typedef struct {
    char* name;
    int size;
    label_text_t *labels;
} MIC_P_shape_dim;

typedef struct {
    char* name;
    MIC_P_param_attrib attrib;
    int32_t rank;
    MIC_P_shape_dim *shape;
    int32_t count;
    int32_t type_id;
    float frequency;
    int shift;
    float scale;
    long offset;
} MIC_P_param_def;

typedef enum {
    MIC_P_FUNC_ATTRIB_NONE = 0,
    MIC_P_FUNC_ATTRIB_CAN_FAIL = 1,
    MIC_P_FUNC_ATTRIB_PUBLIC = 2,
    MIC_P_FUNC_ATTRIB_INIT = 4,
    MIC_P_FUNC_ATTRIB_DESTRUCTOR = 8,
} MIC_P_func_attrib;

typedef struct {
    char* name;
    char* description;
    void* fn_ptr;
    MIC_P_func_attrib attrib;
    int32_t param_count;
    MIC_P_param_def *param_list;
} MIC_P_func_def;

typedef struct {
    uint32_t size;
    uint32_t peak_usage;
} MIC_P_mem_usage;

typedef enum {
    MIC_P_API_TYPE_UNDEFINED = 0,
    MIC_P_API_TYPE_FUNCTION = 1,
    MIC_P_API_TYPE_QUEUE = 2,
    MIC_P_API_TYPE_QUEUE_TIME = 3,
    MIC_P_API_TYPE_USER_DEFINED = 4,
} MIC_P_api_type;

typedef struct {
    uint32_t api_ver;
    uint8_t id[16];
    MIC_P_api_type api_type;
    char* prefix;
    MIC_P_mem_usage buffer_mem;
    MIC_P_mem_usage static_mem;
    MIC_P_mem_usage readonly_mem;
    int32_t func_count;
    MIC_P_func_def *func_list;
} MIC_P_api_def;

MIC_P_api_def *MIC_P_api(void);
#endif /* MIC_P_REFLECTION */

