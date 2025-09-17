# Live Model Evaluation 

## Overview

This starter project shows you how to evaluate a trained model for object detection from live streamed data.

In this example you will learn how to do this by streaming data from the local camera.

The graph that you see in the Main.imunit don't have a model, plese put your model path in the unit config.

By following this example, you will learn how to test your own trained models live, to understand how they perform, and to analyse their behaviour, with the target of producing high quality models.

## Concepts 

In this graph there is a Local Camera input node that connects to a Video Track.

The camera input connects to an Image Resize unit before connecting to the model, and then the output from the model connects to a Bounding Box Filter that fine-tunes the detection.

The Bounding Box Filter then connects to a Bounding Box Track to visualize the detection.

When running this graph you will observe bounding boxes with labels appropriate to your hand gestures. 

## Trying it out

1. Open the Main.imunit file from the Solution Explorer.
2. Add your model path and arena size in model unit box.
3. Click the start-button (the play symbol) in the Main.imunit tab
4. Wait for the session to open 
5. Click the record button to start the live evaluation session
6. Look at the video output, display different hand gestures to the camera, and observe the appropriate labeled bounding boxs. 
 