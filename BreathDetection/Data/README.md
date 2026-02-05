# Data folder

Folder where to put data of the project.

## Important note:

You will find a large number of pre-recorded samples in the folder. These are primarily grouped by day and location, as they each exhibit slight differences in terms of daily temperature and air pressure. 

Important note: You will find two main folders here you should primarily use, `train` and `test`. After training over 200 AI models, we have observed that if these Training and Test separations are utilized in the subsequent training of the AI model, the accuracy and performance improve significantly. Note: By default we only use Train and Validation, leaving the Test Set empty at the beginning.

Therefore, my recommendation is to start by strictly separating the datasets by days. If desired, you can later experiment with random mixing.

If you want to, you find in `additional data (not recommended)` a ton of other samples and examples. Maybe you could need them for developing. By default I can't recommend them, they didn't give us good results.

In addition to the selection of datasets, adjusting the weights is also extremely important. The best results were achieved with:
- Train/Val separated – warm_breath weight 2 | cool_blow weight 5

### A small note regarding the naming:
Some samples were simply named after the recording date. For more information about the labels, please open the ".imsession" or ".label" file. All other files are named according to the following scheme: LABEL_PROXIMITY_DURATION_WAIT_TIME_PRESSURE_NUMBER and look like that: xxx(_xxx)_N_N_xxx_N

### General Suggestions:

- place each dataset/recording in its own folder, including label files, videos of data collection, metadata, etc.
- give the same name to each data file in each folder, e.g. data.data, data.wav, etc.
- group folders with data from same class or characteristic. For instance, person1 contains folders gestures1, gestures2, etc. and each gesture folder contains folders with actual data

### Getting Started

For more Information please read the main README file.
Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

### Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.