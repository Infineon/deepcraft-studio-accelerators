#pragma IMAGINET_FRAGMENT_BEGIN "addi_f32"
static inline void addi_f32(
	const float* restrict x,
	int count,
	float immediate,
	float* restrict output)
{
	for (int i = 0; i < count; i++) {
		output[i] = x[i] + immediate;
	}
}
#pragma IMAGINET_FRAGMENT_END
