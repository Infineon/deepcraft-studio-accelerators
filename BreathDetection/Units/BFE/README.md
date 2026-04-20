# Breath Feature Extraction — Studio Unit

## What It Does

This DEEPCRAFT Studio unit (`BreathDetection.FeatureExtraction`) takes a raw pressure + temperature sensor window and computes **19 numerical features** that a neural network can use to classify breaths into **cool_blow**, **warm_breath**, or **unlabelled**.

It replaces raw sensor values, which vary wildly between sessions due to weather, altitude, and sensor warm-up, with stable, meaningful numbers that describe *what happened* inside each window.

## Why It Exists

Models trained directly on raw DPS368 pressure and temperature collapse to predicting only the idle class. Two root causes were identified through data analysis:

1. **Absolute pressure offset**: each session records at a different ambient pressure (930–970 hPa). The model learns the offset instead of the breath shape.
2. **Temperature drift**: the sensor heats up over time, so raw temperature values are dominated by a slow upward ramp rather than the brief thermal signature of a breath.

This unit removes both problems by computing *relative* statistics within each window. A Random Forest trained on these 19 features achieved **88% accuracy / 83% balanced accuracy** on the held-out test set, confirming that separability exists.

## Input / Output

| | Shape | Type | Description |
|---|---|---|---|
| **Input** | `[96, 2]` | Float32 | Sensor window. Column 0 = pressure (hPa), column 1 = temperature (°C) |
| **Output** | `[19]` | Float32 | Feature vector |

The recommended upstream configuration is a **Contextual Window** with:
- Window size: **96 samples** (1.5 s at 64 Hz)
- Stride: **48 samples** (50% overlap → one prediction every 0.75 s)

The unit also exposes a **Sampling Rate** parameter (default 64 Hz) so derivatives and slopes are computed in physical units (hPa/s, °C/s).

## The 19 Features

Features are grouped into five families. Each group targets a specific physical aspect of breath events.

### Group 1 — Pressure Shape (indices 0–4)

These describe the *shape* of the pressure waveform inside the window after subtracting the window mean (baseline removal).

| # | Name | Formula | Why it helps |
|---|---|---|---|
| 0 | `p_std` | Standard deviation of centred pressure | Breath events create pressure excursions; idle windows are flat. Higher std → likely a breath. |
| 1 | `p_range` | max(P) − min(P) | Peak-to-peak amplitude. Cool blows produce sharp, large-range pulses. |
| 2 | `p_skew` | Third standardised moment | Cool blows often produce an asymmetric (positively skewed) pulse; warm breaths are more symmetric. |
| 3 | `p_kurtosis` | Fourth standardised moment − 3 | Measures "peakedness". A single sharp pulse gives high kurtosis vs. gentle sustained change. |
| 4 | `p_energy` | mean(P_centred²) | Total signal energy. Proportional to p_std² but kept as a separate feature for the NN. |

> **Baseline removal** (`P_centred = P − mean(P)`) is the single most important preprocessing step. It makes the features invariant to the absolute ambient pressure, which differs by tens of hPa between recording sessions.

### Group 2 — Pressure Dynamics (indices 5–10)

These capture how *fast* the pressure changes — the first derivative dP/dt, computed as consecutive-sample differences scaled by the sampling rate (units: hPa/s).

| # | Name | Formula | Why it helps |
|---|---|---|---|
| 5 | `dp_mean` | mean(dP/dt) | Net pressure trend direction over the window. |
| 6 | `dp_std` | std(dP/dt) | Variability of pressure rate-of-change. Breath events create bursts of high variability; idle is quiet. **Ranked #4 by importance.** |
| 7 | `dp_max` | max(dP/dt) | Fastest positive pressure swing (onset of a cool blow). |
| 8 | `dp_min` | min(dP/dt) | Fastest negative pressure swing (recovery after a pulse). |
| 9 | `dp_range` | dp_max − dp_min | Total dynamic range of the derivative. **Ranked #6.** |
| 10 | `dp_abs_mean` | mean(\|dP/dt\|) | Average absolute rate of change. High for both breath types, low for idle. **Ranked #3 by importance.** |

### Group 3 — Temperature (indices 11–13)

Temperature features focus on *change*, not absolute value, to be robust to sensor self-heating.

| # | Name | Formula | Why it helps |
|---|---|---|---|
| 11 | `t_std` | std(T − mean(T)) | Temperature variability. Warm breaths raise temperature; cool blows may briefly lower it. |
| 12 | `t_range` | max(T) − min(T) | Peak-to-peak temperature excursion. |
| 13 | `t_slope` | Linear regression slope × Fs | Rate of temperature change in °C/s. **Ranked #1 by importance.** Warm breath → positive slope; cool blow → near-zero or slightly negative; idle → near-zero. This is the single most discriminative feature between the two breath classes. |

### Group 4 — Temperature Dynamics (indices 14–16)

First derivative of temperature (dT/dt), analogous to Group 2 for pressure.

| # | Name | Formula | Why it helps |
|---|---|---|---|
| 14 | `dt_mean` | mean(dT/dt) | Average temperature derivative. **Ranked #2.** Strongly positive for warm breath. |
| 15 | `dt_std` | std(dT/dt) | Temperature derivative variability. |
| 16 | `dt_abs_mean` | mean(\|dT/dt\|) | Average absolute temperature change rate. |

### Group 5 — Cross-Channel & Trend (indices 17–18)

| # | Name | Formula | Why it helps |
|---|---|---|---|
| 17 | `p_t_corr` | Pearson correlation of centred P and T | Warm breaths produce correlated pressure + temperature changes (both rise). Cool blows show lower or negative correlation— pressure spikes but temperature doesn't. |
| 18 | `p_slope` | Linear regression slope of pressure × Fs | Overall pressure trend in hPa/s. Complements `dp_mean` by being less sensitive to noise. |

## Feature Importance Ranking

From Random Forest evaluation on the training set (Gini importance):

| Rank | Feature | Importance |
|---|---|---|
| 1 | `t_slope` | 0.114 |
| 2 | `dt_mean` | 0.108 |
| 3 | `dp_abs_mean` | 0.096 |
| 4 | `dp_std` | 0.081 |
| 5 | `dp_max` | 0.045 |
| 6 | `dp_range` | 0.043 |
| 7 | `dp_min` | 0.040 |
| 8 | `t_std` | 0.039 |
| 9 | `t_range` | 0.036 |
| 10 | `p_skew` | 0.034 |

Temperature slope and derivative features dominate because they are the primary separator between cool_blow and warm_breath. Pressure derivative features are the primary separator between breath (either type) and idle.

## How It Is Computed — Algorithm

The implementation makes **three passes** over the 96-sample window with zero dynamic memory allocation:

1. **Pass 1** — Accumulate sums for means, track min/max, and gather linear-regression accumulators (Σi·P, Σi·T) for slope computation.
2. **Pass 2** — Using the means from Pass 1, compute centred variance, skewness, kurtosis, energy, and cross-channel covariance in a single loop.
3. **Pass 3** — Compute consecutive-sample derivatives and accumulate their statistics (mean, std, min, max, abs-mean) without allocating a derivative array.

All arithmetic uses `double` (64-bit) intermediates for numerical stability; the final 19 values are written as `float32`.

## Files

| File | Purpose |
|---|---|
| `FeatureExtraction.imunit` | DEEPCRAFT Studio unit definition (XML). Declares input/output shapes, parameters, contracts, and links to the code fragments. |
| `feature_extraction.py` | Python implementation (`breath_feature_extraction` fragment). Used during training in Studio and for Python unit tests. |
| `feature_extraction.h` | C implementation (`breath_feature_extraction_f32` fragment). Used for firmware code generation targeting PSoC 6. No dynamic allocation, only `math.h` and `float.h` dependencies. |

## How to Use in DEEPCRAFT Studio

1. Place all three files in the project's include directory (or `Units/`).
2. In the preprocessing pipeline, stack:
   - **Contextual Window** — 96 samples, stride 48, input shape `[2]`
   - **Breath Feature Extraction** — sampling rate = 64
3. The NN input layer should expect shape `[19]`.
4. Enable **class-weight balancing** in the loss function (the dataset is imbalanced — ~50% idle, ~25% cool_blow, ~25% warm_breath).
