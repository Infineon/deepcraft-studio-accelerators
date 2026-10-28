# Rebuilding the dataset and preprocessing beats on the device

The scripts provided in this folder can be used to rebuild the dataset used in this project starting from the original one from PhysioNet. To do that run the following commands:

```bash
cd PrematureHeartBeatDetection/Tools
python -m pip install -r requirements.txt
python step04_prepare_dataset.py
```

The main script `step04_prepare_dataset.py` rebuilds the dataset in the `Data` folder and refreshes the session entries in `PrematureHeartBeatDetection.improj` and `Resources/dataset_manifest.json`. The scripts and the manifest define the output, so this command reproduces the shipped sessions and their train, validation, and test split.

## Scripts

1. `step01_download_bidmc.py`
   a. Downloads the PhysioNet dataset including ECG data from 15 people as `chf01`–`chf15` (`.hea`, `.dat`, `.ecg`).
2. `step02_ecg_classes.py`
   a. Maps PhysioNet beat symbols to source classes. The map is beat type only. Electrode sites are in the project README in the **Recording setup** section.
3. `step03_convert_bidmc_to_data.py`
   a. Reads ECG channel 0 and cuts each beat from the midpoint before its R-peak to the midpoint after it.
   b. Linearly interpolates that cut to 140 samples.
4. `step04_prepare_dataset.py` (main script, calls the ones above)
   a. Keeps every PVC, R-on-T PVC, and supraventricular beat, plus 100,000 normal beats spread across the 15 people (seed 73). Detector-unclassified beats are dropped.
   b. Packs up to 300 same-person, same-class beats into one Studio session/recording.
   c. Writes one `label.label` per session. In the default binary mode, positive sessions have one `premature_beat` label spanning the file. Normal sessions are header-only, so Studio treats them as `unlabeled`.
   d. Z-scores each recording on its own selected samples.
   e. Updates the project file in place. `chf07` and `chf15` stay in test. The other 13 people stay split across train and validation sessions, as listed in the manifest.

Flags for `step04_prepare_dataset.py`:

| Flag | Effect |
|---|---|
| `--skip-download` | Skip the download and use the files already under `../Raw_Data/chfdb` |
| `--force-download` | Download the PhysioNet files again. Has no effect together with `--skip-download` |
| `--keep-intermediate` | Keep the unstandardized packed sessions under `../.build/raw_packed` |
| `--label-mode binary` | Default: `unlabeled` vs `premature_beat` |
| `--label-mode three-class` | `unlabeled` plus `pvc`, `r_on_t_pvc`, and `supraventricular` |

Raw files and `.build` are not needed after a successful rebuild.

## On-device deployment

When deploying on the device, prepare each beat the same way the training beats were built, then call the network/model once. For every heartbeat: find the R-peaks, cut from the midpoint before this R-peak to the midpoint after it, resample that cut to 140 samples, and z-score it with this person's mean and standard deviation. The cut ends halfway to the next R-peak, so the decision is ready about one heartbeat later.

The following steps describe this per-beat pipeline in order, from the raw 250 Hz stream to the single call of the trained network, and point out the parts that must match training.

1. **Sample rate.** Acquire at 250 Hz, or resample the stream to 250 Hz once. The interpolation in step 4 is a second resample.
2. **Detect.** Find R-peaks with a light QRS detector on the 250 Hz buffer. Reject cuts shorter than 12 samples (`MIN_SEGMENT` / `ECG_PRE_MIN_SEGMENT`).
3. **Cut.** Keep raw samples from the previous mid-RR onward. On each new R, copy `[left, right)` into a scratch buffer and drop older samples, with `left = (R_prev + R) / 2` and `right = (R + R_next) / 2`.
4. **Interpolate.** Linearly resample that cut to 140 samples, with the same endpoints as `np.interp` in `step03_convert_bidmc_to_data.py`. For output index `k = 0 … 139` and `N = right - left`:

   ```text
   src = k * (N - 1) / 139
   i = floor(src)
   t = src - i
   y[k] = (1 - t) * x[i] + t * x[i + 1]
   ```

   If `N == 140`, copy the samples. Heart rate changes how many samples sit between the midpoints. Training always presents a 140-point shape. A raw 140-sample buffer at 250 Hz is 0.56 s of wall-clock time, a full beat only near 107 bpm.
5. **Z-score.** Apply `(y - μ) / σ` after the crop, using the live person's running mean and standard deviation, and freeze them when they settle. Hold alarms until μ and σ have settled. The means in `dataset_manifest.json` belong to the 15 training recordings. This is the same rule as the project README **Standardization** section.
6. **Classify.** Call the neural network once on the 140 samples, then wait for the next R. Keep the cut and interpolation in float or with headroom, then scale into the network input type. The training input is z-scored.

The steps above classify one complete beat. Sliding a fixed window along the raw ECG, without cutting out a beat following the steps above, is a different task/project which involves for instance a complete retraining of the models.

### Deployment code example: `ecg_preproc.h`

The self-contained C header `ecg_preproc.h` implements steps 2 to 5 above for a live 250 Hz ECG stream: it detects R-peaks, cuts the beat, interpolates it to 140 samples, and z-scores it with a running mean and standard deviation, then hands the 140 values to your code for the model call. It is an example/template to start from. Adapt the buffers, detector, numeric format, and Edge API names. But keep in mind that the mid-RR cut, linear interpolate to 140, and per-person z-score need to stay equivalent to training.

Copy `ecg_preproc.h` into the firmware and include it from one `.c` file. The functions are `static inline`, so that file holds the whole implementation. The template below defines four functions and a dummy `main` that calls them: `app_init` once at startup, `on_ecg_sample` once per 250 Hz sample, `on_stats_settled` once when `ecg_pre_stats_settled()` returns 1, and `app_poll` on every pass of the main loop. `dummy_sample_ready` and `dummy_read_millivolts` stand in for the sample timer and the ADC. Replace the commented model lines with the names from the DEEPCRAFT Studio Edge export.

```c
#include "ecg_preproc.h"
/* #include "model.h" */

static EcgPre pre;
static float beat[ECG_PRE_BEAT_LEN];
static volatile int beat_ready;

void app_init(void)
{
    ecg_pre_init(&pre);
    beat_ready = 0;
    /* model_init(); */
}

void on_ecg_sample(float millivolts)
{
    if (ecg_pre_push_sample(&pre, millivolts, beat))
        beat_ready = 1;             /* beat[] now holds one z-scored beat */
}

void on_stats_settled(void)
{
    ecg_pre_freeze(&pre);
}

void app_poll(void)
{
    if (!beat_ready)
        return;
    beat_ready = 0;
    /* model_enqueue(beat);         one inference, then wait for the next beat */
}

/* Dummy stand-ins. Replace with the real 250 Hz timer and the ADC in millivolts. */
static int dummy_sample_ready(void) { return 1; }
static float dummy_read_millivolts(void) { return 0.0f; }

int main(void)
{
    int frozen = 0;

    app_init();

    for (;;) {
        if (dummy_sample_ready())
            on_ecg_sample(dummy_read_millivolts());
        if (!frozen && ecg_pre_stats_settled(&pre)) {
            on_stats_settled();
            frozen = 1;
        }
        app_poll();
    }
}
```

The function `ecg_pre_push_sample()` returns 1 when `beat[]` is ready for the model. A beat is cut from the midpoint before its R-peak to the midpoint after it, so the header needs three R-peaks: the previous one, the one being classified, and the next one. The first beat is therefore ready when the third R-peak is detected, and every later beat is ready when the R-peak after it arrives, about one heartbeat after the beat itself. The header works this way because it reproduces how the training beats were cut.

The function `ecg_pre_stats_settled()` returns 1 when the newest 2 seconds on the ring and the 2 seconds before them have nearly the same mean and standard deviation (within 5% and 10% of the larger standard deviation). The ring holds about 4 seconds, so that comparison can first succeed once it is full, and it stays 0 while the two stretches still differ, such as while the baseline is wandering. Until `on_stats_settled()` runs, hold the alarm. The running mean and standard deviation are still changing, so the same beat would be z-scored differently a few seconds later and the model output can jump. Finish the model call before the next beat, so `beat[]` is free when `ecg_pre_push_sample()` writes the next one. Replace `ecg_pre_detect_r()` inside the header with a production QRS detector; it is a sketch with a fixed threshold.