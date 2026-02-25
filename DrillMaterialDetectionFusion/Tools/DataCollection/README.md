# Live Data Collection

## Overview

This project shows you how to collect and annotate IMU+Microphone sensor fusion data live. This can be done directly from your PSOC™ Edge AI Kit attached over USB-serial. It requires running the 'PSOC Edge DEEPCRAFT Machine Learning Data Collection' firmware on your device, found in ModusToolbox and the [documentation](https://developer.imagimob.com/deepcraft-studio/getting-started/infineon-boards/psoc-edge-e84-eval-kit).


The graph that you see in the Main.imunit contains input/data source nodes representing the device connected through the serial port.

## Concepts 

By opening the Main.imunit file you will see the graph which constitutes this data collection project.
In this graph there is the serial port as data source.

There is also an output data track node in the graph, connected to the data source. This node will generate the data so that it can be saved and visualized.

There is also a 'Predefined Labels' node. The labels that are entered into this node will appear as label buttons/short cuts when running the graph to record data.

When running this graph you will get a session visualizing the MEMS Microphone and the IMU data, containing a label track and label buttons which are used to label the data while recording.

After recording, you can save the session to disk, to be used for later model training or evaluation.

## Trying it out

Click the "Start" button on the toolbar to execute the GraphUX pipeline.
By clicking the "Record" button in the .imsession window, you should be able to record data:

![](../../Resources/imgs/recording_sample1.png)

![](../../Resources/imgs/recording_sample2.png)

Once you have completed data collection, you can save the sample in the `Data` folder or your preferred folder.

## Generation of preprocessing code
When deploying a trained model to an MCU, you must deploy the preprocessing alongside the model.
The preprocessing is defined as a graph within this data collection project, and code can be generated from the graph. However, when using multiple sensors (sensor fusion), data synchronization between sensors is required. Currently, DEEPCRAFT™ Studio cannot generate code for the synchronization portion from the graph. Therefore, when deploying to the MCU, you must generate separate preprocessing code for each sensor and manually implement the synchronization logic within the MCU-side project.
This section explains how to generate separate preprocessing code for each sensor.
For the synchronization logic, refer to the MCU-side project.

![](../../Resources/imgs/Preprocessor1.png)


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
