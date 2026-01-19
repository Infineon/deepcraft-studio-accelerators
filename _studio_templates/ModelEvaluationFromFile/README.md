# Model evaluation from file

## Overview

This starter project shows you how to evaluate trained models on recorded data. 
The graph that you see in the Main.imunit contains a model trained to detect different modes of operations of a hairdryer, by listening to data recorded through a microphone.

By following this example, you will learn how to test your own trained models on recorded data, to understand how they perform, and to analyse their behaviour, with the target of producing high quality models.

## Concepts 

By opening the Main.imunit file you will see the graph which constitutes this starter project.
In this graph there is a data source (audio data stored on disk), connected to a trained model.

There are also a couple of visualization/output nodes in the graph.

One data track, outputting and visualizing the raw audio stream from the file.

And two tracks (a label and a data track) connected directly to the model output.

When running this graph you will get a session visualizing the audio data and the model output on this data both as raw values (a plot) and as labels. 

## Trying it out

1. Open the file Main.imunit from the Solution Explorer.
2. Click the start-button (the play symbol) in the Main.imunit tab
3. Wait for the session to open 
4. Look at the plots showing the model's predictions on the data
5. You can play back the data to listen to it by clicking the play-button in the open session
6. Drag in and connect the other audio recording and repeat to analyze the results on this file

## Contents

`Models` - this folder contains a pretrained model for detecting the mode of operation of a hairdryer from microphone input. 
