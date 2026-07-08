# Vegetables Fruits Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview

This project detects and classifies fruits and vegetables in camera images using object detection.

- **Problem:** Identify multiple types of produce in real-world scenes for smart kitchen, retail, and food-handling applications.
- **Machine Learning method:** Supervised object detection with YOLOv8n (320×320 input), trained in DEEPCRAFT Studio and exported as int8 TFLite for Infineon edge deployment.
- **Sensor and data:** Camera; RGB images with bounding-box labels for 17 produce classes.
- **Relevance:** Automated produce recognition supports smart appliances, inventory systems, quality inspection, and consumer-facing food applications on edge devices.

## Features

1. **Real-Time Produce Detection**: The project uses a YOLOv8n-based model to detect and classify 17 types of fruits and vegetables accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double-clicking the `.tflite` file, which generates a Graph UX project to run with a live camera or video file.

## Contents

`Data` - Folder containing labeled RGB image sessions for training, validation, and testing. Organized by produce category (fruits, vegetables, mixed-scene test sets). 

`Models` - Folder where trained YOLOv8n models, predictions, and generated Edge code are saved after training in Studio.

`Resources` - Folder containing supporting project files, including `name_mapping.csv` which maps original Roboflow sample names to canonical class-based filenames used in the dataset.

## Steps to get started: Model Training and Evaluation

1. Open `VegetablesFruitsDetection.improj` in DEEPCRAFT Studio and train the YOLOv8n model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from the training job.
3. Double-click the `.tflite` file to create a Graph UX evaluation project.
4. Run the Graph UX project to evaluate model performance in real time using a selected camera or video file.
5. Point the camera at fruits and vegetables and observe bounding-box detections from the live feed.


## Adding More Data

- Use the **Object Detection Data Collection Graph UX** template in Studio to capture and label new images from a camera.
- Import additional labeled images through Studio's data import workflow for object detection.
- Label new data manually in Studio or use model-assisted labeling to speed up annotation.
- Group new samples by class or scenario (e.g. single-item vs. mixed produce scenes) to keep the dataset organized.

Note: This project contains RGB format images, so new data should be in RGB format.

## Steps to Production

- **Increase data variability:** Add images from different lighting, backgrounds, angles, and camera devices, especially images of multiple different objects placed together. Use Studio augmentation (translate, scale, mosaic, HSV) to expand visual diversity.
- **Test set separation:** Ensure the test set includes data not used in train/validation—especially mixed-scene images with multiple produce items—to verify generalization.
- **Negative data:** Add non-produce scenes to reduce false positives on irrelevant objects.
- **Threshold tuning:** Adjust confidence and IoU thresholds in advanced training settings to balance detection sensitivity and precision for your target hardware.
- **Edge validation:** Export the int8 TFLite model and verify inference on the target Infineon PSOC™ Edge device.

## Attribution & Citation

This project contains data derived from the following datasets:

[Apples](https://universe.roboflow.com/roboflow-100/apples-fvpl5) — RF100 benchmark; originally from [Apple Sorting](https://universe.roboflow.com/arfiani-nur-sayidah-9lizr/apple-sorting-2bfhk) by Arfiani Nur Sayidah, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
apples-fvpl5_dataset,
title = { apples Dataset },
type = { Open Source Dataset },
author = { Roboflow 100 },
howpublished = { \url{ https://universe.roboflow.com/roboflow-100/apples-fvpl5 } },
url = { https://universe.roboflow.com/roboflow-100/apples-fvpl5 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { may },
note = { visited on 2026-07-08 },
}`

[Banana Detection](https://universe.roboflow.com/evgenii-zorin-cm5us/banana-detection-7jjzn) created by Evgenii Zorin, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
banana-detection-7jjzn_dataset,
title = { Banana detection Dataset },
type = { Open Source Dataset },
author = { Evgenii Zorin },
howpublished = { \url{ https://universe.roboflow.com/evgenii-zorin-cm5us/banana-detection-7jjzn } },
url = { https://universe.roboflow.com/evgenii-zorin-cm5us/banana-detection-7jjzn },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { may },
note = { visited on 2026-07-08 },
}`

[Fruit](https://universe.roboflow.com/object-detection-fruit/fruit-smrhb) — multi-class fruit detection dataset created by Object Detection Fruit, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
fruit-smrhb_dataset,
title = { Fruit Dataset },
type = { Open Source Dataset },
author = { Object Detection Fruit },
howpublished = { \url{ https://universe.roboflow.com/object-detection-fruit/fruit-smrhb } },
url = { https://universe.roboflow.com/object-detection-fruit/fruit-smrhb },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { jan },
note = { visited on 2026-07-08 },
}`

[Fruits](https://universe.roboflow.com/kjrtest1/fruits-vtsmn) — mixed fruit scenes created by KJRtest1, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
fruits-vtsmn_dataset,
title = { Fruits Dataset },
type = { Open Source Dataset },
author = { KJRtest1 },
howpublished = { \url{ https://universe.roboflow.com/kjrtest1/fruits-vtsmn } },
url = { https://universe.roboflow.com/kjrtest1/fruits-vtsmn },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { mar },
note = { visited on 2026-07-08 },
}`

[Lemon](https://universe.roboflow.com/project-1utmy/lemon-ahnya) created by project-1utmy, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
lemon-ahnya_dataset,
title = { lemon Dataset },
type = { Open Source Dataset },
author = { project-1utmy },
howpublished = { \url{ https://universe.roboflow.com/project-1utmy/lemon-ahnya } },
url = { https://universe.roboflow.com/project-1utmy/lemon-ahnya },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { aug },
note = { visited on 2026-07-08 },
}`

[Peach](https://universe.roboflow.com/curry/peach-4h6uv) created by curry, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
peach-4h6uv_dataset,
title = { peach Dataset },
type = { Open Source Dataset },
author = { curry },
howpublished = { \url{ https://universe.roboflow.com/curry/peach-4h6uv } },
url = { https://universe.roboflow.com/curry/peach-4h6uv },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { jun },
note = { visited on 2026-07-08 },
}`

[YOLO v11-2](https://universe.roboflow.com/t-ar1fh/yolo-v11-2-d8v9v) — grape and green vegetable classes (spinach renamed to `green_vegetables`) created by T, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
yolo-v11-2-d8v9v_dataset,
title = { yolo v11-2 Dataset },
type = { Open Source Dataset },
author = { T },
howpublished = { \url{ https://universe.roboflow.com/t-ar1fh/yolo-v11-2-d8v9v } },
url = { https://universe.roboflow.com/t-ar1fh/yolo-v11-2-d8v9v },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { nov },
note = { visited on 2026-07-08 },
}`

[Cucumber](https://universe.roboflow.com/object-detection/cucumber-dataset) — provided by Roboflow, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
cucumber-dataset_dataset,
title = { cucumber dataset Dataset },
type = { Open Source Dataset },
author = { new-workspace-c1vsu },
howpublished = { \url{ https://universe.roboflow.com/new-workspace-c1vsu/cucumber-dataset } },
url = { https://universe.roboflow.com/new-workspace-c1vsu/cucumber-dataset },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2021 },
month = { dec },
note = { visited on 2026-07-08 },
}`

[Green Vegetable](https://universe.roboflow.com/daaa-ubn0h/green-vegetable) created by Daaa, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
green-vegetable_dataset,
title = { Green vegetable Dataset },
type = { Open Source Dataset },
author = { Daaa },
howpublished = { \url{ https://universe.roboflow.com/daaa-ubn0h/green-vegetable } },
url = { https://universe.roboflow.com/daaa-ubn0h/green-vegetable },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { mar },
note = { visited on 2026-07-08 },
}`

[Potato](https://universe.roboflow.com/vegetable/potato-uxgs4) created by Vegetable, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
potato-uxgs4_dataset,
title = { Potato Dataset },
type = { Open Source Dataset },
author = { Vegetable },
howpublished = { \url{ https://universe.roboflow.com/vegetable/potato-uxgs4 } },
url = { https://universe.roboflow.com/vegetable/potato-uxgs4 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { mar },
note = { visited on 2026-07-08 },
}`

[Vegetable Detection](https://universe.roboflow.com/final-project-wzoba/vegetable-detection-i2deg) — bell pepper, carrot, tomato, and related classes created by final project, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
vegetable-detection-i2deg_dataset,
title = { Vegetable Detection Dataset },
type = { Open Source Dataset },
author = { final project },
howpublished = { \url{ https://universe.roboflow.com/final-project-wzoba/vegetable-detection-i2deg } },
url = { https://universe.roboflow.com/final-project-wzoba/vegetable-detection-i2deg },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { nov },
note = { visited on 2026-07-08 },
}`

[Shiitake Mushroom](https://universe.roboflow.com/graduation-project-l20ra/shiitake-mushroom) created by Graduation Project, released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@misc{
shiitake-mushroom_dataset,
title = { Shiitake Mushroom Dataset },
type = { Open Source Dataset },
author = { Graduation Project },
howpublished = { \url{ https://universe.roboflow.com/graduation-project-l20ra/shiitake-mushroom } },
url = { https://universe.roboflow.com/graduation-project-l20ra/shiitake-mushroom },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { jul },
note = { visited on 2026-07-08 },
}`

Custom capture data in `imagimob_collected` was collected by Imagimob and is not derived from Roboflow. Licensed under [DEEPCRAFT™ Studio Terms and Conditions](https://developer.imagimob.com/legal/studio-terms-and-conditions).

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.