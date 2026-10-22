#ifndef ECG_PREPROC_H
#define ECG_PREPROC_H

/*
 * EXAMPLE on-device preprocessor for Premature Heartbeat Detection.
 *
 * Turns a live 250 Hz single-lead ECG stream into the 140-sample z-scored
 * beat that the trained DEEPCRAFT Studio model expects. Adapt the buffers,
 * the R-peak detector, and the numeric format to your firmware. It is not
 * drop-in production code.
 *
 * Per detected beat it performs the four steps used to build Data/:
 *   1. detect the R-peak (ecg_pre_detect_r, a sketch to replace),
 *   2. cut from the midpoint before this R to the midpoint after it,
 *   3. linearly interpolate that cut to 140 samples (same as np.interp),
 *   4. z-score with the live person's running mean and std.
 * Then call the Studio Edge model once. This matches
 * Tools/step03_convert_bidmc_to_data.py. A full sliding window skips the
 * cut and needs a new training run.
 *
 * Dependencies: <stdint.h> for fixed-width integers and <math.h> for
 * sqrtf(). Both are part of any C99 toolchain, including arm-none-eabi-gcc.
 * No dynamic allocation, no stdio.
 *
 * Usage: include this header from ONE .c file (all functions are static
 * inline). Call ecg_pre_push_sample() once per 250 Hz sample, in physical
 * units (millivolts). When it returns 1, z_out[140] holds one beat ready
 * for the classifier. The first beat is ready on the third detected R-peak,
 * so each decision lags the beat by about one RR interval, as in training.
 *
 *   #include "ecg_preproc.h"
 *   #include "model.h"   // generated Studio Edge code
 *
 *   static EcgPre pre;
 *   static float z[ECG_PRE_BEAT_LEN];
 *
 *   void setup(void) { ecg_pre_init(&pre); }
 *
 *   void on_ecg_sample(float millivolts)
 *   {
 *       if (ecg_pre_push_sample(&pre, millivolts, z)) {
 *           // classify once per beat; use the names from your generated code
 *           // model_enqueue(z);
 *       }
 *   }
 *
 * Memory: two ECG_PRE_RING_LEN float buffers (8 KB at 1024) plus a
 * 140-float scratch on the stack in ecg_pre_push_sample().
 */

#include <math.h>
#include <stdint.h>

#define ECG_PRE_BEAT_LEN    140    /* model input length, fixed by training */
#define ECG_PRE_MIN_SEGMENT 12     /* shorter mid-RR cuts are skipped, as in training */
#define ECG_PRE_RING_LEN    1024   /* raw history; must cover 1.5 RR intervals (4 s at 250 Hz) */
#define ECG_PRE_REFRACT_SMP 50     /* detector dead time after a peak: 200 ms at 250 Hz */
#define ECG_PRE_PEAK_MV     0.4f   /* detector threshold on the high-passed signal, in mV */
/* "Settled" means the newest half of the ring and the half before it agree.
   Each half is 512 samples, 2.048 s at 250 Hz, so the check can first succeed
   once the ring is full (about 4 s). Change the fractions for a noisier lead. */
#define ECG_PRE_SETTLE_MEAN_FRAC 0.05f /* |mean_new - mean_old| <= this * std */
#define ECG_PRE_SETTLE_STD_FRAC  0.10f /* |std_new - std_old|  <= this * std */

typedef struct {
    float    ring[ECG_PRE_RING_LEN];    /* most recent raw samples, indexed by sample count */
    float    scratch[ECG_PRE_RING_LEN]; /* one contiguous mid-RR cut */
    uint32_t n;            /* samples pushed so far; also the index of the next sample */
    int32_t  r_prev;       /* sample index of the R-peak before the beat being classified */
    int32_t  r_curr;       /* sample index of the R-peak of the beat being classified */
    float    lp;           /* slow low-pass state used by the sketch detector */
    float    prev_hp;      /* previous high-passed sample, for the peak test */
    int32_t  last_peak_n;  /* sample index of the last declared R-peak */
    double   mean;         /* running mean of the raw stream (Welford) */
    double   m2;           /* running sum of squared deviations (Welford) */
    uint32_t n_stats;      /* samples included in mean / m2 */
    int      frozen;       /* 1 stops the statistics update; see ecg_pre_freeze() */
} EcgPre;

/* Reset every field. Call once before the first sample. */
static inline void ecg_pre_init(EcgPre *s)
{
    uint32_t i;
    for (i = 0; i < ECG_PRE_RING_LEN; i++) {
        s->ring[i] = 0.f;
        s->scratch[i] = 0.f;
    }
    s->n = 0;
    s->r_prev = -1;
    s->r_curr = -1;
    s->lp = 0.f;
    s->prev_hp = 0.f;
    s->last_peak_n = -1;
    s->mean = 0.0;
    s->m2 = 0.0;
    s->n_stats = 0;
    s->frozen = 0;
}

/*
 * Stop updating the running mean and std. Call this once
 * ecg_pre_stats_settled() returns 1, so a later burst of premature beats
 * or motion cannot shift the z-score.
 */
static inline void ecg_pre_freeze(EcgPre *s)
{
    s->frozen = 1;
}

/* Current running std of the raw stream. 1.0 until two samples are seen. */
static inline float ecg_pre_std(const EcgPre *s)
{
    float sigma = 1.f;
    if (s->n_stats > 1)
        sigma = sqrtf((float)(s->m2 / (double)(s->n_stats - 1)));
    if (sigma < 1e-6f)
        sigma = 1.f;
    return sigma;
}

/* Read raw sample number idx from the ring. idx must be within the last ECG_PRE_RING_LEN samples. */
static inline float ecg_pre_ring_at(const EcgPre *s, int32_t idx)
{
    return s->ring[(uint32_t)idx % ECG_PRE_RING_LEN];
}

/* Sample mean and sample std of ring samples [start, start + count). */
static inline void ecg_pre_range_stats(
    const EcgPre *s, int32_t start, int32_t count, float *mean_out, float *std_out)
{
    double mean = 0.0;
    double m2 = 0.0;
    int32_t i;
    for (i = 0; i < count; i++) {
        double x = (double)ecg_pre_ring_at(s, start + i);
        double d = x - mean;
        mean += d / (double)(i + 1);
        m2 += d * (x - mean);
    }
    *mean_out = (float)mean;
    *std_out = (count > 1) ? sqrtf((float)(m2 / (double)(count - 1))) : 1.f;
}

/*
 * 1 when the running mean and std have settled, or when they are already
 * frozen. Settled means the newest 2 s on the ring and the 2 s before them
 * agree within ECG_PRE_SETTLE_MEAN_FRAC and ECG_PRE_SETTLE_STD_FRAC.
 * Returns 0 until the ring holds 4 s, and whenever those two stretches
 * still differ (baseline wander, a burst of large beats).
 */
static inline int ecg_pre_stats_settled(const EcgPre *s)
{
    int32_t half = ECG_PRE_RING_LEN / 2;
    int32_t start;
    float mean_old, std_old, mean_new, std_new, scale;
    if (s->frozen)
        return 1;
    if (s->n < (uint32_t)ECG_PRE_RING_LEN)
        return 0;
    start = (int32_t)s->n - ECG_PRE_RING_LEN;
    ecg_pre_range_stats(s, start, half, &mean_old, &std_old);
    ecg_pre_range_stats(s, start + half, half, &mean_new, &std_new);
    scale = (std_new > std_old) ? std_new : std_old;
    if (scale < 1e-6f)
        return fabsf(mean_new - mean_old) <= 1e-6f;
    if (fabsf(mean_new - mean_old) > ECG_PRE_SETTLE_MEAN_FRAC * scale)
        return 0;
    if (fabsf(std_new - std_old) > ECG_PRE_SETTLE_STD_FRAC * scale)
        return 0;
    return 1;
}

/*
 * Step 3. Linearly resample x[0..n-1] onto y[0..139], keeping both
 * endpoints, exactly like np.interp(linspace(0,1,140), linspace(0,1,n), x)
 * in step03_convert_bidmc_to_data.py. n must be >= 2.
 */
static inline void ecg_pre_interp140(const float *x, int n, float *y)
{
    int k;
    if (n == ECG_PRE_BEAT_LEN) {
        for (k = 0; k < ECG_PRE_BEAT_LEN; k++)
            y[k] = x[k];
        return;
    }
    for (k = 0; k < ECG_PRE_BEAT_LEN; k++) {
        /* source position k*(n-1)/139 split into integer index and fraction */
        int   num = k * (n - 1);
        int   i   = num / (ECG_PRE_BEAT_LEN - 1);
        float t   = (float)(num % (ECG_PRE_BEAT_LEN - 1)) / (float)(ECG_PRE_BEAT_LEN - 1);
        if (i >= n - 1)
            y[k] = x[n - 1];
        else
            y[k] = (1.f - t) * x[i] + t * x[i + 1];
    }
}

/*
 * Step 1, SKETCH ONLY. Replace with a production QRS detector
 * (Pan-Tompkins or a vendor library), or feed R-peak indices yourself.
 *
 * Removes the baseline with a slow one-pole low-pass, then declares a peak
 * when the high-passed signal turns down after exceeding ECG_PRE_PEAK_MV.
 * The peak is the previous sample, so it returns that index (>= 0) or -1.
 * A refractory period of ECG_PRE_REFRACT_SMP samples prevents double hits
 * on one QRS. The fixed threshold assumes an R amplitude near 1 mV.
 */
static inline int32_t ecg_pre_detect_r(EcgPre *s, float x)
{
    float hp = x - s->lp;
    int32_t peak = -1;
    s->lp += 0.05f * (x - s->lp);
    if (s->last_peak_n >= 0 &&
        (int32_t)s->n - s->last_peak_n < ECG_PRE_REFRACT_SMP) {
        s->prev_hp = hp;
        return -1;
    }
    if (s->prev_hp > ECG_PRE_PEAK_MV && hp < s->prev_hp) {
        peak = (s->n > 0) ? (int32_t)s->n - 1 : 0;
        s->last_peak_n = peak;
    }
    s->prev_hp = hp;
    return peak;
}

/* Advance the R-peak history so the new peak becomes the beat to classify next. */
static inline void ecg_pre_shift_r(EcgPre *s, int32_t r_next)
{
    if (r_next >= 0) {
        s->r_prev = s->r_curr;
        s->r_curr = r_next;
    }
}

/*
 * Steps 1-4 for one sample.
 *
 * mv    : one 250 Hz sample in physical units (millivolts).
 * z_out : receives the 140 z-scored samples when the function returns 1.
 *
 * Returns 1 when a full beat is ready for the classifier, else 0. The beat
 * returned is the one centred on r_curr; the new peak found in this call
 * only closes its right boundary. Beats whose cut is shorter than
 * ECG_PRE_MIN_SEGMENT or older than the ring are skipped.
 *
 * The sample counter is 32-bit: at 250 Hz it wraps after about 99 days.
 * Call ecg_pre_init() again if the device runs longer.
 */
static inline int ecg_pre_push_sample(EcgPre *s, float mv, float z_out[ECG_PRE_BEAT_LEN])
{
    int32_t left, right, nseg, r_next;
    int i;
    float y[ECG_PRE_BEAT_LEN];
    float sigma, mean;

    /* keep the raw sample */
    s->ring[s->n % ECG_PRE_RING_LEN] = mv;

    /* step 4 statistics, updated from the raw stream until frozen */
    if (!s->frozen) {
        double d = (double)mv - s->mean;
        s->n_stats++;
        s->mean += d / (double)s->n_stats;
        s->m2 += d * ((double)mv - s->mean);
    }

    /* step 1 */
    r_next = ecg_pre_detect_r(s, mv);
    s->n++;

    /* need three peaks: r_prev, r_curr, and the new one */
    if (r_next < 0 || s->r_prev < 0 || s->r_curr < 0) {
        ecg_pre_shift_r(s, r_next);
        return 0;
    }

    /* step 2: mid-RR boundaries around r_curr */
    left = (s->r_prev + s->r_curr) / 2;
    right = (s->r_curr + r_next) / 2;
    nseg = right - left;
    if (nseg < ECG_PRE_MIN_SEGMENT ||
        nseg > ECG_PRE_RING_LEN ||
        (int32_t)s->n - left > ECG_PRE_RING_LEN) {
        /* too short to interpolate, or the ring no longer holds sample `left` */
        ecg_pre_shift_r(s, r_next);
        return 0;
    }
    for (i = 0; i < nseg; i++)
        s->scratch[i] = ecg_pre_ring_at(s, left + i);

    /* step 3 */
    ecg_pre_interp140(s->scratch, (int)nseg, y);

    /* step 4 */
    sigma = ecg_pre_std(s);
    mean = (float)s->mean;
    for (i = 0; i < ECG_PRE_BEAT_LEN; i++)
        z_out[i] = (y[i] - mean) / sigma;

    ecg_pre_shift_r(s, r_next);
    return 1;
}

#endif /* ECG_PREPROC_H */
