# Siren Detector 

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

**NOTE:** This project is the Siren starter model and not the DEEPCRAFT™ Ready Model for Siren Detection. The Ready Model is available on the [Imagimob](https://www.imagimob.com/) website

## Overview 

This machine learning project contains everything you need to develop and deploy your very own version of the siren detection model.
Bundled with the project is an already trained model, and instructions for how to deploy it to the Infineon AURIX™ TC375 Lite Kit Board + 
KITA2G Audio Shield Board, which is ideally suitable for automotive and industrial applications. 

## Data

The project data consists of 487 sessions of 16-bit PCM mono audio recordings, sampled at 16Khz.
Each session is either containing siren sounds, non-siren sounds (conversation, dogs barking, etc) and/or background noise.

The data is already distributed into the training and validation set, so the project is ready to be trained.

## Use-cases

This project can be used as a starting point to create a siren detector for any relevant use case, for example:
- In automotive, to alert the driver or the car itself that there are emergency vehicles in the vicinity, to increase awareness and safety.
- In headphones and other hearables to make the wearer aware that there are emergency vehicles in the vicinity to pay attention to their surroundings.

## Taking the project further

To get this project to a production ready state you would need to add more siren and non-siren data. You might also improve it for your particular edge device
by adding data recorded with that device. You can also use augmentation to mix different sounds together and simulate distances to make the model more robust to sound variation.

**If you are interested in deploying an already production ready model into your product, Imagimob also offers a Siren Detection Ready Model. Find out more at www.imagimob.com/products.**

## Deploying on AURIX TC345

In our developer pages we have a complete guide, including a code example for deploying this starter project on the Infineon TC375 Lite Kit FreeRTOS + Audio Shield Board.
Read more at https://developer.imagimob.com/getting-started/infineon-aurix-and-imagimob-studio.

## Deploying on PSOC and other MCU
For deploying this model on other MCUs you can follow the standard deployment process and use the code examples provided in our documentation. [PSOC 6 & PSOC Edge](https://developer.imagimob.com/deployment/deploy-models-supported-boards/deploy-siren-detection-model-PSoC-boards) and other [non-Infineon MCUs](https://developer.imagimob.com/deployment/deploy-models-other-boards)

## Data Licence
All included data, is based on data extracted from freesound.org using [CC-BY-4.0](https://creativecommons.org/licenses/by/4.0/deed.en) & [CC0](https://creativecommons.org/public-domain/cc0/). You can see our master attribution list for more details; https://github.com/Infineon/deepcraft-studio-accelerators/blob/main/AttributionLists/Freesound_Attribution_List.csv

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
