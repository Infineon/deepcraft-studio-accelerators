# Presence Detection Project

## Overview - Use-Case

The **Presence Detection Project** aims to automatically detect and localize humans in images or video frames. The solution focuses on a lightweight model that can run efficiently on edge devices while maintaining acceptable accuracy and latency.

YOLOv5n (nano) is fine tuned using transfer learning method on a dataset from different scenarios. The model outputs bounding boxes and confidence scores for detected persons. Training included standard augmentation (flips, translation, scale, mosaic). YOLOv5n is chosen for its strong speed/accuracy balance and small footprint, enabling deployment on embeded devices. The primary sensor is a standard RGB camera (USB, MIPI-CSI, smartphone, or industrial).

This capability is relevant to many applications: 
- Safety and compliance monitoring in industrial areas
- Energy-saving presence detection for home/office automation
- Human-aware navigation in robotics and drones

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.


## Contents

**`Data`** 	- Contains data taken from Roboflow with human class images: [Human datasets](https://universe.roboflow.com/leo-ueno/people-detection-o4rdr/dataset/1). This dataset used images and/or annotations from Universe projects with CC BY 4.0 license.

**`Models`** - Folder where trained trained yolo5n, model predictions and generated Edge code are saved. 

**`Tools`**	- Folder where contains the **Model Evaluation Graph** as part of the **GraphUx project**, allowing users to:
  - Input a trained `.tflite` model.
  - Visualize and analyze the performance of the model.


## Steps to get started: Model Training and Evaluation
  
   1. Train the YOLO-based model using the provided dataset or custom data.
   2. Download the trained model `.tflite` file from trained job. 
   3. Add downloaded tflite model path in the **Model Evaluation Object Detection Graph UX** in the `Tools` folder.
   4. Run the Graph UX project to evaluate model performance in real time using selected camera.
   5. Make sure to have human presence in front of the camera and observe detection from live camera.

## Adding More Data

You can add more data to the project to improve the existing human presence detection. For the new data you are going to add, you can choose to add existed dataset or collect your own data using Studio. 
Steps for adding own collected data: 
 1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
 2. Import data to your project and retrain to get an updated model.
 

## Steps to Production

The recommended path to production for this project includes the following steps:
- Add more images with people especially in the scenario close to your own use case if detection rate is low.
- Add negative data to make human presence detections robust against non relevant objects.
- Try different augmentation settings to increase the variability of the dataset.
- Try different advanced settings such as optimizer,  iou threshold or confidence threshold to make model more or less sensitive.

## Attribution & Citation
@misc{
people-detection-o4rdr_dataset,
title = { People Detection Dataset },
type = { Open Source Dataset },
author = { Leo Ueno },
howpublished = { \url{ https://universe.roboflow.com/leo-ueno/people-detection-o4rdr } },
url = { https://universe.roboflow.com/leo-ueno/people-detection-o4rdr },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { oct },
note = { visited on 2025-10-09 },
}
