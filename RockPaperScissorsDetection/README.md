# Rock Scissors Paper Detection Project

## Overview

The **Rock, Scissors, Paper Detection Project** is a real-time gesture recognition system powered by a YOLO-based backend for detecting and classifying hand gestures. The project aims to build a robust end-to-end system that identifies rock, scissors, and paper gestures from live video input.

This project allows the user to build object detection models that can be used in interactive applications, making it ideal for:
- **Educational purposes**
- **AI-powered games**
- **Gesture-controlled systems**

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

## Features

1. **Real-Time Gesture Detection**: The project uses a YOLO-based model to detect and classify gestures accurately and in real-time.   
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by providing the path to a `.tflite` file, using the model evaluation object detection available in the `Tools` folder.

## Contents

- **`Data`**: Contains data (7333 rgb images) derived from the [RPS dataset](https://universe.roboflow.com/roboflow-58fyf/rock-paper-scissors-sxsw) for training and testing the model.

- **`Models`**: Stores the trained YOLO-based model and its quantized versions, prepared for deployment.

- **`Tools`**: This folder contains only the **Model Evaluation Graph** as part of the **GraphUx project**, allowing users to:
  - Input a trained `.tflite` model.
  - Visualize and analyze the performance of the model.

## Steps to get started: Model Training and Evaluation
  
   1. Train the YOLO-based model using the provided dataset or custom data.
   2. Download the trained model `.tflite` file from trained job. 
   3. Add downloaded tflite model path in the **Model Evaluation Object Detection Graph UX** in the `Tools` folder.
   4. Run the Graph UX project to evaluate model performance in real time using selected camera.
   5. Perform the gestures and observe detection from live camera.
   
## Adding more data
- You can collect more data to the project following the steps below to improve the existing gestures or to include new ones.
	 1. Use `Object Detection Data Collection Graph UX` template to collect and label gesture data.
	 2. Import data to your project and retrain to get an updated model.
- You can bring data from other sources.
	 1. Import data to your project and label images if necessary.
	  
	Note: This project contains rgb format images, so new data should have rgb format.

## Steps to production
The recommended path to production for this project includes the following steps:
- Add more data for gestures with low detection rate.
- Add negative data to make  gesture detections robust against non relevant hand movements.
- Try different augmentation settings to increase the variability of the dataset, such as increase 'flip left right' and 'flip up down' parameters to get mirrored images of gestures.
- Try different advanced settings such as optimizer,  iou threshold or confidence threshold to make model more or less sensitive. 

## Attribution & Citation

This dataset in turn contains data derived from four projects:
[Egohands](https://universe.roboflow.com/brad-dwyer/egohands-public/) created by Sven Bambach and Stefan Lee and David Crandall and Chen Yu and released under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

`@inproceedings{egohands2015iccv,
    title = {Lending A Hand: Detecting Hands and Recognizing Activities in Complex Egocentric Interactions},
    author = {Sven Bambach and Stefan Lee and David Crandall and Chen Yu},
    booktitle = {IEEE International Conference on Computer Vision (ICCV)},
    year = {2015}
}`

[Rock Paper Scissors Presentation Dataset](https://universe.roboflow.com/presentations/rock-paper-scissors-presentation/) created by [Presentations](https://universe.roboflow.com/presentations) and licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/). 

[Rock Paper Scissors Dataset](https://universe.roboflow.com/team-roboflow/rock-paper-scissors-detection) created by [Team Roboflow](https://universe.roboflow.com/team-roboflow). 

`@misc{
rock-paper-scissors-detection_dataset,
title = { Rock Paper Scissors Dataset },
type = { Open Source Dataset },
author = { Team Roboflow },
howpublished = { \url{ https://universe.roboflow.com/team-roboflow/rock-paper-scissors-detection } },
url = { https://universe.roboflow.com/team-roboflow/rock-paper-scissors-detection },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { jan },
note = { visited on 2025-10-09 },
}`

[MIT Indoor Scene Recognition Dataset](universe.roboflow.com/popular-benchmarks/mit-indoor-scene-recognition/) created by [Popular Benchmarks](https://universe.roboflow.com/popular-benchmarks) and licensed under [MIT](https://choosealicense.com/licenses/mit/).

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
