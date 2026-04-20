#pragma IMAGINET_INCLUDES_BEGIN
#include <math.h>
#include <float.h>
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "breath_feature_extraction_f32"

/*
 * Extract 19 statistical and derivative features from a pressure + temperature
 * sensor window for breath-detection classification.
 *
 *   input   — float array, shape [n_samples, n_channels] (row-major, channels interleaved)
 *             channel 0 = pressure (hPa), channel 1 = temperature (deg-C)
 *   n_samples  — number of time-steps in the window  (e.g. 96)
 *   n_channels — number of channels per time-step    (must be 2)
 *   fs         — sampling rate in Hz                  (e.g. 64)
 *   output     — float array, shape [19]
 *
 * Output feature indices:
 *   [0]  p_std        [1]  p_range      [2]  p_skew       [3]  p_kurtosis
 *   [4]  p_energy     [5]  dp_mean      [6]  dp_std       [7]  dp_max
 *   [8]  dp_min       [9]  dp_range     [10] dp_abs_mean  [11] t_std
 *   [12] t_range      [13] t_slope      [14] dt_mean      [15] dt_std
 *   [16] dt_abs_mean  [17] p_t_corr     [18] p_slope
 */
static void breath_feature_extraction_f32(
    const float *restrict input,
    int   n_samples,
    int   n_channels,
    int   fs,
    float *restrict output)
{
    const int nc = n_channels;
    const int n  = n_samples;
    const int nd = n - 1;                       /* derivative sample count  */
    const double fsd = (double)fs;

    /* ------------------------------------------------------------------ */
    /* Pass 1 — means, min/max, sums for linear-regression slopes         */
    /* ------------------------------------------------------------------ */
    double p_sum  = 0.0, t_sum  = 0.0;
    double ip_sum = 0.0, it_sum = 0.0;         /* sum(i * value)           */
    float  p_min  = FLT_MAX, p_max = -FLT_MAX;
    float  t_min  = FLT_MAX, t_max = -FLT_MAX;

    for (int i = 0; i < n; i++) {
        float p = input[i * nc + 0];
        float t = input[i * nc + 1];
        p_sum  += p;
        t_sum  += t;
        ip_sum += (double)i * p;
        it_sum += (double)i * t;
        if (p < p_min) p_min = p;
        if (p > p_max) p_max = p;
        if (t < t_min) t_min = t;
        if (t > t_max) t_max = t;
    }

    double p_mean = p_sum / n;
    double t_mean = t_sum / n;

    /* Linear-regression slope:  a = (n·Σ(i·y) – Σi·Σy) / (n·Σi² – (Σi)²) */
    double sum_i    = (double)n * (n - 1) / 2.0;
    double sum_i2   = (double)n * (n - 1) * (2 * n - 1) / 6.0;
    double sl_denom = (double)n * sum_i2 - sum_i * sum_i;

    double p_slope = (sl_denom != 0.0)
        ? ((double)n * ip_sum - sum_i * p_sum) / sl_denom * fsd
        : 0.0;
    double t_slope = (sl_denom != 0.0)
        ? ((double)n * it_sum - sum_i * t_sum) / sl_denom * fsd
        : 0.0;

    /* ------------------------------------------------------------------ */
    /* Pass 2 — centred statistics (variance, skewness, kurtosis, energy, */
    /*          cross-channel covariance)                                  */
    /* ------------------------------------------------------------------ */
    double p_var_sum  = 0.0, p_skew_sum = 0.0, p_kurt_sum = 0.0;
    double t_var_sum  = 0.0;
    double pt_cov_sum = 0.0;

    for (int i = 0; i < n; i++) {
        double pc  = input[i * nc + 0] - p_mean;
        double tc  = input[i * nc + 1] - t_mean;
        double pc2 = pc * pc;
        double tc2 = tc * tc;
        p_var_sum  += pc2;
        p_skew_sum += pc2 * pc;
        p_kurt_sum += pc2 * pc2;
        t_var_sum  += tc2;
        pt_cov_sum += pc * tc;
    }

    double p_var = p_var_sum / n;
    double p_std = sqrt(p_var > 0.0 ? p_var : 0.0);

    double t_var = t_var_sum / n;
    double t_std = sqrt(t_var > 0.0 ? t_var : 0.0);

    double p_skew = (p_std > 1e-12)
        ? (p_skew_sum / n) / (p_std * p_std * p_std) : 0.0;
    double p_kurt = (p_std > 1e-12)
        ? (p_kurt_sum / n) / (p_var * p_var) - 3.0   : 0.0;
    double p_energy = p_var_sum / n;  /* mean(pc²) */

    double pt_cov  = pt_cov_sum / n;
    double p_t_corr = (p_std > 1e-12 && t_std > 1e-12)
        ? pt_cov / (p_std * t_std) : 0.0;

    /* ------------------------------------------------------------------ */
    /* Pass 3 — derivative statistics (no temporary array allocated)       */
    /* ------------------------------------------------------------------ */
    double dp_sum_v  = 0.0, dp_abs_sum = 0.0, dp_sq_sum = 0.0;
    double dt_sum_v  = 0.0, dt_abs_sum = 0.0, dt_sq_sum = 0.0;
    float  dp_max_v  = -FLT_MAX, dp_min_v = FLT_MAX;

    for (int i = 0; i < nd; i++) {
        double dp = ((double)input[(i + 1) * nc + 0] - input[i * nc + 0]) * fsd;
        double dt = ((double)input[(i + 1) * nc + 1] - input[i * nc + 1]) * fsd;

        dp_sum_v  += dp;
        dp_abs_sum += fabs(dp);
        dp_sq_sum += dp * dp;
        if ((float)dp > dp_max_v) dp_max_v = (float)dp;
        if ((float)dp < dp_min_v) dp_min_v = (float)dp;

        dt_sum_v  += dt;
        dt_abs_sum += fabs(dt);
        dt_sq_sum += dt * dt;
    }

    double dp_mean_v = dp_sum_v / nd;
    double dp_var_v  = dp_sq_sum / nd - dp_mean_v * dp_mean_v;
    double dp_std_v  = sqrt(dp_var_v > 0.0 ? dp_var_v : 0.0);

    double dt_mean_v = dt_sum_v / nd;
    double dt_var_v  = dt_sq_sum / nd - dt_mean_v * dt_mean_v;
    double dt_std_v  = sqrt(dt_var_v > 0.0 ? dt_var_v : 0.0);

    /* ------------------------------------------------------------------ */
    /* Write output feature vector [19]                                   */
    /* ------------------------------------------------------------------ */
    output[0]  = (float)p_std;
    output[1]  = p_max - p_min;                         /* p_range      */
    output[2]  = (float)p_skew;
    output[3]  = (float)p_kurt;
    output[4]  = (float)p_energy;
    output[5]  = (float)dp_mean_v;
    output[6]  = (float)dp_std_v;
    output[7]  = dp_max_v;                              /* dp_max       */
    output[8]  = dp_min_v;                              /* dp_min       */
    output[9]  = dp_max_v - dp_min_v;                   /* dp_range     */
    output[10] = (float)(dp_abs_sum / nd);              /* dp_abs_mean  */
    output[11] = (float)t_std;
    output[12] = t_max - t_min;                         /* t_range      */
    output[13] = (float)t_slope;
    output[14] = (float)dt_mean_v;
    output[15] = (float)dt_std_v;
    output[16] = (float)(dt_abs_sum / nd);              /* dt_abs_mean  */
    output[17] = (float)p_t_corr;
    output[18] = (float)p_slope;
}

#pragma IMAGINET_FRAGMENT_END
