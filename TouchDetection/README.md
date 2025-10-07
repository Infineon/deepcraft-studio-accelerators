# Capsense-Sense based touch detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview

This starter project allows you to build a touch detection that can be used on any supported Infineon MCU with a capsense.

This starter project gives you the infrastructure to allow you to expand on the project or to mimic it and create your own project based on the available/included data and tools. 

The starter project is intended to be a demonstration of how you could build a model using Imagimob AI for a device with a capsense.

Below you can find code examples about how to deploy the output of this project to any supported Infineon MCU with a capsense.

## Data and Classes

The capsense needs to be set up to collect data at 50 Hz using 2 channels (button0 and button1) with raw_count, baseline and diffcount for each channel making it six features in total.

The provided data consists of nearly 117 recordings from 1 individual.

The project has the following 2 classes:

- touch
- no-touch (unlabelled)

## Imagimob - Infineon Integration

You can find below guided code examples on how to use Imagimob AI together with Infineon hardware and software to collect data and deploy your models.

Additional info are available in the guide [Getting Started with MTBML and Imagimob Studio](https://www.infineon.com/dgdl/Infineon-Machine_learning_using_ModusToolbox_Imagimob_Studio-ApplicationNotes-v01_00-EN.pdf?fileId=8ac78c8c8a8d344a018aa850bb2d21b5).

### Required Hardware and Software

- [Infineon PSoC™ 62S2 Wi-Fi Bluetooth® Pioneer Kit (CY8CKIT-062-WIFI-BT)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062-wifi-bt/)
- [Infineon IoT Sense Expansion Kit (CY8CKIT-028-SENSE)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-028-sense/)
- [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
- [ModusToolbox™ for Machine Learning](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/modustoolbox-machine-learning/)


### Data Collection Example

- [Imagimob Data Collection](https://github.com/Infineon/mtb-example-ml-imagimob-data-collection) - code example that demonstrates how to collect data from a digital microphone using pulse-density modulation to pulse-code modulation (PDM/PCM) for your AI/ML project using Imagimob's [Capture Server](https://bitbucket.org/imagimob/captureserver/src/master/) and an [Infineon PSoC™ Pioneer Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/).


### Model Deployment Examples

- [Imagimob ModusToolbox ML Deploy](https://github.com/Infineon/mtb-example-ml-imagimob-mtbml-deploy) > code example that shows how to deploy Imagimob-generated machine learning models on an [Infineon PSoC™ Pioneer Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/) with the [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/) [Machine Learning (MTBML) Pack](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/modustoolbox-machine-learning/)

- [Imagimob Deploy](https://github.com/Infineon/mtb-example-ml-imagimob-deploy) > code example that shows how to deploy Imagimob-generated machine learning models on an Infineon PSoC™ Pioneer or Evaluation Kit (see [list of supported kits](https://github.com/Infineon/mtb-example-ml-imagimob-deploy/tree/master#supported-kits-make-variable-target)) with [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)

## Taking the Project Further

You can take the project further in a number of different ways:

1. You can add additional classes to the existing ones, for example, "left-touch", "right-touch", etc.

2. Add your own recorded data to the dataset and see if you can improve the performance of the provided model.

3. You can use this project as inspiration to do your own touch detection project.

## Contents

`Data` 	- Folder to put your data.

`Models` - Folder where trained models, their predictions and generated Edge code are saved.

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.