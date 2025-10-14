# Gunshot Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview

This is a starter model for detecting gunshots in a noisy environment, quite far along in its development. The model includes strong invariance to many different background noises with around 1 hour of microphone data.
It is presented here with the purpose of being supplemented with a significant amount of gunshot data, without having to worry as much about recording and adding background noise data. 

## Collection of Data
The data was collected by downloading Creative Commons licensed audio files from freesounds.org.

## Adding More Data
In order to add more data, you need to upload 48000 Hz audio files with appropriate labels. This could be done either by finding more data online or recording audio using a microphone, such as the AI Evaluation Kit (https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/). 
Regardless of how the data is obtained, it can be labelled in DEEPCRAFT Studio.
The primary goal should be to add more gunshot audio files, since the existing dataset is lacking in that regard.
The practical and legal concerns for collecting gunshot data are unfortunately unavoidable and outside of our expertise to advise on; however, they are likely necessary to produce a production-ready model.

## Steps to Production
The recommended path to production begins with identifying the use case and tailoring this starter model to that need. 
This involves identifying the intended environment since a model trained on indoor ballistics will have a different performance than one trained in a field or in the woods. 
The most important step is adding relevant gunshot data to the model, after which the details of how the model can be tested need to be tackled. Due to the nature of this model, there is a large gap between creating a proof of concept and implementing an actual production-ready model.
When testing the model, it is possible that gunshot sounds played through a speaker will not be detected, but real gunshots will. This is desired for most applications but an annoyance in testing and demoing of the model. 
To deal with this, it is recommended to branch off and create a new 'demo' model that has been supplemented with data of gunshot sounds played through a speaker. 

## Potential Actions
possibly remove far away gunshots:
417345__inspectorj__gunshot-distant-a

might trim out automatic fire from:
402791__acidsnowflake__ak47

## Data Attributions
forest car people NL Roond 01 200619_0186.wav by klankbeeld -- https://freesound.org/s/623090/ -- License: Attribution 4.0
forest summer Roond 005 200619_0186.wav by klankbeeld -- https://freesound.org/s/524238/ -- License: Attribution 4.0

Heavy Rain by lebaston100 -- https://freesound.org/s/243627/ -- License: Attribution 4.0
Heavy Rain by lebaston100 -- https://freesound.org/s/243629/ -- License: Attribution 4.0
Heavy Rain by lebaston100 -- https://freesound.org/s/243628/ -- License: Attribution 4.0
Rain without thunder by lebaston100 -- https://freesound.org/s/346562/ -- License: Attribution 4.0
Heavy Rain with Thunder by lebaston100 -- https://freesound.org/s/243626/ -- License: Attribution 4.0

Wind Through Trees 3b by spoonbender -- https://freesound.org/s/244942/ -- License: Attribution 4.0

Rain, Moderate, B.wav by InspectorJ -- https://freesound.org/s/401276/ -- License: Attribution 4.0

20180313.forest.ambiance.wav by dobroide -- https://freesound.org/s/421955/ -- License: Attribution 4.0

City Park - A conversation between two ladies.wav by dibko -- https://freesound.org/s/624244/ -- License: Attribution 4.0

The rain falls against the parasol by straget -- https://freesound.org/s/531947/ -- License: Attribution 4.0

Construction, Jackhammer Manual, A.wav by InspectorJ -- https://freesound.org/s/417281/ -- License: Attribution 4.0
Construction, Jackhammer Excavator, A.wav by InspectorJ -- https://freesound.org/s/400991/ -- License: Attribution 4.0

ATV.mp3 by monkeyman535 -- https://freesound.org/s/324331/ -- License: Attribution 4.0

lift truck by trouby -- https://freesound.org/s/362978/ -- License: Attribution 4.0

Maxim Russian machinegun very near by poissonmort -- https://freesound.org/s/160772/ -- License: Attribution 4.0

Gun Shots - Pistols by Hitrison -- https://freesound.org/s/223105/ -- License: Attribution 4.0

M1911_Outdoor_Echo.mp3 by MaxWiley -- https://freesound.org/s/249883/ -- License: Attribution 3.0

Gunshot, Distant, A.wav by InspectorJ -- https://freesound.org/s/417345/ -- License: Attribution 4.0

Other sounds may also be used as can be seen from our master attribution list here https://github.com/Infineon/deepcraft-studio-accelerators/blob/main/AttributionLists/Freesound_Attribution_List.csv

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
