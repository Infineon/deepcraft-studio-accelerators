# Lawn Surface Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Lawn Surface Detection** project builds an end-to-end system that classifies ground surfaces for automower applications: mowable **grass**, non-mowable **soil** and **road**, and ornamental **flowers** that must be avoided.

The object detection model is YOLO-based and it can be used in applications for

- **Autonomous lawn mower navigation:** Detect mowable grass vs soil, road, and flowers so the robot stays on lawn and treats other surfaces as out of bounds
- **Blade protection:** Confirm grass coverage before cutting; pause or reroute when soil, road, or flowers are in view
- **Garden monitoring:** Track lawn vs dirt, paved/gravel road, and flower beds from a low-mounted garden camera

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT Studio
- **Sensor and data type:** RGB camera or live video input (image data); production deployments expect a ground-level automower camera POV
- **Why it matters:** Enables automowers to distinguish mowable lawn surfaces from soil, hardscape, and flower beds in real time—provided the model is trained on data that matches the on-robot camera.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify grass, soil, road, and flowers accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double click `.tflite` file, and it will generate a Graph Ux project to run.

## Contents

- **`Data`**: Contains starter data from Roboflow with images of grass, soil, road, and flowers: [Lawn surface detection datasets](https://universe.roboflow.com/search?q=lawn%20mower%20surface%20detection). Data consists of 8,131 annotated sessions (2,291 grass, 2,500 soil, 1,500 road, 1,840 flower). Sources are **not** recorded from an automower camera—they are close-ups, classification crops, and mixed viewpoints curated to bootstrap class labels.

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv` and `rename_mapping.json` which map the current session image names back to their original Roboflow source filenames.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from trained job.
3. Double click the `.tflite` file and it will create a Graph Ux project.
4. Run the Graph UX project to evaluate model performance in real time using selected camera.
5. Put in front of the camera pictures with grass, soil, road, and flowers and observe detection from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT™ Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 8,131 sessions targeting grass, soil, road, and flowers.

**Important:** This starter dataset teaches surface *classes* but does **not** match an automower's on-board camera (height, angle, motion blur, and garden layout). Soil and road images are mostly texture close-ups; flower images mix outdoor plants and classification crops; grass images are turf close-ups and mixed lawn viewpoints, not robot-mounted camera footage. **For production on a real automower, collecting and labeling data from your robot's camera along its actual mowing route is crucial**—expect to add hundreds to thousands of mower POV sessions before the model generalizes reliably in the field.

**Training augmentation:** DEEPCRAFT Studio Augmentation Settings in this project's `.improj` were changed to better mimic the field of view of a mower running outdoors. Rotation (`degrees` 20), translation (`translate` 0.3), shear (`shear` 20), and perspective (`perspective` 0.001) approximate camera tilt and motion; HSV hue is lowered (`hsv_h` 0.005) and brightness is raised (`hsv_v` 0.6) for outdoor lighting. Parameter names follow [YOLO data augmentation](https://docs.ultralytics.com/guides/yolo-data-augmentation).

Data sources and commercial-use conditions:

- `grass_dataset1` (1000 images, CC BY 4.0): https://universe.roboflow.com/iowa-state-university-krhld/grass-o0vum
  - Turf classification images (species/disease close-ups) converted to object detection with a full-frame `grass` box. Supplemental close-up lawn texture, not mower-view surface regions.
- `grass_dataset2` (432 images, CC BY 4.0): https://universe.roboflow.com/michael-ringer/lawn-k1yxg
  - Ground-level garden lawn/yard surface regions mapped to `grass`.
- `grass_dataset3` (859 images, Public Domain): https://universe.roboflow.com/politeknik-negeri-madiun-cxqum/lawn-mower-mtphj
  - Lawn/grass images with `rumput` (grass) regions mapped to `grass`. Despite the Roboflow project name, this is **not** automower camera POV.
- `soil_dataset1` (1000 images, CC BY 4.0): https://universe.roboflow.com/forgotten-shore/soil-classification-udzoa
  - Soil-type classification close-ups (alluvial, clay, laterite, sandy, etc.) converted to object detection with a full-frame `soil` box.
- `soil_dataset2` (1000 images, CC BY 4.0): https://universe.roboflow.com/md-sohag-w9lng/soil-aoweg
  - Augmented clay, loam, sandy, and red-soil close-ups converted to object detection with a full-frame `soil` box.
- `soil_dataset3` (500 images, CC BY 4.0): https://universe.roboflow.com/rudra1103/soil-detection-xl5ol
  - Regional soil-type classification close-ups converted to object detection with a full-frame `soil` box.
- `road_dataset1` (1500 images total, CC BY 4.0): https://universe.roboflow.com/issues2/road-surface-type-syn0z
  - Road-surface classification images from Roboflow split into subfolders by original source label (500 asphalt, 500 concrete, 500 gravel). All sessions use a single `road` class with full-frame boxes. Snow, ice, and mud source classes were dropped at import.
  - Original Roboflow labels (21 subfolders under `Data/road_dataset1/`):
    - **Gravel (500):** `dry-gravel` (167), `wet-gravel` (166), `water-gravel` (167)
    - **Asphalt (500):** `dry-asphalt-smooth/slight/severe`, `wet-asphalt-smooth/slight/severe`, `water-asphalt-smooth/slight/severe` (55–56 images each)
    - **Concrete (500):** `dry-concrete-smooth/slight/severe`, `wet-concrete-smooth/slight/severe`, `water-concrete-smooth/slight/severe` (55–56 images each)
- `flower_dataset1` (547 images, CC BY 4.0): https://universe.roboflow.com/my-datasets-0aq8j/flower-46h98
  - Outdoor daisy and dandelion object-detection images mapped to `flower`.
- `flower_dataset2` (300 images, Public Domain): https://universe.roboflow.com/jacob-solawetz/flowers_classification
  - Daisy and dandelion classification images converted to full-frame `flower` boxes.
- `flower_dataset3` (993 images, CC BY 4.0): https://universe.roboflow.com/edible-plant/plant-identification-hxspu
  - Outdoor edible, wildflower, and garden-plant object detections mapped to `flower`.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

**Priority for production:** Record sessions from the **automower's own camera** at mowing height, covering every surface class on your property—grass lawns, soil patches, paths/driveways (`road`), and flower beds—in the seasons and lighting conditions the robot will see. Match the robot's resolution and field of view where possible. The starter Roboflow data is useful for initial training and class balance, but field performance depends heavily on this mower POV data.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Collect automower POV data before production.** The starter dataset has 8,131 sessions from mixed Roboflow sources—not an automower camera. Treat it as a bootstrap; retrain with data recorded on your robot (same mount, height, lens, and route) until each surface class is recognized reliably in the field.
- **Add more classes if needed.** The project currently detects `grass`, `soil`, `road`, and `flower`. Drop unused classes or add new ones (for example mulch or pavement types) before retraining.
- **Add negative data to reduce false positives.** Include mower-view images without the target surfaces and common look-alikes so the model does not treat every green or brown texture as a class.
- **Watch soil vs road vs flower confusion.** Close-up texture datasets can overlap; mower-view examples from your garden reduce mix-ups that the starter data cannot fix alone.
- **Match augmentation to outdoor variability.** Increase flip left/right for varied approach angles; adjust HSV for sun, shade, and overcast. Keep flip up/down off for a ground-level automower camera.
- **Tune confidence for your safety target.** Missing grass may leave uncut patches; mistaking road or flowers for grass can damage blades or plantings—set thresholds for the cost you care about.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.

## Attribution & Citation

@misc{
grass-o0vum_dataset,
title = { Grass Dataset },
type = { Open Source Dataset },
author = { Iowa State University },
howpublished = { \url{ https://universe.roboflow.com/iowa-state-university-krhld/grass-o0vum } },
url = { https://universe.roboflow.com/iowa-state-university-krhld/grass-o0vum },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { jul },
note = { visited on 2026-08-31 },
}


@misc{
lawn-k1yxg_dataset,
title = { lawn Dataset },
type = { Open Source Dataset },
author = { michael ringer },
howpublished = { \url{ https://universe.roboflow.com/michael-ringer/lawn-k1yxg } },
url = { https://universe.roboflow.com/michael-ringer/lawn-k1yxg },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { aug },
note = { visited on 2026-08-31 },
}


@misc{
lawn-mower-mtphj_dataset,
title = { lawn mower Dataset },
type = { Open Source Dataset },
author = { Politeknik Negeri Madiun },
howpublished = { \url{ https://universe.roboflow.com/politeknik-negeri-madiun-cxqum/lawn-mower-mtphj } },
url = { https://universe.roboflow.com/politeknik-negeri-madiun-cxqum/lawn-mower-mtphj },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { may },
note = { visited on 2026-08-31 },
}


@misc{
soil-classification-udzoa_dataset,
title = { Soil Classification Dataset },
type = { Open Source Dataset },
author = { forgotten-shore },
howpublished = { \url{ https://universe.roboflow.com/forgotten-shore/soil-classification-udzoa } },
url = { https://universe.roboflow.com/forgotten-shore/soil-classification-udzoa },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { sep },
note = { visited on 2026-08-31 },
}


@misc{
soil-aoweg_dataset,
title = { Soil Dataset },
type = { Open Source Dataset },
author = { Md Sohag },
howpublished = { \url{ https://universe.roboflow.com/md-sohag-w9lng/soil-aoweg } },
url = { https://universe.roboflow.com/md-sohag-w9lng/soil-aoweg },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { nov },
note = { visited on 2026-08-31 },
}


@misc{
soil-detection-xl5ol_dataset,
title = { Soil Detection Dataset },
type = { Open Source Dataset },
author = { rudra1103 },
howpublished = { \url{ https://universe.roboflow.com/rudra1103/soil-detection-xl5ol } },
url = { https://universe.roboflow.com/rudra1103/soil-detection-xl5ol },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { sep },
note = { visited on 2026-08-31 },
}


@misc{
road-surface-type-syn0z_dataset,
title = { road surface type Dataset },
type = { Open Source Dataset },
author = { issues2 },
howpublished = { \url{ https://universe.roboflow.com/issues2/road-surface-type-syn0z } },
url = { https://universe.roboflow.com/issues2/road-surface-type-syn0z },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { feb },
note = { visited on 2026-08-31 },
}


@misc{
flower-46h98_dataset,
title = { Flower Dataset },
type = { Open Source Dataset },
author = { My Datasets },
howpublished = { \url{ https://universe.roboflow.com/my-datasets-0aq8j/flower-46h98 } },
url = { https://universe.roboflow.com/my-datasets-0aq8j/flower-46h98 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2022 },
month = { jun },
note = { visited on 2026-08-31 },
}


@misc{
flowers_classification_dataset,
title = { Flowers Classification Dataset },
type = { Open Source Dataset },
author = { Alexander Mamaev },
howpublished = { \url{ https://universe.roboflow.com/jacob-solawetz/flowers_classification } },
url = { https://universe.roboflow.com/jacob-solawetz/flowers_classification },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2020 },
month = { apr },
note = { visited on 2026-08-31 },
}


@misc{
plant-identification-hxspu_dataset,
title = { Plant Identification Dataset },
type = { Open Source Dataset },
author = { Edible Plant },
howpublished = { \url{ https://universe.roboflow.com/edible-plant/plant-identification-hxspu } },
url = { https://universe.roboflow.com/edible-plant/plant-identification-hxspu },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { oct },
note = { visited on 2026-08-31 },
}


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).


## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
