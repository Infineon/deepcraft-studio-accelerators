# Road Sign Image Classification

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Road Sign Image Classification** project builds an end-to-end system that identifies **43 German traffic sign classes** from camera or live video input, including speed limits, warning signs, prohibitory signs, and mandatory signs (GTSRB).

The image classification model can be used in applications for

- **Autonomous vehicle systems:** Classify traffic signs in a camera view for vehicle perception pipelines
- **Advanced Driver Assistance Systems (ADAS):** Support speed-limit, warning, and regulatory-sign recognition for driver assistance
- **Traffic monitoring:** Identify common signs for navigation assistance and roadside monitoring

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** Image classification trained in DEEPCRAFT™ Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables traffic-sign recognition from live camera feeds, provided the model is trained on images that match the deployment camera, sign set, and country.

## Features

1. **Real-Time Image Classification**: The project uses a deep learning model to classify traffic signs accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Image Classification Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double-clicking the `.tflite` file; it will generate a Graph UX project to run.

## Contents

- **`Data`**: Contains starter data from the **German Traffic Sign Recognition Benchmark (GTSRB)** as RGB PNG sessions **resized to 64×64**, covering **43 traffic sign classes** such as speed limits, stop, yield, no entry, and other warning, mandatory, and prohibitory signs. Data consists of 51,839 labeled sessions grouped into class folders (for example `speed_limit_50km_h`, `stop`, `yield`). Class counts are unbalanced: the largest classes include `speed_limit_50km_h` (3,000), `speed_limit_30km_h` (2,940), and `yield` (2,880); the smallest include `speed_limit_20km_h` (270), `dangerous_curve_left` (270), and `go_straight_or_left` (270).

- **`Models`**: Stores the trained image classification model and its quantized versions as well as their predictions.

- **`Resources`**: Mapping of project sessions to original GTSRB files (`rename_mapping.csv`, `rename_mapping.json`).

## Steps to get started: Model Training and Evaluation

1. Train the image classification model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from the trained job.
3. Double-click the `.tflite` file and it will create a Graph UX project.
4. Run the Graph UX project to evaluate model performance in real time using the selected camera.
5. Put in front of the camera pictures of traffic signs (or capture live roadside views) and observe classification from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT™ Studio image-classification sessions under `Data/`. Each session contains a 64×64 RGB PNG and a `LabelXml` annotation with a class name (no bounding box). The project currently contains 51,839 sessions targeting 43 GTSRB classes. Sessions are grouped by class folder.

**Image size:** Official GTSRB images are PPM files whose size varies (about 15×15 to 250×250 pixels) and are not always square. For this project they were converted to RGB PNG and resized to **64×64**, which is also the training `ImageSize`. New data should be imported at the same 64×64 RGB size, or resized to match before training.

**Official GTSRB train/test split:** GTSRB is published in two parts: a training set (39,209 images) and a held-out test set (12,630 images). This project keeps that split. The official test images are used only for the **test** set (12,630 sessions). The 60/20/20 values stored in the project file are the Studio default target sizes; assigned sessions follow the partitions below, not a random 60/20/20 draw over all 51,839 images.

**Train vs validation is split by track.** Official GTSRB training images come in **tracks of 30 frames** of the same physical sign (the camera approaching one sign). Splitting those frames at random puts near-duplicate views of the same sign in both train and validation and makes validation scores look unrealistically high. This project instead keeps each of the 1,307 tracks entirely in train or entirely in validation (about 75/25 of tracks per class): **29,430 train**, **9,779 validation**, **12,630 test**. Session folder names use `train_*`, `valid_*`, and `test_*` to match the assigned set.

Track-based splitting, together with leaving left/right and up/down flip off, produced the best results on this dataset.

**Training augmentation:** Values below are the DEEPCRAFT™ Studio Augmentation Settings stored in this project. They are applied at 64 px. Parameter names follow [YOLO data augmentation](https://docs.ultralytics.com/guides/yolo-data-augmentation).

**Do not enable flip left/right (`fliplr`) or flip up/down (`flipud`).** Traffic signs are not symmetric. A left/right flip turns a left curve into a right curve (and `keep_left` into `keep_right`). Flipping also mirrors digits on speed-limit signs, so the model would train on invalid numbers. An up/down flip is equally wrong: signs are not seen upside down, and it also distorts arrows and digits. Using either flip will not give correct results on this task.

- `degrees` 0 — no rotation; traffic signs are upright, and rotating them can mix similar shapes.
- `translate` 0.1 — default shift, so the sign can sit slightly off-center in the crop.
- `scale` 0.5 — default zoom range for signs seen at different distances.
- `shear` 0 — left at the default off. Shear distorts pictograms and digits.
- `fliplr` 0 — **must stay off.** Left/right flip is invalid for this dataset: curve and keep-left/keep-right signs change class when mirrored, and speed-limit digits are no longer the same number.
- `flipud` 0 — **must stay off.** Up/down flip is invalid: roadside cameras do not see signs upside down, and it also corrupts arrows and speed values.
- `perspective` 0 — left at the default off.
- `bgr` 0 — left at the default off. Channel swap is not a realistic camera failure mode here.
- `mosaic` 1 — default mosaic on.
- `mixup` 0 — left at the default off. Blending two signs would mix class labels.
- `copy_paste` 0 (`CopyPasteMode` Flip) — left at the default off. The mode setting has no effect while copy-paste is 0.
- `hsv_s` 0.7 — default saturation jitter for faded or vivid sign paint.
- `hsv_v` 0.4 — default brightness jitter for sun, shade, and headlights.
- `hsv_h` 0.015 — default small hue shift so white-balance changes are covered without recoloring red/blue sign fields.

For selecting the most meaningful parameters for Data Augmentations it is important to understand your dataset, the use-case and the environment setup.

**Data source and commercial-use conditions:**

- GTSRB (51,839 images): https://benchmark.ini.rub.de/gtsrb_dataset.html
  - Standard 43-class German traffic sign recognition benchmark from the Institut für Neuroinformatik, Ruhr-Universität Bochum. Original GTSRB crops vary in size; in this project they are stored as 64×64 RGB PNGs.
  - Official terms: *“The data is free to use.”* The authors ask that you cite Stallkamp et al., IJCNN 2011. There is no Creative Commons (or other named) license, and no non-commercial restriction.

## Adding More Data

You can add more data to the project following the steps below to improve classification or to include new classes.

1. Use `Image Classification Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT™ Studio image-classification format: RGB images with matching `LabelXml` class labels. New data should be RGB, matching the existing sessions. See [Bring your own data into DEEPCRAFT™ Studio](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data) and [Label image data](https://developer.imagimob.com/deepcraft-studio/data-preparation/data-labeling/label-image-data).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data for traffic sign classes with low classification accuracy.** The starter dataset has 51,839 GTSRB sessions, but several classes have only a few hundred examples (`speed_limit_20km_h`, `dangerous_curve_left`, `go_straight_or_left`). Performance can also drop on your target camera, country, or sign design. Collect and label images from the actual deployment scene—same angle, distance, and lighting—and retrain until those classes are classified reliably.
- **Add more classes if needed.** The project currently classifies the 43 GTSRB classes only. If your product must cover another country, extra speed limits, or extra warning pictograms, add new classes and label accordingly before retraining.
- **Add negative data.** Include non-relevant objects and backgrounds (billboards, logos, buildings, vehicles) as unlabeled negatives so the model does not treat every red or blue shape as a traffic sign, then retrain.
- **Do not use flip left/right or flip up/down.** You cannot flip signs with curves or with a speed value. A left/right flip turns `dangerous_curve_left` into `dangerous_curve_right` (and the same for keep-left/keep-right) and mirrors the digits on speed-limit signs. An up/down flip puts signs upside down and also distorts arrows and numbers. Either setting will train the model on labels that no longer match the image. Leave `fliplr` and `flipud` at 0.
- **Watch directional and digit confusions.** Left/right variants and nearby speed limits (30 vs 50, 80 vs 100) are easy to mix; extra close-up examples from your camera reduce mix-ups that the original GTSRB crops cannot fix alone.
- **Match augmentation to roadside variability.** Try different augmentation settings to increase the variability of the dataset, such as modest perspective/zoom to mimic viewing signs from different angles and distances, and brightness/contrast changes to cover different lighting conditions. Keep rotation small so pictograms stay readable. Do **not** use left/right or up/down flip.
- **Try different advanced settings** such as optimizer or confidence threshold to make the model more or less sensitive. Missing a speed-limit sign may affect driver assistance; a false detection may show the wrong limit—set thresholds for the cost you care about.
- **Add data from different lighting, weather, and driving conditions.** Collect from day, night, dawn, dusk, rain, and fog, and include various camera angles, motion blur, and partial occlusions to enhance classification accuracy in real driving scenarios.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting and weather conditions, distances, and backgrounds. Use DEEPCRAFT™ Studio augmentation settings (scale, brightness, exposure) to increase image variability. Do not use flip left/right or flip up/down: curve signs and speed-limit values cannot be flipped and still match their class.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without traffic signs, and common look-alikes (billboards, logos, buildings, vehicles), so the model stays robust against false positives.

## Attribution & Citation

This project uses the **German Traffic Sign Recognition Benchmark (GTSRB)** dataset:

@article{stallkamp2012gtsrb,
  title = {Man vs. Computer: Benchmarking Machine Learning Algorithms for Traffic Sign Recognition},
  author = {Stallkamp, Johannes and Schlipsing, Marc and Salmen, Jan and Igel, Christian},
  journal = {Neural Networks},
  volume = {32},
  pages = {323--332},
  year = {2012},
  issn = {0893-6080},
  doi = {10.1016/j.neunet.2012.02.016},
  url = {https://doi.org/10.1016/j.neunet.2012.02.016},
  publisher = {Elsevier}
}

Dataset home page: https://benchmark.ini.rub.de/

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

For bringing additional image data into Studio, see [Bring your own data into DEEPCRAFT™ Studio](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data).

## Help & Support

If you need support or if you want to know how to deploy the model onto the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
