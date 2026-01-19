# Live Data Collection

## Overview

This starter project shows you how to collect and annotate audio data live. This can be done directly from your PC or from external edge devices attached over USB-serial. 

The same principle applies for other sensor data than audio data as well.

The graph that you see in the Main.imunit contains input/data source nodes representing the PC microphone and an edge device connected through the serial port.

By following this example, you will learn how to collect data and annotate it live, which will drastically reduce the time spent on collecting data.

## Concepts 

By opening the Main.imunit file you will see the graph which constitutes this starter project.
In this graph there are two data sources (serial and PC microphone).

There is also an output data track node in the graph, connected to the data source. This node will generate the data so that it can be saved and visualized.

There is also a 'Predefined Labels' node. The labels that are entered into this node will appear as label buttons/short cuts when running the graph to record data.

When running this graph you will get a session visualizing the audio data, containing a label track and label buttons which are used to label the data while recording.

After recording, you can play it back and/or save it to disk, to be used for later model training or evaluation.

## Trying it out

1. Open the Main.imunit file from the Solution Explorer.
2. Click the start-button (the play symbol) in the Main.imunit tab
3. Wait for the session to open 
4. Press the record button to start recording
5. Record the data you want your model to classify and label it while doing so using the label buttons 
6. You can play back the data to listen to it by clicking the play-button in the open session
7. Save the recording to disk using ctrl+s or the Save button
