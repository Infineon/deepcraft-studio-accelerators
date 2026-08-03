#pragma IMAGINET_INCLUDES_BEGIN
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "master"


#ifndef VEC3_H
#define VEC3_H
typedef struct Vec3 {
    float x, y, z;
} Vec3;

void __vMinus(Vec3* out, Vec3* a, Vec3* b)
{
	out->x = a->x - b->x;
	out->y = a->y - b->y;
	out->z = a->z - b->z;
}

float __vLen(const Vec3* in)
{    
    return sqrtf((in->x * in->x) + (in->y * in->y) + (in->z * in->z));
}

void __vClear(Vec3 *in)
{    
    in->x = in->y = in->z = 0.0f;
}

void __vScale(Vec3 *in, float scale)
{    
    in->x *= scale; 
   	in->y *= scale;
   	in->z *= scale;
}

void __vNorm(Vec3 *out, const Vec3 *in)
{    
	float len = (in->x * in->x) + (in->y * in->y) + (in->z * in->z);
	float d = 0.0f;

	if (len != 0.0f)
	{
		d = 1.0f / sqrtf(len);
	}

	out->x = in->x * d;
	out->y = in->y * d;
	out->z = in->z * d;
}

float __vDot(const Vec3 *a, const Vec3 *b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

void __vCross(Vec3 *out, const Vec3 *a, const Vec3 *b )
{    
    out->x = a->y * b->z - a->z * b->y;
    out->y = a->z * b->x - a->x * b->z;
    out->z = a->x * b->y - a->y * b->x;
}

void __vRotate(Vec3 *out, Vec3 *in, Vec3 *a, float rad)
{    
    float t = 1.0f - cosf(rad);
    float c = cosf(rad);
    float s = sinf(rad);

    float az = a->z;
    float ax = a->x;    
    float ay = a->y;
    
    float x = in->x;
    float y = in->y;
    float z = in->z;
        
    out->x = ((t * (ax*ax) + c) * x) + ((t * ax * ay + s * az) * y) + ((t * ax * az - s * ay) * z);
    out->y = ((t * ax * ay - s * az) * x) + ((t * (ay*ay) + c) * y) + ((t * ay * az + s * ax) * z);
    out->z = ((t * ax * az + s * ay) * x) + ((t * ay * az - s * ax) * y) + ((t * (az*az) + c) * z);  
}

void __vFilter(Vec3 *filterVec, Vec3 *vec, float rate)
{
	filterVec->x = ((1.0f - rate) * filterVec->x) + (rate * vec->x); // 0.95 and 0.05
	filterVec->y = ((1.0f - rate) * filterVec->y) + (rate * vec->y); // TODO: Defines for these.
	filterVec->z = ((1.0f - rate) * filterVec->z) + (rate * vec->z);
}
#endif

#ifndef CONSTANTS_H
#define CONSTANTS_H
typedef enum
{
    AXIS_X,
    AXIS_Y,
    AXIS_Z,
    NUM_AXES
} Axis_t;

typedef enum
{
    FEATURE_FORCE,
    FEATURE_DIMENSION,
    FEATURE_ROTATION_TOTAL,
    FEATURE_CROSSING,
    FEATURE_CHAOS,
    FEATURE_SAMPLING_X,
    FEATURE_SAMPLING_Y,
    FEATURE_SAMPLING_Z,
    NUM_FEATURES
} Features_t;

typedef struct
{
    float x[3];
    float y[3];
} SampleState;

/******** Definitions/Configurations for FeatureModel ********/

Vec3 RawAcc = {0.0f, 0.0f, 0.0f};
Vec3 prevRawAcc = {0.0f, 0.0f, 0.0f};
uint32_t LastAccelTime;
#define TRIGGER_TIMEOUT 1000
uint32_t TRIGGER_TIMES[NUM_FEATURES] = {0, 0, 0, 0, 0};
float TRIGGER_VALUE[NUM_FEATURES] = {0, 0, 0, 0, 0};
float NeuralBuffer[6] = {0, 0, 0, 0, 0, 0};
#define MAX_INT 100000


//***************************************
//		Force
//***************************************

float force_sum = 0.0f;
float prev_force = 0.0f;

/*
This determines how much the
lpf filter will filter (0-1) higher = more filtering
*/
#define FORCE_ALPHA 0.7f

//***************************************
//		Dimension
//***************************************

float dim_sum = 0.0f;
float prev_dim = 0.0f;

/*
This determines how much the
lpf filter will filter (0-1) higher = more filtering
*/
#define DIM_ALPHA 0.4f

//***************************************
//		Rotation
//***************************************

float prev_total_rotation = 0.0f;
int8_t rot_init[NUM_AXES];
Vec3 rot_previous[NUM_AXES];

/*
This determines how much the
lpf filter will filter (0-1) higher = more filtering
*/
#define TOTAL_ROTATION_ALPHA 0.95f

//***************************************
//		Crossing
//***************************************

/*
This determines how much the
lpf filter will filter (0-1) higher = more filtering
*/
#define CROSSING_ALPHA 0.75f

//***************************************
//		Chaos
//***************************************

#define KURT_N 39
#define KURT_N_P (KURT_N + 1)


//***************************************
//		Sampling
//***************************************

#define STILLNESS_THRESHOLD 0.5f
#define SECONDARY_STILLNESS_THRESHOLD 0.14f
#define AFTERFALL_TIMER 10000

#endif


void force_feature(const float *input, float *output)
{
    
    float total_force = __vLen(&RawAcc);

    total_force = FORCE_ALPHA * prev_force + ((1.0f - FORCE_ALPHA) * total_force);
    prev_force = total_force;

    TRIGGER_TIMES[FEATURE_FORCE] = LastAccelTime;
    TRIGGER_VALUE[FEATURE_FORCE] = total_force;
    
}


float GetDimension(Vec3 RawAcc, Vec3 prevRawAcc)
{
    Vec3 delta;
    __vMinus(&delta, &RawAcc, &prevRawAcc);
    return __vLen(&delta);
}

void dimension_feature(const float *input, float *output)
{
    static Vec3 prevRawAcc = {0.0f, 0.0f, 0.0f};

    float dimension = GetDimension(RawAcc, prevRawAcc);
    prevRawAcc = RawAcc;

    dimension = DIM_ALPHA * prev_dim + (1.0f - DIM_ALPHA) * dimension;
    prev_dim = dimension;

    TRIGGER_TIMES[FEATURE_DIMENSION] = LastAccelTime;
    TRIGGER_VALUE[FEATURE_DIMENSION] = dimension;

}

float GetRotationForAxis(Vec3 direction, int axis)
{
	switch (axis)
	{
	case AXIS_X:
		direction.x = 0.0f;
		break;
	case AXIS_Y:
		direction.y = 0.0f;
		break;
	case AXIS_Z:
		direction.z = 0.0f;
		break;
	default:
		break;
	}

	__vNorm(&direction, &direction); // Normalize for Dot

	// set first previous vector to direction -> first rotation always 0
	if (!rot_init[axis])
	{
		rot_init[axis] = 1;
		rot_previous[axis].x = direction.x;
		rot_previous[axis].y = direction.y;
		rot_previous[axis].z = direction.z;

		__vNorm(&rot_previous[axis], &rot_previous[axis]); // Normalize for Dot
	}

	float dot = __vDot(&direction, &rot_previous[axis]); // Alignment of the vectors, both need to be normalized

	if (dot >= 1.0f)
		dot = 0.9999999999f; /* acos(1) returns +0 and acos(x) returns NaN for abs(x) > 1 */

	if (dot < -1.0f)
		dot = -1.0f;

	rot_previous[axis] = direction;

	return acosf(dot); /* rotation */
}

void rotation_feature(const float *input, float *output)
{

	float total_rotationX = GetRotationForAxis(RawAcc, AXIS_X);
	float total_rotationY = GetRotationForAxis(RawAcc, AXIS_Y);
	float total_rotationZ = GetRotationForAxis(RawAcc, AXIS_Z);
	float total_rotation = total_rotationX + total_rotationY + total_rotationZ;

	total_rotation = TOTAL_ROTATION_ALPHA * prev_total_rotation + ((1.0f - TOTAL_ROTATION_ALPHA) * total_rotation);
	prev_total_rotation = total_rotation;

	TRIGGER_TIMES[FEATURE_ROTATION_TOTAL] = LastAccelTime;
	TRIGGER_VALUE[FEATURE_ROTATION_TOTAL] = total_rotation;
}


float num_crossings = 0;
float xprev, yprev, zprev;

float ZeroCrossing2(float current, float prev)
{
	if (prev < 0.0f && current > 0.0f)
	{
		return 1.0f * fabsf(prev - current); 
	}
	if (prev > 0.0f && current < 0.0f)
	{
		return 1.0f * fabsf(prev - current);
	}
	return 0;
}

float CalculateCrossings2(float x, float y, float z)
{

	x = CROSSING_ALPHA * xprev + ((1.0f - CROSSING_ALPHA) * x);
	y = CROSSING_ALPHA * yprev + ((1.0f - CROSSING_ALPHA) * y);
	z = CROSSING_ALPHA * zprev + ((1.0f - CROSSING_ALPHA) * z);

	float sum_cross = 0;
	sum_cross += ZeroCrossing2(x, xprev);
	sum_cross += ZeroCrossing2(y, yprev);
	sum_cross += ZeroCrossing2(z, zprev);
	xprev = x;
	yprev = y;
	zprev = z;
	num_crossings = 0.9f * num_crossings + ((1.0f - 0.9f) * sum_cross);
	return num_crossings;
}

void crossing_feature(const float* input, float* output) {

    // Calculate zero crossing
    float crossing_score = CalculateCrossings2(RawAcc.x, RawAcc.y, RawAcc.z);
	TRIGGER_TIMES[FEATURE_CROSSING] = LastAccelTime;
	TRIGGER_VALUE[FEATURE_CROSSING] = crossing_score;

}

/* Window data buffer */
float x_data_buffer[KURT_N + 1];
float y_data_buffer[KURT_N + 1];
float z_data_buffer[KURT_N + 1];
float max_vals[3]; // Store max val for each axis in time eindow
int16_t buffer_pos;
int16_t buffer_len;
float moments[4];
float data_vector[40];

const float b_1_factors[] = {0.0f, 0.02564103f, 0.05128205f, 0.07692308f, 0.1025641f, 0.1282051f, 0.1538462f, 0.1794872f, 0.2051282f, 0.2307692f,
							 0.2564103f, 0.2820513f, 0.3076923f, 0.3333333f, 0.3589744f, 0.3846154f, 0.4102564f, 0.4358974f, 0.4615385f, 0.4871795f, 0.5128205f, 0.5384616f, 0.5641026f,
							 0.5897436f, 0.6153846f, 0.6410257f, 0.6666667f, 0.6923077f, 0.7179487f, 0.7435898f, 0.7692308f, 0.7948718f, 0.8205128f, 0.8461539f, 0.8717949f, 0.8974359f,
							 0.9230769f, .948718f, 0.974359f, 1.0f};
const float b_2_factors[] =
	{
		0.0f, 0.0f, 0.00134952f, 0.00404858f, 0.00809716f, 0.01349528f, 0.02024291f, 0.02834008f, 0.03778677f, 0.048583f, 0.06072874f, 0.07422403f, 0.08906882f, 0.1052632f, 0.122807f, 0.1417004f, 0.1619433f, 0.1835358f, 0.2064777f, 0.2307692f, 0.2564103f, 0.2834008f, 0.3117409f, 0.3414305f, 0.3724696f, 0.4048583f, 0.4385965f, 0.4736842f, 0.5101215f, 0.5479082f, 0.5870445f, 0.6275303f, 0.6693657f, 0.7125506f, 0.757085f, 0.802969f, 0.8502024f, 0.8987854f, 0.948718f, 1.0f};
const float b_3_factors[] =
	{
		0.0f, 0.0f, 0.0f, 0.0001094212f, 0.0004376846f, 0.001094212f, 0.002188423f, 0.003829741f, 0.006127585f, 0.009191378f, 0.01313054f, 0.01805449f, 0.02407266f,
		0.03129445f, 0.0398293f, 0.04978663f, 0.06127585f, 0.07440639f, 0.08928767f, 0.1060291f, 0.1247401f, 0.1455301f, 0.1685086f, 0.1937849f, 0.2214684f, 0.2516687f,
		0.284495f, 0.3200569f, 0.3584637f, 0.3998249f, 0.4442499f, 0.4918481f, 0.542729f, 0.5970019f, 0.6547762f, 0.7161615f, 0.7812671f, 0.8502024f, 0.9230769f, 1.0f};

void GetBlendVal(float *x_avg, float *y_avg, float *z_avg, const float a)
{
	*x_avg = (a * x_data_buffer[buffer_pos]) + ((1.0f - a) * (*x_avg));
	*y_avg = (a * y_data_buffer[buffer_pos]) + ((1.0f - a) * (*y_avg));
	*z_avg = (a * z_data_buffer[buffer_pos]) + ((1.0f - a) * (*z_avg));
}

/*****************************************************************************
 * Perform in place insertion sort on provided float array.
 * @param[out] array to be sorted,
 * @param[in] length of array to sort.
 *****************************************************************************/
void InsertionSort(float *array, int arr_len)
{
	for (int i = 1; i < arr_len; i++)
	{
		int j = i;
		while (j > 0 && array[j - 1] > array[j])
		{
			// Swap values
			float temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;

			j = j - 1;
		}
	}
}

/*****************************************************************************
 * Calculates up to the 4th order L-moment, note the input vector has to be 4 samples long!
 * @param[in] x
 * @return the l-moments of up to 4th order
 *****************************************************************************/
void lmom4(float *x)
{

	for (int i = 0; i < 40; i++)
	{
		data_vector[i] = x[i];
	}

	InsertionSort(data_vector, 40);

	float b0 = 0.0f;
	float b1 = 0.0f;
	float b2 = 0.0f;
	float b3 = 0.0f;

	for (int i = 0; i < 40; i++)
	{
		b0 += data_vector[i];
		b1 += b_1_factors[i] * data_vector[i];
		b2 += b_2_factors[i] * data_vector[i];
		b3 += b_3_factors[i] * data_vector[i];
	}

	b0 = (b0) / 40.0f;
	b1 = (b1) / 40.0f;
	b2 = (b2) / 40.0f;
	b3 = (b3) / 40.0f;

	moments[0] = (b0);
	moments[1] = ((2.0f * b1) - b0);
	moments[2] = ((6.0f * b2) - (6.0f * b1) + b0);
	moments[3] = ((20.0f * b3) - (30.0f * b2) + (12.0f * b1) - b0);
}

void chaos_feature(const float *input, float *output)
{
	// Fill up buffer if needed
	while (buffer_len < KURT_N)
	{
		x_data_buffer[buffer_len] = 0.0f; // RawAcc.x;
		y_data_buffer[buffer_len] = 0.0f; // RawAcc.y;
		z_data_buffer[buffer_len] = 0.0f; // RawAcc.z;
		buffer_len++;
	}

	float old_x = RawAcc.x;
	float old_y = RawAcc.y;
	float old_z = RawAcc.z;
	GetBlendVal(&old_x, &old_y, &old_z, 0.5f);

	buffer_pos = (buffer_pos + 1) % KURT_N;
	x_data_buffer[buffer_pos] = old_x;
	y_data_buffer[buffer_pos] = old_y;
	z_data_buffer[buffer_pos] = old_z;

	float kurt_score = 0.0f;

	lmom4(x_data_buffer);
	kurt_score += (moments[3] / moments[1]);

	lmom4(y_data_buffer);
	kurt_score += (moments[3] / moments[1]);

	lmom4(z_data_buffer);
	kurt_score += (moments[3] / moments[1]);

	TRIGGER_TIMES[FEATURE_CHAOS] = LastAccelTime;
	TRIGGER_VALUE[FEATURE_CHAOS] = kurt_score;
}


SampleState fx = {0}, fy = {0}, fz = {0};

const float b[] = {0.0675, 0.1349, 0.0675};  // feedforward
const float a[] = {1.0, -1.1429, 0.4128};    // feedback

float filter_sample(float input, SampleState *state){
    
    // Shift input history
    state->x[2] = state->x[1];
    state->x[1] = state->x[0];
    state->x[0] = input;

    // Shift output history
    state->y[2] = state->y[1];
    state->y[1] = state->y[0];

    // Apply filter formula (Direct Form I)
    state->y[0] = b[0]*state->x[0] + b[1]*state->x[1] + b[2]*state->x[2] - a[1]*state->y[1] - a[2]*state->y[2];

    return state->y[0];
}

void sampling_feature(const float *input, float *output)
{
    TRIGGER_VALUE[FEATURE_SAMPLING_X] = filter_sample(RawAcc.x, &fx);
    TRIGGER_VALUE[FEATURE_SAMPLING_Y] = filter_sample(RawAcc.y, &fy);
    TRIGGER_VALUE[FEATURE_SAMPLING_Z] = filter_sample(RawAcc.z, &fz);
}


static inline void update_features(const float *input, bool force, bool dim, bool rot, bool cross, bool chaos, bool sampling, float *output)
{

   RawAcc.x = input[0];
   RawAcc.y = input[1];
   RawAcc.z = input[2];

   int i = 0;

   if (force)
   {
      force_feature(input, output);
      output[i] = TRIGGER_VALUE[FEATURE_FORCE];
      i++;
   }

   if (dim)
   {
      dimension_feature(input, output);
      output[i] = TRIGGER_VALUE[FEATURE_DIMENSION];
      i++;
   }

   if (rot)
   {
      rotation_feature(input, output);
      output[i] = TRIGGER_VALUE[FEATURE_ROTATION_TOTAL];
      i++;
   }

   if (cross)
   {
      crossing_feature(input, output);
      output[i] = TRIGGER_VALUE[FEATURE_CROSSING];
      i++;
   }

   if (chaos)
   {
      chaos_feature(input, output);
      output[i] = TRIGGER_VALUE[FEATURE_CHAOS];
      i++;
   }

   if (sampling) {
      sampling_feature(input, output);
      output[i] = TRIGGER_VALUE[FEATURE_SAMPLING_X];
      i++;
      output[i] = TRIGGER_VALUE[FEATURE_SAMPLING_Y];
      i++;
      output[i] = TRIGGER_VALUE[FEATURE_SAMPLING_Z];
   }
   prevRawAcc = RawAcc;
   LastAccelTime += 20;
}



#pragma IMAGINET_FRAGMENT_END