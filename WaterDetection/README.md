# CAPSENSE&trade; Water Detection Starter model using DEEPCRAFT&trade; Studio

## Overview

This is an starter project for detecting water and finger presses on surfaces using 
the capacitive sensing technology CAPSENSE&trade; in combination with machine learning. The CY8CKIT-062S2-AI board streams data to the Studio using Streaming Protocol V2, enabling real-time data collection and evaluation of trained models.

## Getting Started

### What CAPSENSE&trade; is doing
With CAPSENSE&trade; we use a capacitive sensing to sense small changes of the self-capacitance of the sensor pad. These changes are caused by the dielectric constant of different materials. In this setup we can assume a simple parallel plate condensator and therefore use following equation:
$$C = \frac{\epsilon_0\epsilon_rA}{d}$$
Since water has a higher dielectric constant than air, the capacity is increased. These changes are used to determine the different labels for this project. To differentiate between finger touches and water on the surface, we use different sensing frequencies (100 kHz and 5.75 MHz). Water isn't affecting the self-capacitance in higher frequency ranges, which is due to its decreasing dielectric constant for higher frequencies. In contrast, a finger press can be detected at both frequencies, while water is only detectable at the low frequency.

### Framework of the project
To start with this project, there are several steps that need to be done:
#### 1. Sensor Hardware
To obtain the capacity changes a capacitive sensor is needed. In this project we use the CAPSENSE&trade; enabled microcontroller PSOC4100T with the latest generation of the CAPSENSE&trade; sensing technology. We attached a simple PCB containing three buttons surrounded by a guard ring and used all four sensing pads as one sensor (ganged). With this we can increase the sensing range of the sensor. The sensor readings for the low-frequency and the high-frequency measurements are stored into a buffer that can be read over I2C by the CY8CKIT-062S2-AI board.

#### 2. CY8CKIT-062S2-AI board
The CY8CKIT-062S2-AI board is running the Streaming Protocol V2 and reads the buffer of the CAPSENSE&trade; over I2C and then streams the sensor data into DEEPCRAFT&trade; Studio.


#### 3. DEEPCRAFT&trade; Project for collecting data
In this project we collect the data by using the Graph UX interface to create a simple data collection pipeline. The Graph UX file is located in the `Tools` folder. Connect the CY8CKIT-062S2-AI board (running the Streaming Protocol V2 firmware) to your PC and dragg it into the Graph UX window from the Node Explorer.
![alt text](/Resources/image-1.png)
After that we insert our predefined labels over the Node explorer and name them Touch, Wet, Dry
and insert a Data Track to the Graph UX window to be able to record, label and store the data from the sensor.
![](/Resources/image-2.png)
With that beeing done, we can start recording data by pressing the start button at the top toolbar.
##### Collecting and labeling data
After we pressed the start button we are connected to the board and can start the recording by pressing the record button. It is recommended to record small sessions of around 2 minutes to make it easier to distribute the recordings into the different sets (training, validation, test). For the starter model we collected in total 75 minutes of data and used a 60/20/20 train/validation/test split.
![](/Resources/image-3.png)
The image above shows a recorded session in which the measurement surface is wet and finger presses are applied. The blue line represents the low-frequency and the green line the high-frequency measurement. It can be seen that the water presence is only detected in the low-frequency, while the finger presses are detectable at both frequencies. Once the recording is stopped, you can label the recorded data by choosing a predefined label and marking the desired area with your mouse.
For touch labels, it is best to align the labeled frame with the high-frequency signal, as this indicates actual finger contact with the surface, since the low-frequency signal also captures the finger's approach to the sensing area. We collected data for following scenarios:
- **Dry**: Nothing on the measurement surface
- **Wet**: Water covering the measurement surface
- **Touch**: Finger press on dry measurement surface
- **Wet_Touch**: Finger press on wet measurement surface
- **Noise_Dry**: Dry measurement surface with hand floating over it
- **Noise_Wet**: Wet measurement surface with hand floating over it

We recorded noise to make the model more robust. A recording session for the Noise_Dry case looked like this:
**![alt text](/Resources/image-4.png)**

#### 4. DEEPCRAFT&trade; Project for training the model
##### Data
For training the model the `WaterDetection_AIKit.improj` file must be opened. Here the recorded data can be imported using the Add Data button. The individual data recordings can be assigned to the different sets (Training/Evaluation/Testing). After the recorded sessions are asigned a data distribution similar to the following picture should have been achieved.
![](/Resources/image-5.png)
Now we can move to the next step which is the Preprocessor.
##### Preprocessor
![alt text](/Resources/image-7.png)
Here a sliding window is added which takes 34 datapoints to make the prediction based on this data. This is needed since the finger press is only detectable over a series of data, to capture the whole pattern of the press. After adding the preprocessor we can start with the training.
##### Training
Now we prepared everything for the training of the model. We start creating the model by clicking on the `Generate Model List` button and set our desired configuration parameters.
![](/Resources/image-8.png)
Since the model should run on an microcontroller we want to achieve small model size. For the optimization it is good to start with the balanced option and then adjust, based on the results of the training. In the Training tab inside the Model Wizard we can adjust the epochs and loss function for the training.
After everything is setup, the Training can be started by pressing the `Start New Training Job` button.
The training is processed in the cloud and afterwards we get the results for the best model.
![alt text](/Resources/image-9.png)
After a sufficient model is trained, we can evaluate the model on live data by switching back to the data collection project.
#### 5. Model evaluation using live-data
To test the model in the DEEPCRAFT&trade; Studio we open the data collection project and drag the trained TensorFlow model file into the Graph UX window. We also drag a Label Track and Data Track into the Graph UX window for visualization.
`Note!! Currently the Studio doesnt offer to train models for integer data type which requires a custom data convert unit from Int16 to Float32 since the CAPSENSE data is an integer ADC count----- the unit is located in the Units folder`
![alt text](/Resources/image-10.png)
Now we can press the `Start` button in the top toolbar to open the live session and press record to see the live labeling by the model predictions. 

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please contact us on the following email: [support@imagimob.com](mailto:support@imagimob.com).

You can also access the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page and ask your questions.
