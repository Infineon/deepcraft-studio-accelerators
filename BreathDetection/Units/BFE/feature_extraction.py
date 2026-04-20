#pragma IMAGINET_INCLUDES_BEGIN
import numpy as np
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "breath_feature_extraction"

def breath_feature_extraction_py(input, n_samples, n_channels, sampling_rate, output):
    """
    Extract 19 statistical and derivative features from a [n_samples, 2]
    pressure + temperature sensor window.

    Features (output indices):
      [0]  p_std        - Pressure std (baseline-removed)
      [1]  p_range      - Pressure peak-to-peak range
      [2]  p_skew       - Pressure skewness
      [3]  p_kurtosis   - Pressure excess kurtosis
      [4]  p_energy     - Pressure energy (mean squared, baseline-removed)
      [5]  dp_mean      - Mean pressure derivative (hPa/s)
      [6]  dp_std       - Pressure derivative std
      [7]  dp_max       - Max pressure derivative
      [8]  dp_min       - Min pressure derivative
      [9]  dp_range     - Pressure derivative range
      [10] dp_abs_mean  - Mean absolute pressure derivative
      [11] t_std        - Temperature std (baseline-removed)
      [12] t_range      - Temperature peak-to-peak range
      [13] t_slope      - Temperature linear slope (deg-C/s)
      [14] dt_mean      - Mean temperature derivative
      [15] dt_std       - Temperature derivative std
      [16] dt_abs_mean  - Mean absolute temperature derivative
      [17] p_t_corr     - Pressure-temperature correlation
      [18] p_slope      - Pressure linear slope (hPa/s)
    """
    n = int(n_samples)
    fs = float(sampling_rate)

    pressure = input[:, 0].astype(np.float64)
    temp     = input[:, 1].astype(np.float64)

    # --- Baseline removal ---
    p_mean = pressure.mean()
    t_mean = temp.mean()
    p_c = pressure - p_mean
    t_c = temp - t_mean

    # --- Pressure centred statistics ---
    p_std_val = np.sqrt(np.mean(p_c * p_c))
    p_range   = pressure.max() - pressure.min()
    m3 = np.mean(p_c ** 3)
    m4 = np.mean(p_c ** 4)
    p_skew = m3 / (p_std_val ** 3) if p_std_val > 1e-12 else 0.0
    p_kurt = m4 / (p_std_val ** 4) - 3.0 if p_std_val > 1e-12 else 0.0
    p_energy = np.mean(p_c * p_c)

    # --- Pressure derivatives ---
    dp = np.diff(pressure) * fs
    dp_mean_val = dp.mean()
    dp_std_val  = np.sqrt(np.mean((dp - dp_mean_val) ** 2))
    dp_max_val  = dp.max()
    dp_min_val  = dp.min()
    dp_range    = dp_max_val - dp_min_val
    dp_abs_mean = np.mean(np.abs(dp))

    # --- Temperature centred statistics ---
    t_std_val = np.sqrt(np.mean(t_c * t_c))
    t_range   = temp.max() - temp.min()

    # --- Linear regression slopes ---
    idx = np.arange(n, dtype=np.float64)
    sum_i  = n * (n - 1) / 2.0
    sum_i2 = n * (n - 1) * (2 * n - 1) / 6.0
    denom  = n * sum_i2 - sum_i * sum_i
    if denom != 0.0:
        t_slope = (n * np.dot(idx, temp)     - sum_i * temp.sum())     / denom * fs
        p_slope = (n * np.dot(idx, pressure) - sum_i * pressure.sum()) / denom * fs
    else:
        t_slope = 0.0
        p_slope = 0.0

    # --- Temperature derivatives ---
    dt = np.diff(temp) * fs
    dt_mean_val = dt.mean()
    dt_std_val  = np.sqrt(np.mean((dt - dt_mean_val) ** 2))
    dt_abs_mean = np.mean(np.abs(dt))

    # --- Cross-channel correlation ---
    if p_std_val > 1e-12 and t_std_val > 1e-12:
        p_t_corr = np.mean(p_c * t_c) / (p_std_val * t_std_val)
    else:
        p_t_corr = 0.0

    # --- Write output vector ---
    output[0]  = p_std_val
    output[1]  = p_range
    output[2]  = p_skew
    output[3]  = p_kurt
    output[4]  = p_energy
    output[5]  = dp_mean_val
    output[6]  = dp_std_val
    output[7]  = dp_max_val
    output[8]  = dp_min_val
    output[9]  = dp_range
    output[10] = dp_abs_mean
    output[11] = t_std_val
    output[12] = t_range
    output[13] = t_slope
    output[14] = dt_mean_val
    output[15] = dt_std_val
    output[16] = dt_abs_mean
    output[17] = p_t_corr
    output[18] = p_slope

#pragma IMAGINET_FRAGMENT_END
