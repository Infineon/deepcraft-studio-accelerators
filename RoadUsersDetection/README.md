# Road Users Object Detection Project

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Data & Use-Case

This is an object detection project specifically tailored to identifying road users, leveraging the robust capabilities of the YOLO (You Only Look Once) algorithm. The model has been trained on a customized subset of the [PASCAL VOC 2012](https://docs.ultralytics.com/datasets/detect/voc/) dataset. 

The PASCAL VOC (Visual Object Classes) dataset is widely used, open-source visual object recognition benchmark that contains high quality annotated images spanning multiple object categories. It has been extensively adopted in computer vision research for tasks such as object detection, classification, and segmentation. 

In this work, a customized subset of PASCAL VOC 2012 version was curated to focus specifically on classes representing road users, namely **person, bicycle, bus, train, car, and motorbike**. This targeted selection was intended to optimize the model’s performance in traffic related scenarios by prioritizing categories most relevant to autonomous driving and advanced driver-assistance systems. 

The model is of a compact size and optimized architecture, making it highly suitable for deployment on resource-constrained edge devices while maintaining good performance and accuracy.

## Contents

`Data` 	- Contains the road users dataset derived from [PASCAL VOC 2012](https://docs.ultralytics.com/datasets/detect/voc/) object detection dataset, also available on [Kaggle](https://www.kaggle.com/datasets/gopalbhattrai/pascal-voc-2012-dataset). With 5074 RGB images covering the following categories: person, bicycle, bus, train, car and motorbike. Original & citation can be found [here](https://exposing.ai/voc/)

`Models` - Contains the trained and quantized model in .tflite file, ready for deployement, together with its predictions.

`Tools`	-  Contains only the Model Evaluation Graph as part of the GraphUx project, which allows to visualize and analyze the performance of the model.

## Model Training and Evaluation
 
1. Train YOLO model using the provided dataset.
2. Download the .tflite model from the trained job.
3. Add downloaded .tflite model path in the Model Evaluation Object Detection Graph UX in the Tools folder.
4. Run the Graph UX project to evaluate model performance in real time using selected camera.


## Adding more data

You can add more data from other sources for road users, or bring your own collected data and label it. Added images should be in RGB format similar to the orignal source data. Your new images can also have new objects. Overall, it is a good practice to maintain a good balance between the different objects categories.

## Steps to production

The recommended path to production for this road users detection project includes the following steps:  
- Add more data for road users if the detection rate for specific classes (e.g., cars) is low.
- Expand the dataset by incorporating additional classes, such as trucks, or other road vehicles, and ensure the data covers diverse scenarios like varying weather conditions (e.g., rain, fog, or bright sunlight), different times of day (daylight and nighttime), and challenging environments (e.g., urban, rural, or highways).
- Include negative data to improve robustness against irrelevant objects, ensuring the model avoids false detections of non-road users like roadside structures or background elements.
- Experiment with different data augmentation settings to increase dataset variability, such as enabling more frequent 'flip left-right' or 'flip up-down' transformations to generate mirrored images of road users.
- Optimize advanced settings, such as the optimizer, Intersection over Union (IoU) threshold, or confidence threshold, to fine-tune the model's sensitivity and performance for specific use cases.

## Attribution & Citation
Dataset: Everingham, M., Van Gool, L., Williams, C. K. I., Winn, J., & Zisserman, A. (2010). The Pascal Visual Object Classes (VOC) Challenge. International Journal of Computer Vision, 88(2), 303–328. 

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
