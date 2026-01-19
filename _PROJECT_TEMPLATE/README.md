# Project Title

## Overview - Use-Case

Describe here your project mentioning

- the problem you are trying to solve with Machine Learning
- the Machine Learning method used in the project
- the sensor you want to use and the corresponding type of data
- the reason(s) why solving this problem is relevant, which practical applications/products would benefit from it

## Contents

`Data` 	- Folder to put your data. Add a short description

`Models` - Folder where trained models, their predictions and generated Edge code are saved. Add a short description

`PreprocessorTrack`	- Folder where pre-processed data is stored. Add a short description

`Resources`	- Folder where all extra resources/files should be placed. Add a short description

`Tools`	- Folder where all extra tools and scripts belonging to the project should be placed. Add a short description

`Units`	- Folder where custom layers and pre-processors can be added. Add a short description

## Sensor(s) & Data

Describe here data, sensor and/or device settings specifications and/or data collection (high level).

Make sure to specify the data attribution, specifying under which conditions the data can be used for commercial purposes.


## Adding More Data

Describe here how to expand the dataset of the project using Infineon boards, Studio Graph UX, and/or other tools to collect data and/or other data sources

Describe briefly how to label the new data, focusing on Studio capabilities (manual labeling and model assisted) or add and describe a script used to label the data automatically

## Steps to Production

Describe here the main steps to bring this specific project and trained model to production level, focusing on how to solve the issues which are relevant to this project.

Some points to highlight:

- increase data variability: data from different environments, devices, conditions, use cases, people, patterns. Mention in case how to use Data Augmentation functionality for audio data
- make sure Test set contains data that is not used in Train and Validation sets and that allows you to verify that model generalizes to different scenarios
- make sure to add negative data to increase model robustness