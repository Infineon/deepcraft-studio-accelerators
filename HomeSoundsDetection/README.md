# Home Sounds Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview
This starter model is capable of detecting a number of audio signatures common to a home setting.
It currently has 3 labels: 'cough', 'baby cry', and 'water tap', but it can easily be modified to add more.
The starter model contains 550 minutes of data, most of it being unlabelled background noise. 

## Collection of Data
The data was collected by downloading Creative Commons licensed audio files from freesounds.org.

## Adding More Data
In order to add more data, you need to upload 16000 Hz audio files with appropriate labels. This could be done either by finding more data online or recording audio using a microphone, such as the AI Evaluation Kit (https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/). 
Regardless of how the data is obtained, it can be labelled in DEEPCRAFT Studio.

## Steps to Production
The first step toward production is identifying which home sounds you want your model to detect. If you wish to focus on human sounds, for example, 'water tap' might be removed. Another thing that is strongly recommended is to use the augmentation functionality to improve model performance. This model originally had augmented data but it was removed to make the download smaller, you can perform this through the data tab of the project file (.improj)
It is worth noting that selecting a large number of sounds to detect will make the problem more difficult and introduce confusion between similar labels.
Next, you should collect data for the selected use cases, as outlined above.
Furthermore, background data needs to be collected depending on the location the end product is intended to be placed. If you have offices in mind, you will need to supplement the dataset with unlabelled office sounds, for example. 
The existing preprocessor and model architecture are unlikely to suffice, and you will need to fine-tune or overhaul these. In this it is important to keep in mind the capacity and memory limits of the deployment location.
Finally, you should evaluate the model in a realistic setting. 
In the case that false positives are a problem, you could apply post-processing techniques such as temporal smoothing.
## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.