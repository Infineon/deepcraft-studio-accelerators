#pragma IMAGINET_INCLUDES_BEGIN
#include <stdint.h>
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "int16_to_float32"

static inline void int16_to_float32(const int16_t* restrict input, int16_t count, float* restrict output)
{	
	for (int i = 0; i < count; i++) {
		output[i] = (float)input[i];
	}
}

#pragma IMAGINET_FRAGMENT_END