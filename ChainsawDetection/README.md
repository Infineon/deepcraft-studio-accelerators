# Chainsaw Detection

## Overview
This is a starter model that classifies if there is an actively cutting chainsaw in the vicinity; chainsaws that are stalling are defined as not cutting. 
A fully developed model could be used to detect illegal logging or create automatic warning systems. 

## Collection of Data
The majority of data for this model was collected with various microphones and proximities by cutting and stalling chainsaws in a small forest. This data was supplemented by data from freesounds.org in order to add background noise and additional chainsaw sounds.
Specifically, various forest background noises were added.
There is limited variety in the types of wood cut due to the collection being in the same forest.
The data was collected at 16000Hz, and the project contains around 700 minutes of data, with 50 of those being data during cutting. 
After a preliminary evaluation, the model performed very poorly on chainsaw audio played through a speaker, making it harder to demo. As such, additional data was collected by playing chainsaw audio through a variety of speakers to supplement the dataset, after which it significantly improved on sounds played through speakers.

## Adding More Data
Adding more background noise data can be done online or by collecting microphone data of a suitable environment (i.e., forest, construction site, river). This can then be imported into the studio project.
Adding more chainsaw data ought to be done through a thorough collection. Adding variation of different types of chainsaws, different types of trees, and varying the distance from the microphone is strongly recommended, with the distances being most important. 

## Steps to Production
The first step is to identify the use-case, hardware and location of your desired chainsaw detection model and modifying the existing project to account for that. For example, if your microphone is to be encased to protect it from rain, applying data augmentation on the existing data is likely benefitial.
Next, collect more data as outlined above with background noise tailored to your use case.
It is recommended to apply some amount of post processing to reduce false positives. Since chainsaws involved in illegal logging are not active for just a short number of seconds, a models false positive rate can be reduced by for example temporal smoothing.

## Attributions
Chainsaw Start Attempts.wav by lonemonk -- https://freesound.org/s/185580/ -- License: Attribution 3.0
Construction, Jackhammer Excavator, A.wav by InspectorJ -- https://freesound.org/s/400991/ -- License: Attribution 4.0
atmosphere tokyo construction.wav by IsraGallo -- https://freesound.org/s/513672/ -- License: Attribution 4.0
20180313.forest.ambiance.wav by dobroide -- https://freesound.org/s/421955/ -- License: Attribution 4.0
forest summer Roond 005 200619_0186.wav by klankbeeld -- https://freesound.org/s/524238/ -- License: Attribution 4.0
forest car people NL Roond 01 200619_0186.wav by klankbeeld -- https://freesound.org/s/623090/ -- License: Attribution 4.0
Chainsaw, Moderately Distant, A.wav by InspectorJ -- https://freesound.org/s/418042/ -- License: Attribution 4.0
Chainsaw trimming trees with street noise by Morphic__ -- https://freesound.org/s/541277/ -- License: Attribution 4.0
crowd_of_people_in_a_hall.wav by kwahmah_02 -- https://freesound.org/s/254810/ -- License: Attribution 3.0
People, Crowd Talking Chatting by FreeToUseSounds -- https://freesound.org/s/414307/ -- License: Attribution 3.0
## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.