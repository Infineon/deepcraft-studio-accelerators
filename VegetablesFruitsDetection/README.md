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

## Sensor(s) & Data

- **Sensor:** Camera (RGB images)
- **Input size:** 320×320 pixels
- **Classes (17):** apple, banana, grape, strawberry, kiwi, lemon, orange, peach, pineapple, watermelon, cucumber, green_vegetables, potato, tomato, bell_pepper, carrot, shiitake
- **Data format:** Imagimob session format (`.imsession` + `.labelxml` per sample)
- **Collection:** Images sourced from Roboflow exports and custom captures; includes mixed-fruit test scenes for generalization checks

## Adding More Data

- Use the **Object Detection Data Collection Graph UX** template in Studio to capture and label new images from a camera.
- Import additional labeled images through Studio's data import workflow for object detection.
- Label new data manually in Studio or use model-assisted labeling to speed up annotation.
- Group new samples by class or scenario (e.g. single-item vs. mixed produce scenes) to keep the dataset organized.

Note: This project contains RGB format images, so new data should be in RGB format.

## Attribution & Citation

This project contains data derived from the following Roboflow datasets. All listed sources are licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) unless noted otherwise. Verify commercial-use terms for each source before deployment.

- [Apples](https://universe.roboflow.com/roboflow-100/apples-fvpl5) — RF100 benchmark; originally from [Apple Sorting](https://universe.roboflow.com/arfiani-nur-sayidah-9lizr/apple-sorting-2bfhk) by Arfiani Nur Sayidah
- [Banana Detection](https://universe.roboflow.com/evgenii-zorin-cm5us/banana-detection-7jjzn)
- [Fruit](https://universe.roboflow.com/object-detection-fruit/fruit-smrhb) — multi-class fruit detection dataset
- [Fruits](https://universe.roboflow.com/kjrtest1/fruits-vtsmn) — mixed fruit scenes
- [Lemon](https://universe.roboflow.com/project-1utmy/lemon-ahnya)
- [Peach](https://universe.roboflow.com/curry/peach-4h6uv)
- [YOLO v11-2](https://universe.roboflow.com/t-ar1fh/yolo-v11-2-d8v9v) — grape and green vegetable classes (spinach renamed to `green_vegetables`)
- [Cucumber](https://universe.roboflow.com/object-detection/cucumber-dataset) — provided by Roboflow
- [Green Vegetable](https://universe.roboflow.com/daaa-ubn0h/green-vegetable)
- [Potato](https://universe.roboflow.com/vegetable/potato-uxgs4)
- [Vegetable Detection](https://universe.roboflow.com/final-project-wzoba/vegetable-detection-i2deg) — bell pepper, carrot, tomato, and related classes
- [Shiitake Mushroom](https://universe.roboflow.com/graduation-project-l20ra/shiitake-mushroom)

Custom capture data in `imagimob_collected` was collected by Imagimob and is not derived from Roboflow. Licensed under [DEEPCRAFT™ Studio Terms and Conditions](https://developer.imagimob.com/legal/studio-terms-and-conditions)


## Steps to Production

- **Increase data variability:** Add images from different lighting, backgrounds, angles, and camera devices, especially images of multiple different objects placed together. Use Studio augmentation (translate, scale, mosaic, HSV) to expand visual diversity.
- **Test set separation:** Ensure the test set includes data not used in train/validation—especially mixed-scene images with multiple produce items—to verify generalization.
- **Negative data:** Add non-produce scenes to reduce false positives on irrelevant objects.
- **Threshold tuning:** Adjust confidence and IoU thresholds in advanced training settings to balance detection sensitivity and precision for your target hardware.
- **Edge validation:** Export the int8 TFLite model and verify inference on the target Infineon PSOC™ Edge device.
