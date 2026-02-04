# Modell Evaluation with manual offset using DEEPCRAFT Studio

## Overview

You can test your ML model as usual using the PSoC, or run it directly on your PC with Deepcraft. To improve this workflow you can use this `Main.imunit`file.
In the graphical chart, you can independently adjust the offset of each stream (temperature and pressure) using numeric values. Make sure to use this feature: ambient pressure can change even within minutes, and small adjustments to this parameter can significantly improve your model’s performance. Also note that the PSoC may heat up due to insufficient cooling. You can compensate for this, for example by applying a negative value to the temperature offset.
To change the offset of a given stream, simply click the gray box and, under “constant” (pink), left-click the right input field to set the value as desired.

For more Information please read the main README file.

### Trying it out

1. Open the Main.imunit file from the Solution Explorer.
2. Click the start-button (the play symbol) in the Main.imunit tab
3. Wait for the session to open 
4. Press the record button to start testing.

### Getting Started

For more Information please read the main README file.
Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

### Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.