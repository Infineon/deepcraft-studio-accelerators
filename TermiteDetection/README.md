# Termite Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview

The **Termite Detection Project** is an example project showing how to build a model that can detect termites. The project aims to build a robust end-to-end system that identifies termites from live video input.

The termite object detection model is YOLO-based and it can be used in applications for

- **Biology research: Termites population and/or species count**
- **House/gardens maintenance**

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.
			 
## Features

1. **Real-Time Termite Detection**: The project uses a YOLO-based model to detect and classify termites accurately and in real-time.   
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by providing the path to a `.tflite` file, using the model evaluation object detection available in the `Tools` folder.


## Contents

- **`Data`**: Contains data taken from Roboflow with termite class images: [Termite datasets](https://universe.roboflow.com/search?q=termite+object+detection). Data consists of 2276 annotated sessions each containing multiple annotations from different backgrounds and sizes. 

	- termite1	- this folder contains all data from Roboflow termite dataset
	- termite2	- this folder contains all data from Roboflow termite2 dataset
	- termite3	- this folder contains all data from Roboflow termite3 dataset

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Tools`**: This folder contains only the **Model Evaluation Graph** as part of the **GraphUx project**, allowing users to:
  - Input a trained `.tflite` model.
  - Visualize and analyze the performance of the model.


## Steps to get started: Model Training and Evaluation
  
   1. Train the YOLO-based model using the provided dataset or custom data.
   2. Download the trained model `.tflite` file from trained job. 
   3. Add downloaded tflite model path in the **Model Evaluation Object Detection Graph UX** in the `Tools` folder.
   4. Run the Graph UX project to evaluate model performance in real time using selected camera.
   5. Put infront of the camera pictures with termites or real termites and observe detection from live camera.

## Adding more data
You can add more data to the project following the steps below to improve the existing termite detection or to include new insects to be detected.
 1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
 2. Import data to your project and retrain to get an updated model.


## Steps to production
The recommended path to production for this project includes the following steps:
- Add more data for termite if detection rate is low.
- Add more classes like other insects to be detected
- Add negative data to make termite detections robust against non relevant objects like other, similar insects.
- Try different augmentation settings to increase the variability of the dataset, such as increase 'flip left right' and 'flip up down' parameters to get mirrored images of termites.
- Try different advanced settings such as optimizer,  iou threshold or confidence threshold to make model more or less sensitive.

## Attribution & Citation
@misc{
termite1_dataset,
title = { termite1 Dataset },
type = { Open Source Dataset },
author = { Song },
howpublished = { \url{ https://universe.roboflow.com/song-zcqwx/termite1 } },
url = { https://universe.roboflow.com/song-zcqwx/termite1 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { mar },
note = { visited on 2025-10-09 },
}

@misc{
termite-rtlzw_dataset,
title = { termite Dataset },
type = { Open Source Dataset },
author = { termite },
howpublished = { \url{ https://universe.roboflow.com/termite/termite-rtlzw } },
url = { https://universe.roboflow.com/termite/termite-rtlzw },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { may },
note = { visited on 2025-10-09 },
}

@misc{
termite2_dataset,
title = { termite2 Dataset },
type = { Open Source Dataset },
author = { song },
howpublished = { \url{ https://universe.roboflow.com/song-3auy6/termite2 } },
url = { https://universe.roboflow.com/song-3auy6/termite2 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { may },
note = { visited on 2025-10-09 },
}

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
