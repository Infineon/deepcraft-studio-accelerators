# Live Model Evaluation 

## Overview

This starter project shows you how to evaluate a trained model for object detection from live streamed data.

In this example you will learn how to do this by streaming data from the local camera.

The graph that you see in the Main.imunit contains a model trained to detect hand gestures from the rock, paper, scissors game.

By following this example, you will learn how to test your own trained models live, to understand how they perform, and to analyse their behaviour, with the target of producing high quality models.

## Concepts 

By opening the Main.imunit file you will see the graph which constitutes this starter project.

In this graph there is a Local Camera input node that connects to a Video Track and also to the trained TFLite model.

The camera input connects to an Image Resize unit before connecting to the model, and then the output from the model connects to a Bounding Box Filter that fine-tunes the detection.

The Bounding Box Filter then connects to a Bounding Box Track to visualize the detection.

When running this graph you will observe bounding boxes with labels appropriate to your hand gestures. 

## Trying it out

1. Open the Main.imunit file from the Solution Explorer.
2. Click the start-button (the play symbol) in the Main.imunit tab
3. Wait for the session to open 
4. Click the record button to start the live evaluation session
5. Look at the video output, display different hand gestures to the camera, and observe the appropriate labeled bounding boxs. 

## Contents

`Models` - this folder contains a pretrained model for detecting the hand gestures from the rock, paper, scissors game.
