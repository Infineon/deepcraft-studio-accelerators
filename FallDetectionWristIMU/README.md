# Fall Detection (Wrist-worn)

## Overview - Use-Case

This project allows you to build models that detect falls in less active individuals, such as elderly people, using a 3-axis accelerometer worn on the wrist. It uses Classification to distinguish a fall from everyday activity, and pairs the model with a stillness-based post-processing gate that confirms a fall after a period of inactivity, reducing false positives.

Reliable wrist-worn fall detection is relevant to wearables, safety monitoring, and healthcare products aimed at helping less active or elderly users get timely assistance after a fall.

## Contents

`Data` - Folder where data is located. Contains wrist-worn accelerometer recordings organized by anonymized source, batch, class (Fall / NonFall), and session.

`Models` - Folder where trained models, their predictions and generated Edge code are saved.

`Tools` - Folder containing the `CodeGenGraphUX` Graph UX project used for code generation, including feature extraction and the stillness-based post-processing gate. The custom units (`Tools/CodeGenGraphUX/Units`) live inside this Graph UX project rather than a top-level `Units` folder, since Graph UX resolves unit paths relative to its own project.

## Sensor(s) & Data

The accelerometer needs to be set up to collect data at 50 Hz, using a +/- 8g scale with 12- or 16-bit resolution. Input values must be expressed in g.

The provided data consists of wrist-worn accelerometer recordings of simulated falls and everyday non-fall activities collected by Imagimob AB and project partners. Dataset identities and session identifiers have been anonymized. Data is licensed under the [DEEPCRAFT™ Studio Terms and Conditions](https://developer.imagimob.com/legal/studio-terms-and-conditions).

## Adding More Data

To collect more data you can utilize the PSOC™ 6 AI Evaluation Kit and the [streaming protocol](https://developer.imagimob.com/data-preparation/data-collection/collect-data-using-graph-ux) to stream data directly into DEEPCRAFT™ Studio and add it to this project.

New sessions can be labeled directly in Studio, using either manual labeling or model-assisted labeling.

## Steps to Production

To take this project to production you should do the following:

- Increase data variability: add data from different age groups, fall types, environments, and devices.
- Add negative data of people going about their everyday lives (walking, running, sitting, sports, etc.) to increase model robustness and teach the model what is not a fall.
- Make sure the Test set contains data not used in Train and Validation, so you can verify the model generalizes to different wearers and scenarios.
- Validate sensor orientation against the coordinate system used during data collection; incorrect axis orientation can reduce model performance.
ist.csv

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Stu
