# Fall Detection (Belt-mounted)

## Overview

This starter model allows you to build models to detect a fall using an IMU (Interial Mesurement Unit - accelerometer and gyroscope) mounted on the buckle of a belt.
For that, this starter model uses data collected from 2 different IMU: a Bosh IMU and an ST-Microelectronics IMU. Both IMU sensors are set up to collect data at 50 Hz using a +- 8g for the accelerometer scale and +- 500 dps for the gyro scale. 

This project gives you the infrastructure to allow you to expand on the project by adding other events to detect or adding more data and make the model production ready. 

## Taking the Project Further

To take the project to production you should do the following:

1. Add more data to the project. You can vary the data between different age groups and different types of falls.

2. Adding more data from people going about their every day lives in order to teach the model everything that is not a fall. Things like playing sports, running, walking etc. all help to ensure that the model can accurately differentiate what is and isn't a fall

## How to collect more data

To collect more data you can utilise the PSOC 6 AI Evaluation Kit (https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/) and utilise the streaming protocol (https://developer.imagimob.com/data-preparation/data-collection/collect-data-using-graph-ux) in order to get data streaming directly into the platform and can add it to your project to make it production ready. 

## How to deploy the model

You can check the ModusToolbox™ BSP CEs for different options for model deployment or find out deployment API on our [developer portal](https://developer.imagimob.com/deployment)

## Contents

`Data`  - Folder where data is located.

`Units`  - Folder where custom layers and pre-processors can be added.

`Models` - Folder where trained models, their predictions and generated Edge code are saved.

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.