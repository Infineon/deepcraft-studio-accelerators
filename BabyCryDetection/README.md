# Baby Cry (Starter Model)

**NOTE:** This project is the Baby Cry starter model and not the DEEPCRAFT™ Ready Model for Baby Cry Detection. The Ready Model is available on the Imagimob website

## Overview

This starter model allows you to build a baby cry detector that can be used on any supported Infineon MCU with a microphone. Everything is included to allow you to expand on the project to bring it to production on your own. 

Below you can find code examples about how to deploy the output of this project to any supported Infineon MCU with a microphone.

## Data and Classes

Data with "baby cry" sound events and other types of sounds is already added to the project to get you started. You can add more data in the same format to further improve the model. 

The provided data consists of 164 recordings from different babies and other sounds/background noise. 
Each recording contains:

- Audio (16 kHz mono, used as input to the AI model)

The project has the following classes:

- Baby Cry

*Note:* If you are using your own data, record it as 16 kHz mono, or edit the project preprocessor to fit your data format.


## Taking the Project Further

This project is only a starter model and as such some work is needed to further develop this project. Such as including more data from home environments as well as some data You can take the project further in a number of different ways:

1. You can add additional classes to the existing ones by adding the relevant data, for example, children talking, children playing, different ages etc.
2. Add your own recorded data to the dataset and see if you can improve the performance of the provided model.



**If you are interested in deploying an already production ready model into your product, Imagimob also offers a Baby Cry Detection Ready Model. Find out more at www.imagimob.com/products.**


## Imagimob - Infineon Integration

You can find below guided code examples on how to use Imagimob AI together with Infineon hardware and software to collect data and deploy your models.

Additional info are available in the guide [Getting Started with MTBML and Imagimob Studio](https://www.infineon.com/dgdl/Infineon-Machine_learning_using_ModusToolbox_Imagimob_Studio-ApplicationNotes-v01_00-EN.pdf?fileId=8ac78c8c8a8d344a018aa850bb2d21b5).

### Required Hardware and Software

- [Infineon PSoC™ 62S2 Wi-Fi Bluetooth® Pioneer Kit (CY8CKIT-062S2-43012)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/)
- [Infineon IoT Sense Expansion Kit (CY8CKIT-028-SENSE)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-028-sense/)
- [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
- [ModusToolbox™ for Machine Learning](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/modustoolbox-machine-learning/)


### Data Collection Example

- [Imagimob Data Collection](https://github.com/Infineon/mtb-example-ml-imagimob-data-collection) - code example that demonstrates how to collect data from a digital microphone using pulse-density modulation to pulse-code modulation (PDM/PCM) for your AI/ML project using Imagimob's [Capture Server](https://bitbucket.org/imagimob/captureserver/src/master/) and an [Infineon PSoC™ Pioneer Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/).


### Model Deployment Examples

- [Imagimob ModusToolbox ML Deploy](https://github.com/Infineon/mtb-example-ml-imagimob-mtbml-deploy) > code example that shows how to deploy Imagimob-generated machine learning models on an [Infineon PSoC™ Pioneer Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/) with the [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/) [Machine Learning (MTBML) Pack](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/modustoolbox-machine-learning/)

- [Imagimob Deploy](https://github.com/Infineon/mtb-example-ml-imagimob-deploy) > code example that shows how to deploy Imagimob-generated machine learning models on an Infineon PSoC™ Pioneer or Evaluation Kit (see [list of supported kits](https://github.com/Infineon/mtb-example-ml-imagimob-deploy/tree/master#supported-kits-make-variable-target)) with [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)


## Contents

`Data` - Folder where data is located

- train_set - folder with "baby cry" and other (unlabelled) data used in the Train set 
- validation_set - folder with "baby cry" and other (unlabelled) data used in the Validation set 
- test_set - folder with "baby cry" and other (unlabelled) data used in the Test set 

The folders train_set, validation_set, and test_set contain:
- baby_cry	- folder with data for "baby cry" audio
- other	- folder that contain all data that's unlabelled. It's intended make the model more robust against random noises and thus lowering false positives

`Units` - Folder where custom layers and pre-processors can be added

`Models` - Folder where trained models, their predictions and generated Edge code are saved. The folder includes also GradCam results for each session, which provide visual explanations of the model's predictions. For more information about GradCam, you can refer to the following [link](https://keras.io/examples/vision/grad_cam/).

`PreprocessorTrack` - Folder where preprocessed data is located

## Data Licence
All included data, is based on data extracted from freesound.org using [CC-BY-4.0](https://creativecommons.org/licenses/by/4.0/deed.en) & [CC0](https://creativecommons.org/public-domain/cc0/)

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
