# Surface Image Classification

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview

The Surface Image Classification Project is a real-time road surface classification system powered by a deep learning backend for classifying different road surface conditions. The project aims to build a robust end-to-end system that identifies various asphalt and road surfaces including dry, rainy, muddy, snowy, and other surface conditions from live video input.

This project allows the user to build image classification models that can be used in interactive applications, making it ideal for:

•	Autonomous vehicle systems

•	Road condition monitoring

•	Safety and navigation assistance

•	Traffic management systems

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

## Features

1.	Real-Time Surface Classification: The project uses a deep learning model to classify road surface conditions accurately and in real-time.

2.	Custom Data Integration: Users can add new data through the data import or using Image Classification Data Collection Graph UX template and label their own data for model training.

3.	Model Evaluation: Evaluate trained models by providing .tflite file and when you double click, it will automatically generate a graph UX project for evaluate in real time.

## Contents

•	Data: Contains data (7350 rgb images) derived from various road surface datasets for training and testing the model, including different asphalt types, road surfaces, and weather conditions (rainy, muddy, snowy, etc.).

•	Models: Stores the trained image classification model and its quantized versions, prepared for deployment.
																												   
•	Input a trained .tflite model.

•	Visualize and analyze the performance of the model.

## Steps to get started: Model Training and Evaluation

1.	Train the image classification model using the provided dataset or custom data.

2.	Download the trained model .tflite file from trained job.

3.	Add downloaded tflite model path in the Model Evaluation Image Classification Graph UX in the Tools folder.

4.	Run the Graph UX project to evaluate model performance in real time using selected camera.

5.	Observe surface classification from live camera feed.

## Adding more data

•	You can collect more data to the project following the steps below to improve the existing surface classifications or to include new ones.

1.	Use Image Classification Data Collection Graph UX template to collect and label road surface data.

2.	Import data to your project and retrain to get an updated model.

•	You can bring data from other sources.

1.	Import data to your project and label images if necessary.

Note: This project contains rgb format images, so new data should have rgb format.

## Steps to production

The recommended path to production for this project includes the following steps:

•	Add more data for surface conditions with low classification accuracy.

•	Add negative data to make surface classifications robust against non-relevant road features and backgrounds.

•	Try different augmentation settings to increase the variability of the dataset, such as increase 'flip left right' and 'flip up down' parameters to get mirrored images of road surfaces.

•	Try different advanced settings such as optimizer or confidence threshold to make model more or less sensitive.

•	Consider adding data from different lighting conditions (day, night, dawn, dusk) to improve robustness.

•	Include data from various camera angles and perspectives to enhance classification accuracy.


## Attribution & Citation

This dataset in turn contains data derived from multiple projects:

Road Surface Classification Dataset created by Team Roboflow and licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

@misc{
road-surface-types-qmeud_dataset,
title = { road surface types Dataset },
type = { Open Source Dataset },
author = { issues },
howpublished = { \url{ https://universe.roboflow.com/issues/road-surface-types-qmeud } },
url = { https://universe.roboflow.com/issues/road-surface-types-qmeud },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { feb },
note = { visited on 2025-11-28 },
}

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
