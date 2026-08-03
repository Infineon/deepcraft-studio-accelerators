
#pragma IMAGINET_INCLUDES_BEGIN
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "gate"


/******** Definitions/Configurations for FeatureModel ********/

#ifdef _WIN32
#include <windows.h>

#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

double get_timestamp_ms() {
    static LARGE_INTEGER frequency;
    static int initialized = 0;
    if (!initialized) {
        QueryPerformanceFrequency(&frequency);
        initialized = 1;
    }

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (double)now.QuadPart * 1000.0 / frequency.QuadPart;
}

#else
#include <time.h>

double get_timestamp_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)(ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6);
}
#endif


#include <time.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>


/******** Definitions/Configurations for FeatureModel ********/

#define GATE_FALL_THRESHOLD 0.6f
#define GATE_AFTERFALL_TIMER 8000
#define GATE_SECONDARY_STILLNESS_TIMER (GATE_AFTERFALL_TIMER * 0.6)
#define GATE_SECONDARY_STILLNESS_THRESHOLD 0.14f
#define GATE_TIMESTAMP 20
typedef struct
{
    float prevMovementTotal;
    int fallTriggered;
    int stillnessTime;
    int prevFall;
    int checkExtendedStillness;
    int secondaryStillness;
    float successful_fall_time;
    float last_confidence;
} GateState;

void initGateState(GateState *state)
{
    state->prevMovementTotal = 0.0f;
    state->fallTriggered = 0;
    state->stillnessTime = 0;
    state->prevFall = 0;
    state->checkExtendedStillness = 0;
    state->secondaryStillness = 0;
    state->successful_fall_time = 0.0f;
    state->last_confidence = 0.0f;
}

float check_stillness(float timestamp, float movement, GateState *state)
{
    state->fallTriggered = (state->last_confidence > GATE_FALL_THRESHOLD);

    if (state->fallTriggered && !state->prevFall)
    {
        state->successful_fall_time = timestamp;
    }

    if (state->fallTriggered)
    {
        state->checkExtendedStillness = 1;
    }

    static int prevSuccessfulFallTime;
    if (state->checkExtendedStillness)
    {
        if (state->successful_fall_time != prevSuccessfulFallTime)
            state->stillnessTime = 0;
        
        if (timestamp - state->successful_fall_time < GATE_AFTERFALL_TIMER)
        {
            prevSuccessfulFallTime = state->successful_fall_time;
            if (fabsf(movement) < GATE_SECONDARY_STILLNESS_THRESHOLD)
            {
                state->stillnessTime += GATE_TIMESTAMP;
            }
           
            if (state->stillnessTime >= (int)(GATE_SECONDARY_STILLNESS_TIMER))
            {
                state->secondaryStillness = 1;
                state->checkExtendedStillness = 0;
                state->stillnessTime = 0;
                state->fallTriggered = 0;
                state->prevMovementTotal = 0;
            }
        }
        else
        {
            state->stillnessTime = 0;
            state->secondaryStillness = 0;
            state->checkExtendedStillness = 0;
            state->fallTriggered = 0;
            state->prevMovementTotal = 0;
            
        }
    }
    else
    {
        state->stillnessTime = 0;
    }

    state->prevFall = state->fallTriggered;
    int result = state->secondaryStillness;

    return result;
}

EXPORT void gate(const float *input, const float *confidence, int window_size, float *output)
{

    static GateState state;
    static int initialized = 0;

    if (!initialized)
    {
        initGateState(&state);
        initialized = 1;
    }

    state.last_confidence = confidence[1];

    int result = 0;

    for (int i = 0; i < window_size; ++i)
    {
        float movement = input[i];
        float timestamp = (float)get_timestamp_ms();

        if (check_stillness(timestamp, movement, &state))
            result = 1;
    }

    output[0] = 1.0f - result;
    output[1] = (float)result;
    
    state.secondaryStillness = 0;
}


#pragma IMAGINET_FRAGMENT_END