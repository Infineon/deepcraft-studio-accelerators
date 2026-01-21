# Live Model Evaluation 

## Overview

This starter project shows you how to evaluate trained models live from streamed data.

In this example you will learn how to do this by streaming data from the PC microphone or through an external edge device, with a built-in microphone, attached over USB-serial.

The graph that you see in the Main.imunit contains a model trained to detect the spoken words 'up' and 'down', by listening to data recorded through a microphone.

By following this example, you will learn how to test your own trained models live, to understand how they perform, and to analyse their behaviour, with the target of producing high quality models.

## Concepts 

By opening the Main.imunit file you will see the graph which constitutes this starter project.
In this graph there are two data sources/input nodes (Local Microphone and Serial Capture), connected to a trained model. 

The trained model is divided into two nodes, a preprocessor and the model (neural network).

There are also a couple of visualization/output nodes in the graph.

Two tracks (a label and a data track) connected directly to the model output.

There is also a data track inside the preprocessor node, outputting and visualizing the spectrograms generated from the audio data which are later classified/analyzed by the model. You can see this data track node by opening the preprocessor node (by double-clicking on it in the canvas).

When running this graph you will get a session visualizing the preprocessed audio data and the model output on this data both as raw values (a plot) and as labels. 

## Trying it out

1. Open the Main.imunit file from the Solution Explorer.
2. Click the start-button (the play symbol) in the Main.imunit tab
3. Wait for the session to open 
4. Click the record button to start the live evaluation session
5. Look at the plots showing the model's predictions on the data and the audio spectrograms
6. These visualizations show you how the model and the preprocessor performs and is valuable information that can be used to tune your preprocessing, models and data collection processes.

## Contents

`Models` - this folder contains a pretrained model for detecting the spoken words 'up' and 'down'.
