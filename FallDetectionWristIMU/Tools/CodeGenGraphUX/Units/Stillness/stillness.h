
#pragma IMAGINET_INCLUDES_BEGIN
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "stillness"

#ifndef VEC3_H
#define VEC3_H

typedef struct Vec3
{
    float x, y, z;
} Vec3;

void __vMinus(Vec3 *out, Vec3 *a, Vec3 *b)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}

float __vLen(const Vec3 *in)
{
    return sqrtf((in->x * in->x) + (in->y * in->y) + (in->z * in->z));
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

#endif

typedef struct
{
    float prevMovementTotal;
    Vec3 prevAcc;
} StillnessState;

float lpfFilter(float current, float alpha, float prev)
{
    return alpha * prev + (1.0f - alpha) * current;
}

void initStillnessState(StillnessState *state)
{
    state->prevMovementTotal = 0.0f;
    state->prevAcc = (Vec3){0.0f, 0.0f, 0.0f};
}

float calculate_stillness(unsigned int timestamp, Vec3 acc, StillnessState *state)
{
    Vec3 capAcc = acc;
    Vec3 diffAcc;

    float len = __vLen(&capAcc);
    if (len > 2.5f)
        __vScale(&capAcc, 1.0f / len);

    __vMinus(&diffAcc, &capAcc, &state->prevAcc);
    float movement = __vLen(&diffAcc);

    state->prevAcc = capAcc;
    movement = lpfFilter(movement, 0.95f, state->prevMovementTotal);
    state->prevMovementTotal = movement;

    return movement;
}

void stillness(const float *input, float *output)
{
    static StillnessState state;
    static int initialized = 0;
    static unsigned int timestamp = 0;

    if (!initialized)
    {
        initStillnessState(&state);
        initialized = 1;
    }

    Vec3 acc = {input[0], input[1], input[2]};

    timestamp += 38;

    *output = calculate_stillness(timestamp, acc, &state);
}

#pragma IMAGINET_FRAGMENT_END