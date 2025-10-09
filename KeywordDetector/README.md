# Keyword Detector

## Overview

This machine learning project contains everything to get started with keyword detection. Bundled with the project is a trained model, the Google Speech commands dataset, and the guide how to download and prepare the dataset as well as some hints on how to take the model to production.

## Data

The original dataset can be downloaded from [here](http://download.tensorflow.org/data/speech_commands_v0.02.tar.gz) with info about licencing also covered [here](https://www.tensorflow.org/datasets/catalog/speech_commands).
The dataset differs from the original dataset in that the single wave files are concatenated to longer time series by stitching them together with 0.1 seconds of silence in between 
to prevent that multiple words are in one input time window of the model. For the transformation, you need to modify the paths in the Python script (locatied at Tools/prepare_dataset.py).

You can add more data by recording with your preferred recorder app of the OS, Deepcraft Studio's [Graph UX](https://developer.imagimob.com/data-preparation/data-collection/collect-data-using-graph-ux) with either your Computer mic or an MCU with [Imagimob Streaming protocol](https://github.com/Infineon/mtb-example-imagimob-streaming-protocol).

## Taking this model to production

This model has been fed with a lot of data to make it more comprehensive. To take this model to production we recommend the following:
1. Shortlisting a group of desired keywords, the smaller the list the better so you can focus on ensuring that the selected list is production grade
2. Change the other classes to negative data so that the model can focus on only learning the selected classes
3. Utilise the augmentation functionality to make the model more robust. We recommend also experimenting with other kinds of augmentation other than what's available in Studio to really bring the performance up
4. Collect more talking data to make the model more robust (negative data so all the words not in the selected keywords)
5. Collect more data of the selected keywords from people of different ethnicities, ages and genders


## Contents

`Data`	- Folder where data is located

- Each track has its own folder. A track is a 15-20 minutes long audio stream.

- Each folder should contain the raw audio file "data.wav" and the label file "label.label". Both are created by the script "prepare_dataset.py"

`Units` 	- Folder where custom layers and pre-processors can be added

`Models` - Folder where trained models, their predictions and generated Edge code are saved.

`Tools`  - Folder where additional files and tools can be added.


## How to train models

Install Imagimob Studio

Open KeywordDetector.improj with Studio

Open the "Training" Tab and generate a new model list. Use the GUI config for network size, etc.

Click "Start new Training Job" and submit the Job, Log-in to Imagimob Account

After Training is finished, download model(s)

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
