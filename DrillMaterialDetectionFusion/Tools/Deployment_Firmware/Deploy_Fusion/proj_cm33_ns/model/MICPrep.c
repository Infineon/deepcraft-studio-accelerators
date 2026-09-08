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

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "arm_math.h"

#include "MICPrep.h"

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
static ALIGNED(16) int8_t _buffer[14360];
static ALIGNED(16) int8_t _state[2304];

// Parameters
static const uint32_t _K10[] = {
    0x3da3d70a, 0x3da3e945, 0x3da41ff6, 0x3da47b1a, 0x3da4faae, 0x3da59ead, 0x3da66711, 0x3da753d1, 
    0x3da864e6, 0x3da99a43, 0x3daaf3de, 0x3dac71a8, 0x3dae1393, 0x3dafd990, 0x3db1c38b, 0x3db3d173, 
    0x3db60333, 0x3db858b5, 0x3dbad1e2, 0x3dbd6ea1, 0x3dc02eda, 0x3dc3126f, 0x3dc61946, 0x3dc9433f, 
    0x3dcc903c, 0x3dd0001c, 0x3dd392bc, 0x3dd747fa, 0x3ddb1fb0, 0x3ddf19b9, 0x3de335ed, 0x3de77423, 
    0x3debd432, 0x3df055ed, 0x3df4f929, 0x3df9bdb7, 0x3dfea369, 0x3e01d506, 0x3e0468b9, 0x3e070cb2, 
    0x3e09c0d8, 0x3e0c8510, 0x3e0f593f, 0x3e123d48, 0x3e15310f, 0x3e183476, 0x3e1b4760, 0x3e1e69af, 
    0x3e219b42, 0x3e24dbfc, 0x3e282bba, 0x3e2b8a5d, 0x3e2ef7c4, 0x3e3273cb, 0x3e35fe51, 0x3e399733, 
    0x3e3d3e4d, 0x3e40f37b, 0x3e44b697, 0x3e48877d, 0x3e4c6608, 0x3e50520f, 0x3e544b6e, 0x3e5851fc, 
    0x3e5c6591, 0x3e608606, 0x3e64b330, 0x3e68ece8, 0x3e6d3302, 0x3e718555, 0x3e75e3b6, 0x3e7a4df9, 
    0x3e7ec3f3, 0x3e81a2bc, 0x3e83e92d, 0x3e863537, 0x3e8886c2, 0x3e8addb8, 0x3e8d3a02, 0x3e8f9b87, 
    0x3e920232, 0x3e946de9, 0x3e96de94, 0x3e99541c, 0x3e9bce69, 0x3e9e4d61, 0x3ea0d0ec, 0x3ea358f1, 
    0x3ea5e557, 0x3ea87604, 0x3eab0ae0, 0x3eada3d1, 0x3eb040bc, 0x3eb2e189, 0x3eb5861c, 0x3eb82e5d, 
    0x3ebada30, 0x3ebd897b, 0x3ec03c23, 0x3ec2f20e, 0x3ec5ab21, 0x3ec86741, 0x3ecb2653, 0x3ecde83b, 
    0x3ed0acdf, 0x3ed37422, 0x3ed63de9, 0x3ed90a1a, 0x3edbd897, 0x3edea945, 0x3ee17c09, 0x3ee450c6, 
    0x3ee72760, 0x3ee9ffbb, 0x3eecd9bb, 0x3eefb544, 0x3ef29239, 0x3ef5707e, 0x3ef84ff6, 0x3efb3086, 
    0x3efe1210, 0x3f007a3c, 0x3f01ebd1, 0x3f035db8, 0x3f04cfe4, 0x3f064245, 0x3f07b4ce, 0x3f09276f, 
    0x3f0a9a1c, 0x3f0c0cc5, 0x3f0d7f5c, 0x3f0ef1d3, 0x3f10641b, 0x3f11d626, 0x3f1347e6, 0x3f14b94c, 
    0x3f162a4a, 0x3f179ad3, 0x3f190ad7, 0x3f1a7a48, 0x3f1be918, 0x3f1d5739, 0x3f1ec49d, 0x3f203136, 
    0x3f219cf5, 0x3f2307cc, 0x3f2471ae, 0x3f25da8c, 0x3f274259, 0x3f28a906, 0x3f2a0e86, 0x3f2b72ca, 
    0x3f2cd5c6, 0x3f2e376a, 0x3f2f97ab, 0x3f30f679, 0x3f3253c7, 0x3f33af88, 0x3f3509af, 0x3f36622d, 
    0x3f37b8f7, 0x3f390dfd, 0x3f3a6134, 0x3f3bb28d, 0x3f3d01fd, 0x3f3e4f76, 0x3f3f9aea, 0x3f40e44e, 
    0x3f422b95, 0x3f4370b1, 0x3f44b397, 0x3f45f439, 0x3f47328c, 0x3f486e82, 0x3f49a811, 0x3f4adf2b, 
    0x3f4c13c5, 0x3f4d45d2, 0x3f4e7547, 0x3f4fa219, 0x3f50cc3a, 0x3f51f3a1, 0x3f531841, 0x3f543a0f, 
    0x3f555901, 0x3f56750a, 0x3f578e20, 0x3f58a437, 0x3f59b746, 0x3f5ac742, 0x3f5bd420, 0x3f5cddd5, 
    0x3f5de457, 0x3f5ee79d, 0x3f5fe79c, 0x3f60e44a, 0x3f61dd9d, 0x3f62d38c, 0x3f63c60e, 0x3f64b518, 
    0x3f65a0a2, 0x3f6688a3, 0x3f676d11, 0x3f684de4, 0x3f692b13, 0x3f6a0495, 0x3f6ada62, 0x3f6bac72, 
    0x3f6c7abd, 0x3f6d453a, 0x3f6e0be2, 0x3f6ecead, 0x3f6f8d94, 0x3f70488f, 0x3f70ff97, 0x3f71b2a4, 
    0x3f7261b1, 0x3f730cb6, 0x3f73b3ac, 0x3f74568d, 0x3f74f553, 0x3f758ff8, 0x3f762676, 0x3f76b8c6, 
    0x3f7746e3, 0x3f77d0c8, 0x3f78566f, 0x3f78d7d4, 0x3f7954f0, 0x3f79cdc0, 0x3f7a423f, 0x3f7ab267, 
    0x3f7b1e35, 0x3f7b85a5, 0x3f7be8b3, 0x3f7c475a, 0x3f7ca197, 0x3f7cf767, 0x3f7d48c6, 0x3f7d95b2, 
    0x3f7dde26, 0x3f7e2221, 0x3f7e619f, 0x3f7e9c9f, 0x3f7ed31e, 0x3f7f051a, 0x3f7f3290, 0x3f7f5b80, 
    0x3f7f7fe7, 0x3f7f9fc5, 0x3f7fbb17, 0x3f7fd1dd, 0x3f7fe416, 0x3f7ff1c2, 0x3f7ffadf, 0x3f7fff6e, 
    0x3f7fff6e, 0x3f7ffadf, 0x3f7ff1c2, 0x3f7fe416, 0x3f7fd1dd, 0x3f7fbb17, 0x3f7f9fc5, 0x3f7f7fe7, 
    0x3f7f5b80, 0x3f7f3290, 0x3f7f051a, 0x3f7ed31e, 0x3f7e9c9f, 0x3f7e619f, 0x3f7e2221, 0x3f7dde26, 
    0x3f7d95b2, 0x3f7d48c6, 0x3f7cf767, 0x3f7ca197, 0x3f7c475a, 0x3f7be8b3, 0x3f7b85a5, 0x3f7b1e35, 
    0x3f7ab267, 0x3f7a423f, 0x3f79cdc0, 0x3f7954f0, 0x3f78d7d4, 0x3f78566f, 0x3f77d0c8, 0x3f7746e3, 
    0x3f76b8c6, 0x3f762676, 0x3f758ff8, 0x3f74f553, 0x3f74568d, 0x3f73b3ac, 0x3f730cb6, 0x3f7261b1, 
    0x3f71b2a4, 0x3f70ff97, 0x3f70488f, 0x3f6f8d94, 0x3f6ecead, 0x3f6e0be2, 0x3f6d453a, 0x3f6c7abd, 
    0x3f6bac72, 0x3f6ada62, 0x3f6a0495, 0x3f692b13, 0x3f684de4, 0x3f676d11, 0x3f6688a3, 0x3f65a0a2, 
    0x3f64b518, 0x3f63c60e, 0x3f62d38c, 0x3f61dd9d, 0x3f60e44a, 0x3f5fe79c, 0x3f5ee79d, 0x3f5de457, 
    0x3f5cddd5, 0x3f5bd420, 0x3f5ac742, 0x3f59b746, 0x3f58a437, 0x3f578e20, 0x3f56750a, 0x3f555901, 
    0x3f543a0f, 0x3f531841, 0x3f51f3a1, 0x3f50cc3a, 0x3f4fa219, 0x3f4e7547, 0x3f4d45d2, 0x3f4c13c5, 
    0x3f4adf2b, 0x3f49a811, 0x3f486e82, 0x3f47328c, 0x3f45f439, 0x3f44b397, 0x3f4370b1, 0x3f422b95, 
    0x3f40e44e, 0x3f3f9aea, 0x3f3e4f76, 0x3f3d01fd, 0x3f3bb28d, 0x3f3a6134, 0x3f390dfd, 0x3f37b8f7, 
    0x3f36622d, 0x3f3509af, 0x3f33af88, 0x3f3253c7, 0x3f30f679, 0x3f2f97ab, 0x3f2e376a, 0x3f2cd5c6, 
    0x3f2b72ca, 0x3f2a0e86, 0x3f28a906, 0x3f274259, 0x3f25da8c, 0x3f2471ae, 0x3f2307cc, 0x3f219cf5, 
    0x3f203136, 0x3f1ec49d, 0x3f1d5739, 0x3f1be918, 0x3f1a7a48, 0x3f190ad7, 0x3f179ad3, 0x3f162a4a, 
    0x3f14b94c, 0x3f1347e6, 0x3f11d626, 0x3f10641b, 0x3f0ef1d3, 0x3f0d7f5c, 0x3f0c0cc5, 0x3f0a9a1c, 
    0x3f09276f, 0x3f07b4ce, 0x3f064245, 0x3f04cfe4, 0x3f035db8, 0x3f01ebd1, 0x3f007a3c, 0x3efe1210, 
    0x3efb3086, 0x3ef84ff6, 0x3ef5707e, 0x3ef29239, 0x3eefb544, 0x3eecd9bb, 0x3ee9ffbb, 0x3ee72760, 
    0x3ee450c6, 0x3ee17c09, 0x3edea945, 0x3edbd897, 0x3ed90a1a, 0x3ed63de9, 0x3ed37422, 0x3ed0acdf, 
    0x3ecde83b, 0x3ecb2653, 0x3ec86741, 0x3ec5ab21, 0x3ec2f20e, 0x3ec03c23, 0x3ebd897b, 0x3ebada30, 
    0x3eb82e5d, 0x3eb5861c, 0x3eb2e189, 0x3eb040bc, 0x3eada3d1, 0x3eab0ae0, 0x3ea87604, 0x3ea5e557, 
    0x3ea358f1, 0x3ea0d0ec, 0x3e9e4d61, 0x3e9bce69, 0x3e99541c, 0x3e96de94, 0x3e946de9, 0x3e920232, 
    0x3e8f9b87, 0x3e8d3a02, 0x3e8addb8, 0x3e8886c2, 0x3e863537, 0x3e83e92d, 0x3e81a2bc, 0x3e7ec3f3, 
    0x3e7a4df9, 0x3e75e3b6, 0x3e718555, 0x3e6d3302, 0x3e68ece8, 0x3e64b330, 0x3e608606, 0x3e5c6591, 
    0x3e5851fc, 0x3e544b6e, 0x3e50520f, 0x3e4c6608, 0x3e48877d, 0x3e44b697, 0x3e40f37b, 0x3e3d3e4d, 
    0x3e399733, 0x3e35fe51, 0x3e3273cb, 0x3e2ef7c4, 0x3e2b8a5d, 0x3e282bba, 0x3e24dbfc, 0x3e219b42, 
    0x3e1e69af, 0x3e1b4760, 0x3e183476, 0x3e15310f, 0x3e123d48, 0x3e0f593f, 0x3e0c8510, 0x3e09c0d8, 
    0x3e070cb2, 0x3e0468b9, 0x3e01d506, 0x3dfea369, 0x3df9bdb7, 0x3df4f929, 0x3df055ed, 0x3debd432, 
    0x3de77423, 0x3de335ed, 0x3ddf19b9, 0x3ddb1fb0, 0x3dd747fa, 0x3dd392bc, 0x3dd0001c, 0x3dcc903c, 
    0x3dc9433f, 0x3dc61946, 0x3dc3126f, 0x3dc02eda, 0x3dbd6ea1, 0x3dbad1e2, 0x3db858b5, 0x3db60333, 
    0x3db3d173, 0x3db1c38b, 0x3dafd990, 0x3dae1393, 0x3dac71a8, 0x3daaf3de, 0x3da99a43, 0x3da864e6, 
    0x3da753d1, 0x3da66711, 0x3da59ead, 0x3da4faae, 0x3da47b1a, 0x3da41ff6, 0x3da3e945, 0x3da3d70a
};

static const uint32_t _K15[] = {
    0x00220020, 0x00260024, 0x002c0029, 0x0031002e, 0x00370034, 0x003e003a, 0x00450041, 0x004c0048, 
    0x00540050, 0x005d0059, 0x00670062, 0x0071006c, 0x007d0077, 0x00890083, 0x0096008f, 0x00a4009d, 
    0x00b400ac, 0x00c500bc, 0x00d700ce, 0x00eb00e1, 0x010000f5
};

static const uint32_t _K16[] = {
    0x00000000, 0x3f000000, 0x3f800000, 0x3f000000, 0x00000000, 0x00000000, 0x3f000000, 0x3f800000, 
    0x3f000000, 0x00000000, 0x00000000, 0x3f000000, 0x3f800000, 0x3f2aaaaa, 0x3eaaaaaa, 0x00000000, 
    0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f2aaaaa, 0x3eaaaaaa, 0x00000000, 0x00000000, 
    0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f000000, 0x00000000, 0x00000000, 0x3f000000, 0x3f800000, 
    0x3f2aaaaa, 0x3eaaaaaa, 0x00000000, 0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f2aaaaa, 
    0x3eaaaaaa, 0x00000000, 0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f2aaaaa, 0x3eaaaaaa, 
    0x00000000, 0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f2aaaaa, 0x3eaaaaaa, 0x00000000, 
    0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f400000, 0x3f000000, 0x3e800000, 0x00000000, 
    0x00000000, 0x3e800000, 0x3f000000, 0x3f400000, 0x3f800000, 0x3f2aaaaa, 0x3eaaaaaa, 0x00000000, 
    0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f400000, 0x3f000000, 0x3e800000, 0x00000000, 
    0x00000000, 0x3e800000, 0x3f000000, 0x3f400000, 0x3f800000, 0x3f2aaaaa, 0x3eaaaaaa, 0x00000000, 
    0x00000000, 0x3eaaaaab, 0x3f2aaaab, 0x3f800000, 0x3f400000, 0x3f000000, 0x3e800000, 0x00000000, 
    0x00000000, 0x3e800000, 0x3f000000, 0x3f400000, 0x3f800000, 0x3f400000, 0x3f000000, 0x3e800000, 
    0x00000000, 0x00000000, 0x3e800000, 0x3f000000, 0x3f400000, 0x3f800000, 0x3f400000, 0x3f000000, 
    0x3e800000, 0x00000000, 0x00000000, 0x3e800000, 0x3f000000, 0x3f400000, 0x3f800000, 0x3f4ccccd, 
    0x3f19999a, 0x3ecccccc, 0x3e4ccccc, 0x00000000, 0x00000000, 0x3e4ccccd, 0x3ecccccd, 0x3f19999a, 
    0x3f4ccccd, 0x3f800000, 0x3f400000, 0x3f000000, 0x3e800000, 0x00000000, 0x00000000, 0x3e800000, 
    0x3f000000, 0x3f400000, 0x3f800000, 0x3f4ccccd, 0x3f19999a, 0x3ecccccc, 0x3e4ccccc, 0x00000000, 
    0x00000000, 0x3e4ccccd, 0x3ecccccd, 0x3f19999a, 0x3f4ccccd, 0x3f800000, 0x3f4ccccd, 0x3f19999a, 
    0x3ecccccc, 0x3e4ccccc, 0x00000000, 0x00000000, 0x3e4ccccd, 0x3ecccccd, 0x3f19999a, 0x3f4ccccd, 
    0x3f800000, 0x3f4ccccd, 0x3f19999a, 0x3ecccccc, 0x3e4ccccc, 0x00000000, 0x00000000, 0x3e4ccccd, 
    0x3ecccccd, 0x3f19999a, 0x3f4ccccd, 0x3f800000, 0x3f4ccccd, 0x3f19999a, 0x3ecccccc, 0x3e4ccccc, 
    0x00000000, 0x00000000, 0x3e4ccccd, 0x3ecccccd, 0x3f19999a, 0x3f4ccccd, 0x3f800000, 0x3f555555, 
    0x3f2aaaaa, 0x3f000000, 0x3eaaaaaa, 0x3e2aaaac, 0x00000000, 0x00000000, 0x3e2aaaab, 0x3eaaaaab, 
    0x3f000000, 0x3f2aaaab, 0x3f555555, 0x3f800000, 0x3f555555, 0x3f2aaaaa, 0x3f000000, 0x3eaaaaaa, 
    0x3e2aaaac, 0x00000000, 0x00000000, 0x3e2aaaab, 0x3eaaaaab, 0x3f000000, 0x3f2aaaab, 0x3f555555, 
    0x3f800000, 0x3f555555, 0x3f2aaaaa, 0x3f000000, 0x3eaaaaaa, 0x3e2aaaac, 0x00000000, 0x00000000, 
    0x3e2aaaab, 0x3eaaaaab, 0x3f000000, 0x3f2aaaab, 0x3f555555, 0x3f800000, 0x3f555555, 0x3f2aaaaa, 
    0x3f000000, 0x3eaaaaaa, 0x3e2aaaac, 0x00000000, 0x00000000, 0x3e2aaaab, 0x3eaaaaab, 0x3f000000, 
    0x3f2aaaab, 0x3f555555, 0x3f800000, 0x3f555555, 0x3f2aaaaa, 0x3f000000, 0x3eaaaaaa, 0x3e2aaaac, 
    0x00000000, 0x00000000, 0x3e2aaaab, 0x3eaaaaab, 0x3f000000, 0x3f2aaaab, 0x3f555555, 0x3f800000, 
    0x3f5b6db7, 0x3f36db6e, 0x3f124924, 0x3edb6db6, 0x3e924924, 0x3e124924, 0x00000000, 0x00000000, 
    0x3e124925, 0x3e924925, 0x3edb6db7, 0x3f124925, 0x3f36db6e, 0x3f5b6db7, 0x3f800000, 0x3f5b6db7, 
    0x3f36db6e, 0x3f124924, 0x3edb6db6, 0x3e924924, 0x3e124924, 0x00000000, 0x00000000, 0x3e124925, 
    0x3e924925, 0x3edb6db7, 0x3f124925, 0x3f36db6e, 0x3f5b6db7, 0x3f800000, 0x3f5b6db7, 0x3f36db6e, 
    0x3f124924, 0x3edb6db6, 0x3e924924, 0x3e124924, 0x00000000, 0x00000000, 0x3e124925, 0x3e924925, 
    0x3edb6db7, 0x3f124925, 0x3f36db6e, 0x3f5b6db7, 0x3f800000, 0x3f600000, 0x3f400000, 0x3f200000, 
    0x3f000000, 0x3ec00000, 0x3e800000, 0x3e000000, 0x00000000, 0x00000000, 0x3e000000, 0x3e800000, 
    0x3ec00000, 0x3f000000, 0x3f200000, 0x3f400000, 0x3f600000, 0x3f800000, 0x3f600000, 0x3f400000, 
    0x3f200000, 0x3f000000, 0x3ec00000, 0x3e800000, 0x3e000000, 0x00000000, 0x00000000, 0x3e000000, 
    0x3e800000, 0x3ec00000, 0x3f000000, 0x3f200000, 0x3f400000, 0x3f600000, 0x3f800000, 0x3f600000, 
    0x3f400000, 0x3f200000, 0x3f000000, 0x3ec00000, 0x3e800000, 0x3e000000, 0x00000000, 0x00000000, 
    0x3e000000, 0x3e800000, 0x3ec00000, 0x3f000000, 0x3f200000, 0x3f400000, 0x3f600000, 0x3f800000, 
    0x3f638e39, 0x3f471c72, 0x3f2aaaaa, 0x3f0e38e4, 0x3ee38e38, 0x3eaaaaaa, 0x3e638e38, 0x3de38e38, 
    0x00000000, 0x00000000, 0x3de38e39, 0x3e638e39, 0x3eaaaaab, 0x3ee38e39, 0x3f0e38e4, 0x3f2aaaab, 
    0x3f471c72, 0x3f638e39, 0x3f800000, 0x3f638e39, 0x3f471c72, 0x3f2aaaaa, 0x3f0e38e4, 0x3ee38e38, 
    0x3eaaaaaa, 0x3e638e38, 0x3de38e38, 0x00000000, 0x00000000, 0x3de38e39, 0x3e638e39, 0x3eaaaaab, 
    0x3ee38e39, 0x3f0e38e4, 0x3f2aaaab, 0x3f471c72, 0x3f638e39, 0x3f800000, 0x3f638e39, 0x3f471c72, 
    0x3f2aaaaa, 0x3f0e38e4, 0x3ee38e38, 0x3eaaaaaa, 0x3e638e38, 0x3de38e38, 0x00000000, 0x00000000, 
    0x3de38e39, 0x3e638e39, 0x3eaaaaab, 0x3ee38e39, 0x3f0e38e4, 0x3f2aaaab, 0x3f471c72, 0x3f638e39, 
    0x3f800000, 0x3f666666, 0x3f4ccccd, 0x3f333333, 0x3f19999a, 0x3f000000, 0x3ecccccc, 0x3e99999a, 
    0x3e4ccccc, 0x3dccccd0, 0x00000000, 0x00000000, 0x3dcccccd, 0x3e4ccccd, 0x3e99999a, 0x3ecccccd, 
    0x3f000000, 0x3f19999a, 0x3f333333, 0x3f4ccccd, 0x3f666666, 0x3f800000, 0x3f666666, 0x3f4ccccd, 
    0x3f333333, 0x3f19999a, 0x3f000000, 0x3ecccccc, 0x3e99999a, 0x3e4ccccc, 0x3dccccd0, 0x00000000, 
    0x00000000, 0x3dcccccd, 0x3e4ccccd, 0x3e99999a, 0x3ecccccd, 0x3f000000, 0x3f19999a, 0x3f333333, 
    0x3f4ccccd, 0x3f666666, 0x3f800000, 0x3f666666, 0x3f4ccccd, 0x3f333333, 0x3f19999a, 0x3f000000, 
    0x3ecccccc, 0x3e99999a, 0x3e4ccccc, 0x3dccccd0, 0x00000000, 0x00000000, 0x3dcccccd, 0x3e4ccccd, 
    0x3e99999a, 0x3ecccccd, 0x3f000000, 0x3f19999a, 0x3f333333, 0x3f4ccccd, 0x3f666666, 0x3f800000, 
    0x3f68ba2e, 0x3f51745d, 0x3f3a2e8c, 0x3f22e8ba, 0x3f0ba2e8, 0x3ee8ba2e, 0x3eba2e8c, 0x3e8ba2e8, 
    0x3e3a2e8c, 0x3dba2e88, 0x00000000
};

// Memory mapped buffers
#define _K10             ((float *)_K10)                     // f32[512] (2048 bytes)
#define _K15             ((int16_t *)_K15)                   // s16[42] (84 bytes)
#define _K16             ((float *)_K16)                     // f32[475] (1900 bytes)
#define _K2              ((int8_t *)(_state + 0x00000000))   // s8[2256] (2256 bytes)
#define _K5              ((int8_t *)(_state + 0x000008d0))   // s8[48] (48 bytes)
#define _K1              ((float *)(_buffer + 0x00000000))   // f32[512] (2048 bytes)
#define _K14             ((float *)(_buffer + 0x00000000))   // f32[257] (1028 bytes)
#define _K19             ((float *)(_buffer + 0x00000404))   // f32[40] (160 bytes)
#define _K20             ((float *)(_buffer + 0x00000000))   // f32[40] (160 bytes)
#define _K21             ((float *)(_buffer + 0x000000a0))   // f32[40] (160 bytes)
#define _K22             ((float *)(_buffer + 0x00000000))   // f32[40] (160 bytes)
#define _K3              ((float *)(_buffer + 0x00000800))   // f32[512] (2048 bytes)
#define _K4              ((float *)(_buffer + 0x00001000))   // f32[257,2] (2056 bytes)
#define _K8              ((float *)(_buffer + 0x00001808))   // f32[1026] (4104 bytes)
#define _K9              ((float *)(_buffer + 0x00002810))   // f32[1026] (4104 bytes)

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

// Represents a Circular Buffer
// https://en.wikipedia.org/wiki/Circular_buffer
typedef struct
{
	char *buf;
	int size;		// total bytes allocated in *buf
	int used;		// current bytes used in buffer.
	int read;
	int write;
} cbuffer_t;

#define CBUFFER_SUCCESS 0
#define CBUFFER_NOMEM -1

// Reset instance (clear buffer)
static inline void cbuffer_reset(cbuffer_t* buf) {
	buf->read = 0;
	buf->write = 0;
	buf->used = 0;
}

// Initializes a cbuffer handle with given memory and size.
static inline void cbuffer_init(cbuffer_t *dest, void *mem, int size) {
	dest->buf = mem;
	dest->size = size;
	cbuffer_reset(dest);
}

// Returns the number of free bytes in buffer.
static inline int cbuffer_get_free(cbuffer_t *buf) {
	return buf->size - buf->used;
}

// Returns the number of used bytes in buffer.
static inline int cbuffer_get_used(cbuffer_t *buf) {
	return buf->used;
}

// Writes given data to buffer.
// Returns CBUFFER_SUCCESS or CBUFFER_NOMEM if out of memory.
static inline int cbuffer_enqueue(cbuffer_t *buf, const void *data, int data_size) {
	int free = cbuffer_get_free(buf);

	// Out of memory?
	if (free < data_size)
		return CBUFFER_NOMEM;

	// Is the data split in the end?
	if (buf->write + data_size > buf->size) {
		int first_size = buf->size - buf->write;
		memcpy(buf->buf + buf->write, data, first_size);
		memcpy(buf->buf, ((char *)data) + first_size, data_size - first_size);
	}
	else {
		memcpy(buf->buf + buf->write, data, data_size);
	}
	buf->write += data_size;
	if (buf->write >= buf->size)
		buf->write -= buf->size;

	buf->used += data_size;
	return CBUFFER_SUCCESS;
}

// Advances the read pointer by given count.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data
static inline int cbuffer_advance(cbuffer_t *buf, int count) {
	int used = cbuffer_get_used(buf);

	if (count > used)
		return CBUFFER_NOMEM;

	buf->read += count;
	if (buf->read >= buf->size)
		buf->read -= buf->size;

	// Reset pointers to 0 if buffer is empty in order to avoid unwanted wrapps.
	if (buf->read == buf->write) {
		buf->read = 0;
		buf->write = 0;
	}

	buf->used -= count;
	return CBUFFER_SUCCESS;
}

// Returns a read pointer at given offset and  
// updates *can_read_bytes (if not NULL) with the number of bytes that can be read.
// 
// Note! Byte count written to can_read_bytes can be less than what cbuffer_get_used() returns.
// This happens when the read has to be split in two since it's a circular buffer.
static inline void* cbuffer_readptr(cbuffer_t* buf, int offset, int* can_read_bytes)
{
	int a0 = buf->read + offset;
	if (a0 >= buf->size)
		a0 -= buf->size;
	if (can_read_bytes != NULL)
	{
		int c0 = buf->used;
		if (a0 + c0 > buf->size)
			c0 = buf->size - a0;

		*can_read_bytes = c0;
	}
	return buf->buf + a0;
}

// Copies given "count" bytes to the "dst" buffer without advancing the buffer read offset.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data.
static inline int cbuffer_copyto(cbuffer_t *buf, void *dst, int count, int offset) {
	
	if (count > cbuffer_get_used(buf))
		return CBUFFER_NOMEM;

	int can_read_bytes;
	void* src_ptr = cbuffer_readptr(buf, offset, &can_read_bytes);

	int c0 = (count < can_read_bytes) ? count : can_read_bytes;
	memcpy(dst, src_ptr, c0);
	
	int c1 = count - c0;

	if (c1 > 0)
		memcpy(((char *)dst) + c0, buf->buf, c1);

	return CBUFFER_SUCCESS;
}

typedef struct {
	cbuffer_t data_buffer;			// Circular Buffer for features
	int input_size;					// Number of bytes in each input chunk
} fixwin_t;

#ifdef _MSC_VER
static_assert(sizeof(fixwin_t) <= 64, "Data structure 'fixwin_t' is too big");
#endif

/*
* Try to dequeue a window.
*
* @param handle Pointer to an initialized handle.
* @param dst Pointer where to write window.
* @param stride_count Number of items (of size handle->input_size) to stride window.
* @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1) is no data is available.
*/
static inline int fixwin_dequeue(void* restrict handle, void* restrict dst, int count, int stride_count)
{
	fixwin_t* fep = (fixwin_t*)handle;

	const int stride_bytes = stride_count * fep->input_size;
	const int size = count * fep->input_size;
	if (cbuffer_get_used(&fep->data_buffer) >= size) {
		if (cbuffer_copyto(&fep->data_buffer, dst, size, 0) != 0)
			return IPWIN_RET_ERROR;

		if (cbuffer_advance(&fep->data_buffer, stride_bytes) != 0)
			return IPWIN_RET_ERROR;

		return IPWIN_RET_SUCCESS;
	}
	return IPWIN_RET_NODATA;
}

static inline void hammingmul_cmsis_f32(const float* restrict a, const float* restrict b, float* restrict result, int d1, int d2)
{
	for (int j = 0; j < d2; j++) {
		arm_mult_f32(a, b, result, d1);
		a += d1;
		result += d1;
	}
}

#define print_error(...) do{ fprintf( stderr, __VA_ARGS__ ); fprintf(stderr, "\n\r"); } while(0)

static_assert (sizeof(arm_rfft_fast_instance_f32) <= 48, "Data structure 'arm_rfft_fast_instance_f32' is too big");

// input array (any shape >= 1D)
// output array (shape = input.shape.replace(axis, n).insert(0,2))
// d0 = input.shape.step(axis)
// d1 = input.shape.size(axis)
// d2 = input.shape.slot(axis)
static inline void rfft_cmsis_f32(
    void* handle,
    const float* restrict input,
    float* restrict output,
    int d0, int d1, int d2, float* restrict temp_a, float* restrict temp_b)
{
    int step = d0 * 2;
    int a0 = d0 * d1;
    int a1 = a0 + step;

    for (int k = 0; k < d2; k++)
    {
        int m0 = k * a0;
        int m1 = k * a1;
        for (int i = 0; i < d0; i++)
        {
            int as = m0 + i;
            for (int j = 0; j < d1; j++)
            {
                temp_a[j] = input[as];
                as += d0;
            }

            arm_rfft_fast_f32((arm_rfft_fast_instance_f32*)handle, temp_a, temp_b, 0);
         
            int index =  i * 2 + m1;
            output[index] = temp_b[0];
            output[index + 1] = 0;
            index += step;
            for (int j = 2; j < d1; j += 2)
            {
                output[index] = temp_b[j];
                output[index + 1] = temp_b[j + 1];
                index += step;
            }
            output[index] = temp_b[1];
            output[index + 1] = 0;
        }
    }
}

static inline void norm_cmsis_cmplx_f32(const float* restrict input, int d2, float* restrict output)
{
	arm_cmplx_mag_f32(input, output, d2);
}

// input array (any shape >= 1D)
// output array (same shape as input array except with 0 replaced with num_filter)
// size = input.shape.size(0)
// slot = input.shape.slot(0)
static inline void mel_cmsis_f32(
	const float* restrict input,
	const short* restrict filter_points,
	const float* restrict filter_coefs,
	int size,
	int slot, 
	int num_filter, 
	float* restrict output)
{	
	for (int k = 0; k < slot; k++) {
		const float *ip = input + k * size;
		const float* coefs = filter_coefs;
		for (int i = 0; i < num_filter; i++) {
			
			short n0 = filter_points[i];
			short n2 = filter_points[i + 2];
			short len = n2 - n0 + 1;
			arm_dot_prod_f32(ip + n0, coefs, len, output++);
			coefs += len;
		}
	}
}

static inline void addi_cmsis_f32(
	const float* restrict x,
	int count,
	float immediate,
	float* restrict output)
{
	arm_offset_f32(x, immediate, output, count);
}

static inline void log_cmsis_f32(const float* restrict x, int count, float scale, float* restrict result)
{
	arm_vlog_f32(x, result, count);
	arm_scale_f32(result, scale, result, count);
}

static inline void clip_cmsis_f32(const float* restrict input, int count, float min, float max, float* restrict output)
{
	arm_clip_f32(input, output, min, max, count);
}

static inline void scale_f32(
	const float* restrict x,
	int count,
	float scale,
	float* restrict output)
{
	for (int i = 0; i < count; i++) {
		output[i] = x[i] * scale;
	}
}

/**
 * Enqueue handle->input_size values from given *data pointer to internal window buffer.
 *
 * @param handle Pointer to an initialized handle.
 * @param data Data to enqueue.
 * @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_ERROR (-2) if internal buffer is out of memory.
 */
static inline int fixwin_enqueue(void* restrict handle, const void* restrict data)
{
	fixwin_t* fep = (fixwin_t*)handle;

	if (cbuffer_enqueue(&fep->data_buffer, data, fep->input_size) != 0)
		return IPWIN_RET_ERROR;

	return IPWIN_RET_SUCCESS;
}

/**
* Initializes a fixwin sampler handle.
*
* @param handle Pointer to a preallocated memory area of fixwin_handle_size() bytes to initialize.
*
* @param input_size Number of bytes to enqueue.
* @param count Number of items (of size input_size) in each window
*/
static inline void fixwin_init(void* restrict handle, int input_size, int count)
{
	fixwin_t* fep = (fixwin_t*)handle;
	fep->input_size = input_size;

	char* mem = ((char*)handle) + sizeof(fixwin_t);

	int data_buffer = input_size * count;
	
	cbuffer_init(&fep->data_buffer, mem, data_buffer);
}

static inline int rfft_cmsis_init_512_f32(void* handle)
{
    if (arm_rfft_fast_init_512_f32((arm_rfft_fast_instance_f32*)handle) != ARM_MATH_SUCCESS) {
        print_error("[FAILED] arm_rfft_fast_init_512_f32");
        return -2;
    }
    return 0;
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
* Try read data from model.
* 
*  @param dataout Output buffer. It will have the same shape as the input. Output float[40].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int MIC_P_dequeue(float *restrict dataout) {    
    __RETURN_ERROR(fixwin_dequeue(_K2, _K1, 512, 160));
    hammingmul_cmsis_f32(_K1, _K10, _K3, 512, 1);
    rfft_cmsis_f32(_K5, _K3, _K4, 1, 512, 1, _K8, _K9);
    norm_cmsis_cmplx_f32(_K4, 257, _K14);
    mel_cmsis_f32(_K14, _K15, _K16, 257, 1, 40, _K19);
    addi_cmsis_f32(_K19, 40, 1, _K20);
    log_cmsis_f32(_K20, 40, 1, _K21);
    clip_cmsis_f32(_K21, 40, 0, 4, _K22);
    scale_f32(_K22, 40, 20, dataout);
    return 0;
}

/*
* Try write data to model.
* 
*  @param datain Input features. Input float[1].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int MIC_P_enqueue(const float *restrict datain) {    
    __RETURN_ERROR(fixwin_enqueue(_K2, datain));
    return 0;
}

/*
* Closes and flushes streams, free any heap allocated memory.
* 
*/
void MIC_P_finalize(void) {    
}

/*
* Initializes buffers to initial state.
* 
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int MIC_P_init(void) {    
    fixwin_init(_K2, 4, 512);
    __RETURN_ERROR(rfft_cmsis_init_512_f32(_K5));
    return 0;
}

#ifdef MIC_P_REFLECTION

static MIC_P_api_def _MIC_P_api_def = {
    api_ver: 1,
    id: {0xf9, 0x96, 0x62, 0x9b, 0x12, 0x94, 0x37, 0x4c, 0xa1, 0xef, 0x77, 0xdd, 0x78, 0xd9, 0xd6, 0x98},
    api_type: MIC_P_API_TYPE_QUEUE,
    prefix: "MIC_P_",
    buffer_mem: {
        size: 14360,
        peak_usage: 12312,
    },
    static_mem: {
        size: 2304,
        peak_usage: 2304,
    },
    readonly_mem: {
        size: 4032,
        peak_usage: 4032,
    },
    func_count: 4,
    func_list: (MIC_P_func_def[]) {
        {
            name: "MIC_P_dequeue",
            description: "Try read data from model.",
            fn_ptr: MIC_P_dequeue,
            attrib: 3,
            param_count: 1,
            param_list: (MIC_P_param_def[]) {
                {
                    name: "dataout",
                    attrib: MIC_P_PARAM_OUTPUT,
                    rank: 1,
                    shape: (MIC_P_shape_dim[]) {
                        {
                            name: "",
                            size: 40,
                        },
                    },
                    count: 40,
                    type_id: IMAGINET_TYPES_FLOAT32,
                    frequency: 100,
                    shift: 3,
                    scale: 1,
                    offset: 0,
                },
            },
        },
        {
            name: "MIC_P_enqueue",
            description: "Try write data to model.",
            fn_ptr: MIC_P_enqueue,
            attrib: 3,
            param_count: 1,
            param_list: (MIC_P_param_def[]) {
                {
                    name: "datain",
                    attrib: MIC_P_PARAM_INPUT,
                    rank: 1,
                    shape: (MIC_P_shape_dim[]) {
                        {
                            name: "Channel",
                            size: 1,
                            labels: (label_text_t[]) { "Mono" },
                        },
                    },
                    count: 1,
                    type_id: IMAGINET_TYPES_FLOAT32,
                    frequency: 16000,
                    shift: 0,
                    scale: 1,
                    offset: 0,
                },
            },
        },
        {
            name: "MIC_P_finalize",
            description: "Closes and flushes streams, free any heap allocated memory.",
            fn_ptr: MIC_P_finalize,
            attrib: 10,
            param_count: 0,
            param_list: (MIC_P_param_def[]) {
            },
        },
        {
            name: "MIC_P_init",
            description: "Initializes buffers to initial state.",
            fn_ptr: MIC_P_init,
            attrib: 7,
            param_count: 0,
            param_list: (MIC_P_param_def[]) {
            },
        },
    },
};

MIC_P_api_def *MIC_P_api(void) {
    return &_MIC_P_api_def;
}

#endif /* MIC_P_REFLECTION */

