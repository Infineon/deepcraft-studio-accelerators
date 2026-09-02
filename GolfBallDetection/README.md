# Golf Ball Detection - DEEPCRAFT™ Studio Accelerator project.

This project is designed to work exclusively with DEEPCRAFT™ Studio.

## Use-case description

This Studio Accelerator aims to provide general guidance on how to develop a Computer Vision project for **golf ball detection** with RGB camera.

The task is framed as an **object detection project**: a type of Computer Vision task with the goal of classifying and locating different objects in the image frame. For this project, one class will be used: golfball.

### How can I know if this project fits my use case?

You can use this starter project if:

- You need to build a Computer Vision project for detecting or counting golf balls on grass fields;
- You have the possibility of collecting additional data, either from real world or via simulated virtual environments.

If you don't have the possibility of collecting a sufficient amount of data, this project might not provide accurate results.

### How can this project ease my go-to-production journey?

This project demonstrates how to approach the task from a Computer Vision perspective. If you start from this project, you will have:

- A ready framework for performing Object Detection (YOLO-based)
- Some data already collected and ready to be used.
- Data augmentation and model training parameters already set.
- An easy pipeline allowing you to collect or import more data as needed.

## Contents

`Data` - Folder to put your data. `Data\golf-ball-public` contains public dataset. `Data\infineon-public` contains additional data collected by Infineon team. 

`Models` - Folder where trained models, their predictions, and generated Edge code are saved.

`Units`    - Folder where custom layers and pre-processors can be added. Not used in this project.

`Tools`    - Folder containing additional tools and project. Not used in this project.


## Sensor settings specification

This starter project requires the [PSOC™ EDGE Evaluation Kit](https://www.infineon.com/evaluation-board/kit-pse84-eval). This platform is equipped with PSOC™ Edge E84 MCU and a USB Camera Module. The board is designed for easy prototyping and lets you collect real-life data to easily build a compelling ML product fast.

Having some golf balls available is optional; but you might need them to test the model and collect additional data. However, if you want to test the project out-of-the-box, you could also show the camera some pictures of golf balls on your laptop screen or your phone.

![](Resources/imgs/golfballs-labels.png)


## Collecting and expanding the dataset

To add more data, you can either rely on Studio's live data collection from Computer Vision project: [Real-Time Image data collection and labeling using camera](https://developer.imagimob.com/deepcraft-studio/data-preparation/data-collection/collect-data-without-kit/collect-image-data-using-graph-ux), or you can add your dataset collected with other means.
If you want to import data collected externally, for example with a mobile phone or with a camera on the field, please refer to (Bring your own data for object detection projects)[https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection]

**Hint**: if you collect data with a mobile phone or another camera, try to set the camera to provide squared images. This will be make easier to process image later and will avoid unwanted stretching.


## Recommended path to production

To bring this project to a production-level system, follow these general steps:

**1. Identify the environment or setting you want this model to operate**
    Ensure to define the setting you want this system to operate. 
    Will the camera be fixed? Will it be mounted on a robot? Will it have to monitor grass fields, sand fields, indoor environments?
    Will the golf balls be all of the same kind, or will they have different colors/textures?

**2. Collect data for a prototype application**
   
  Collect a representative amount of data in a setting which is as close as possible to the final setup, to fine-tune the model to specific angles, light conditions and details of the setting.
  If detection accuracy is low or the model is getting confused, try to add also negative examples to improve model performance when golf balls are not present.

**3. Import your data and train the prototype model**

  Import the data you collected in DEEPCRAFT Studio.
  You are now able to follow the standard DEEPCRAFT Studio steps for processing, training, and deploying your Computer Vision model.

  **4. Deploy and do a real-time test of your prototype model**

  Last thing to be done in prototyping phase is to deploy the model to the device by leveraging the template application already available in ModusToolbox:[MTB Example ML Imagimob MTBML Deploy](https://developer.imagimob.com/deepcraft-studio/deployment/deploy-models-supported-boards/deploy-vision-model-PSOC-Edge) and test the firmware on the machinery. The display will show you real-time detection bounding boxes.

  **5. Going to the production board system**

Last step is to move to the actual final production setup. The production system will likely have the camera placed on a specific place on the final setup, not necessarly the same one of the prorotyping phase. If you can go as close as possible to production conditions during prototyping phase, you will be able to deliver the same model also on the production board with little-to-no additional training or data needed. If this is not the case, you might need to do a new data collection step to allow the model to learn the nuances of the final setup. Follow again steps 2, 3 and 4 also for the production setup to reach a functioning application.

**Note:** All subsequent ML system lifetime monitoring procedures must be defined and implemented by you according to you needs, requirements and targets.

## Dataset Attributions and Citations

@misc{ golfball-pedge-detector, title = { GolfBall Dataset }, type = { Open Source Dataset }, author = { lolepls }, howpublished = { \url{ https://app.roboflow.com/lolepls/golf-ball-raahi-k2ygw/2 } }, url = { https://app.roboflow.com/lolepls/golf-ball-raahi-k2ygw/2 }, journal = { Roboflow Universe }, publisher = { Roboflow }, year = { 2026 }, month = { jan }, note = { visited on 2026-02-09 }, }

@misc{ infineon-public-golfball-dataset, title = { Infineon Public GolfBall Dataset }, type = { Open Source Dataset }, author = { Gioele Mombelli }, journal = { DEEPCRAFT Studio Accelerators }, publisher = { Infineon }, year = { 2026 }, month = { jan }, }

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.