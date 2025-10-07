# CAPSENSE&trade; Water Detection Project using DEEPCRAFT&trade; Studio

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

This project allows you to build a model for detecting water and finger presses on surfaces using the capacitive sensing technology CAPSENSE&trade; in combination with machine learning.
The CY8CKIT-062S2-AI board in combination with the latest generation of the CAPSENSE&trade; has been used to stream data to DEEPCRAFT&trade; Studio using Streaming Protocol V2, enabling real-time data collection and evaluation of trained models.

The model built with this project can be used in applications like

- water/rain detector for safety of electronic devices or equipments
- touch button/control for outdoor use


## Contents

`Data` - Folder containing the CAPSENSE&trade; data used in this project

`Models` - Folder where trained models, their predictions and generated Edge code are saved

`Resources` - Folder where all extra resources/files can be found

`Tools` - Folder containing the GraphUX unit to collect data and evaluate the model in Studio


## Sensor(s) & Data

### What CAPSENSE&trade; is doing

With CAPSENSE&trade; we use a capacitive sensing to sense small changes of the self-capacitance of the sensor pad. These changes are caused by the dielectric constant of different materials.
In this setup we can assume a simple parallel plate condensator and therefore use the following equation C = ( epsilon_0 * epsilon_r * A) / d.

Since water has a higher dielectric constant than air, the capacity is increased. These changes are used to determine the different labels for this project.
To differentiate between finger touches and water on the surface, we use different sensing frequencies (100 kHz and 5.75 MHz). Water isn't affecting the self-capacitance in higher frequency ranges, 
which is due to its decreasing dielectric constant for higher frequencies. In contrast, a finger press can be detected at both frequencies, while water is only detectable at the low frequency.

### Hardware needed for this project

To obtain the capacity changes a capacitive sensor is needed. In this project we use the CAPSENSE&trade; enabled microcontroller PSOC4100T with the latest generation of the CAPSENSE&trade; sensing 
technology. We attached a simple PCB containing three buttons surrounded by a guard ring and used all four sensing pads as one sensor (ganged). With this we can increase the sensing range of the sensor.

We used 2 ganged sensors: one ganged setup for high-frequency data with clock divider and sub-conversions equal to 8 and 512, respectively. The other ganged setup for low-frequency data with clock divider 
and sub-conversions equal to 460 and 256, respectively.

The sensor readings for the low-frequency and the high-frequency measurements are stored into a buffer that can be read over I2C by the CY8CKIT-062S2-AI board.
The latter is running the Streaming Protocol V2 and reads the buffer of the CAPSENSE&trade; over I2C and then streams the sensor data into DEEPCRAFT&trade; Studio.

Similar data and results can be obtained using a PSoC&trade; 4100S Max pioneer kit, tuned in such a way that capacitive data is similar to the one of this project. More info about CAPSENSE&trade; tuning 
available at [CAPSENSE&trade; Tuner Guide](https://www.infineon.com/row/public/documents/30/96/infineon-modustoolbox-capsense-tuner-guide-software-en-09018a9080890355.pdf). To start using this kit for 
your project, select the big sensor pad as a button element in the CAPSENSE configurator and use it with CSD configuration (no CSX). Then use the tuner to identify the signals and make them similar to 
the ones used in this project.

![](/Resources/image1.png)

The image above shows a recorded session in which the measurement surface is wet and finger presses are applied. The blue line represents the low-frequency and the green line the high-frequency 
measurement. It can be seen that the water presence is only detected in the low-frequency, while the finger presses are detectable at both frequencies. Once the recording is stopped, you can label 
the recorded data by choosing a predefined label and marking the desired area with your mouse.
For touch labels, it is best to align the labeled frame with the high-frequency signal, as this indicates actual finger contact with the surface, since the low-frequency signal also captures the 
finger's approach to the sensing area. We collected data for following scenarios:

- **Dry**: Nothing on the measurement surface
- **Wet**: Water covering the measurement surface
- **Touch**: Finger press on dry measurement surface
- **Wet_Touch**: Finger press on wet measurement surface
- **Noise_Dry**: Dry measurement surface with hand floating over it
- **Noise_Wet**: Wet measurement surface with hand floating over it

We recorded noise to make the model more robust. A recording session for the Noise_Dry case looked like this:
![](/Resources/image2.png)


## Adding More Data

In this project, we collect the data by using the Graph UX interface to create a simple data collection pipeline. The Graph UX file is located in the `Tools` folder. 
Connect the CY8CKIT-062S2-AI board or any other board with CAPSENSE&trade;, running the Streaming Protocol V2 firmware, to your PC and dragg it into the Graph UX window from the Node Explorer.

After that we insert our predefined labels over the Node explorer and name them Touch, Wet, Dry
and insert a Data Track to the Graph UX window to be able to record, label and store the data from the sensor.

![](/Resources/image3.png)

With that beeing done, we can start recording data by pressing the start button at the top toolbar.

After we pressed the start button we are connected to the board and can start the recording by pressing the record button. It is recommended to record small sessions of around 2 minutes to 
make it easier to distribute the recordings into the different sets (training, validation, test). For this project we collected in total 75 minutes of data and used a 60/20/20 train/validation/test
split.




## Model evaluation using live-data

To test the model in the DEEPCRAFT&trade; Studio we open the data collection project and drag the trained TensorFlow model file into the Graph UX window. We also drag a Label Track and Data Track 
into the Graph UX window for visualization.

`NOTE: Since the CAPSENSE data is an integer ADC count, we used a custom data convert unit from Int16 to Float32 to make the data compatible with the Studio model's training pipeline which requires float data type. The unit is located in the Tools folder.`

![](/Resources/image4.png)

Now we can press the `Start` button in the top toolbar to open the live session and press record to see the live labeling by the model predictions. 


## Steps to Production

The path to production strongly depends on the specific use-case and/or device where the model will run. Depending on that, the scenarios in which the model needs to work can be different, meaning that 
the relevant data useful for model improvement can change.

For instance, water/touch detection is affected by sensor's mounting which can be horizontal or even vertical. Also the size of the cpacitive surface can be different as well as the mounting location 
which can be indoor or outdoor with different water/humidity conditions. Collecting data from these scenarios and including them in model's training will make the model more robust and work reliably in different conditions.

Make also sure that you add more negative data like finger swipes, hand hovering, etc. Also if the model is expected to detect only water, record capacitive data using other liquids that can be 
present in the environment where the device will work and use those recordings to improve your model.

Collecting data from different CAPSENSE&trade; sensors is required to get a robust model that is able to detect water/touch despite the differences in the hardware and its tuning/calibration.

Keep in mind that it is important to test your model under the conditions relevant for your use-case as well as on additional ones to verify that it can generalize. Use data in the Test set to start 
with but run live model's testing as well to check its performance in real life.



## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
