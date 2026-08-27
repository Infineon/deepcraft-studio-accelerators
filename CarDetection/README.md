# Car Detection - DEEPCRAFT™ Studio Accelerator project.

This project is designed to work exclusively with DEEPCRAFT™ Studio.

## Use-case description

This Studio Accelerator provides general guidance on how to develop a Computer Vision project for car detection with an RGB camera.

The task is framed as an object detection project: a type of Computer Vision task with the goal of classifying and locating objects in the image frame. For this project, one class is used: car.

## How can I know if this project fits my use case?

You can use this starter project if:

- You need to build a Computer Vision project for detecting or counting cars in a specific environment;
- You have the possibility of collecting additional data, either from the real world or via simulated environments.

If you cannot collect a sufficient amount of representative data, this project might not provide accurate results.

## How can this project ease my go-to-production journey?

This project demonstrates how to approach the task from a Computer Vision perspective. If you start from this project, you will have:

- A ready framework for performing Object Detection (YOLO-based);
- Some data already collected and ready to be used;
- Data augmentation and model training parameters already set;
- An easy pipeline allowing you to collect or import more data as needed.

## Contents

- `Data` - Folder to put your data. This project contains public data from Roboflow (in the "img*" folders) and public data collected by Infineon on a small toy car demo setup.
- `Models` - Folder where trained models, their predictions, and generated Edge code are saved.
- `Units` - Folder where custom layers and pre-processors can be added. Not used in this project.
- `Tools` - Folder containing additional tools and project files. Not used in this project.

## Sensor settings specification

This starter project requires the PSOC™ EDGE Evaluation Kit. This platform is equipped with a PSOC™ Edge E84 MCU and a USB Camera Module. The board is designed for easy prototyping and lets you collect real-life data to build a compelling ML product fast.

Having some cars available is optional, but you may need them to test the model and collect additional data. If you want to test the project out of the box, you can also show the camera pictures of cars on your laptop screen or phone, or use toy cars.

## Collecting and expanding the dataset

To add more data, you can rely on Studio's live data collection for Computer Vision projects: real-time image data collection and labeling using a camera. You can also import a dataset collected with other means. If you want to import data collected externally, for example with a mobile phone or a camera on the field, please refer to [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

Hint: if you collect data with a mobile phone or another camera, try to set the camera to provide squared images. This will make image processing easier and avoid unwanted stretching.

## Recommended path to production

To bring this project to a production-level system, follow these general steps:

1. Identify the environment or setting where you want this model to operate. Define whether the camera will be fixed, mounted on a robot, installed on a vehicle, or used to monitor parking lots, roads, indoor spaces, or other scenarios.

2. Collect data for a prototype application.

Collect a representative amount of data in a setting as close as possible to the final setup, to fine-tune the model to specific angles, light conditions, and scene details. If detection accuracy is low or the model is confused, add negative examples to improve performance when cars are not present.

3. Import your data and train the prototype model.

Import the data you collected in DEEPCRAFT Studio. You can then follow the standard DEEPCRAFT Studio steps for processing, training, and deploying your Computer Vision model.

4. Deploy and do a real-time test of your prototype model.

The last step in the prototyping phase is to deploy the model to the device by leveraging the template application already available in ModusToolbox: MTB Example ML Imagimob MTBML. Deploy and test the firmware on the hardware. The display will show real-time detection bounding boxes.

5. Move to the production board system.

The final production setup will likely place the camera in a different position than the prototyping phase. If you can get as close as possible to production conditions during prototyping, you will be able to reuse the same model on the production board with little to no additional training or data. If not, you may need a new data collection step to capture the nuances of the final setup. Repeat steps 2, 3, and 4 for the production setup to reach a functioning application.

Note: All subsequent ML system lifetime monitoring procedures must be defined and implemented by you according to your needs, requirements, and targets.

## Dataset Attributions and Citations

@misc{car-detection-roboflow-dataset, title = {Car Detection Dataset}, type = {Open Source Dataset}, author = {lolepls}, howpublished = {\url{app.roboflow.com/lolepls/car-detection-5fc7i-vtlqe/browse}}, url = {app.roboflow.com/lolepls/car-detection-5fc7i-vtlqe/browse}, journal = {Roboflow Universe}, publisher = {Roboflow}, year = {2026}, month = {jul}, note = {visited on 2026-07-21}, }

@misc{ifx-car-dataset, title = {Infineon Car Dataset}, type = {Open Source Dataset}, author = {Miguel Pfleger}, journal = {DEEPCRAFT Studio Accelerators}, publisher = {Infineon}, year = {2026}, month = {jan}, }

## Getting Started

Please visit developer.imagimob.com, where you can read about Imagimob Studio and go through step-by-step tutorials to get started quickly.

## Help & Support

If you need support or if you want to know how to deploy the model on the device, please submit a ticket on the Infineon community forum Imagimob Studio page.
