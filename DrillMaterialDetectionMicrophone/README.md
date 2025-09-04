# Drill Material Detection w/ Audio

## Overview

This is a starter model that is capable of classifying the material a power drill is drilling into based on the audio signature and is imagined to be incorporated into smart power tools. 
A similar model was developed using the IMU data instead, if that is more fitting to your use case. 
It is developed as a proof of concept and is not fully optimized, achieving around an 85% plastic/wood accuracy.
Furthermore, the current project only differentiates between wood, plastic, and air but is easily scalable to include more labels. 
The preprocessor and model architectures can be used not only for a drill but for any number of motor-based projects where there is a variability in the audio signature based on the desired classification labels.

## Collection of Data
The data was collected from the built-in microphone on the AI-Eval kit (CY8CKIT-062S2-AI) taped to the left top side of a drill and streamed directly into DEEPCRAFT Studio at 16000Hz. 
The drilling was mainly done straight down into an 11mm thick plank of wood and a 3mm thick piece of acrylic plastic, with around 5% of the data being horizontal drilling. Not every hole was made all the way through the material in order to have data for such cases.
Apart from drilling into air, wood, and plastic, the drill was moved around in order to create an invariance to general movement.
There are additional labels for the moment of removing the drill from the material, called wood_out and plastic_out. Further thought towards the necessity of these labels is recommended; it might be better to just train a model that classifies this as regular wood and plastic. 

## Adding More Data
In order to add more data-be it similar, from another type of drill, or another material entirely-you simply need to attach an AI-eval kit (purchasable here: https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/) to a drill and stream the audio data of drilling into DEEPCRAFT Studio and then label it appropriately. 
It is recommended to have a minimum of 100 seconds of data per label, preferably more.

## Steps to Production
The recommended path to production for this starter model is to identify which materials you want to differentiate from, which drill types you want this to work on, and which conditions your application will be placed in.
It is unlikely that keeping non-matching existing data worsens the model so long as your application isn't wildly different.
After obtaining the appropriate machines and materials, you should perform data collection as outlined above, making sure to collect data including all eventualities you want invariance to. 
For example, if you want a model that classifies when a drill is entering a new material, you will want to collect data on many different material combinations, using many different types of drills, held by many different people, in many different settings. 
When all the data collection is done, the preprocessing and model parameters should be optimized and refined to your use case, with size considerations based on your final deployment location.
After evaluating the model, you might realize that your model performs poorly in certain situations; there are no set solutions for this, but adding representative data could help.
## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.