# Project Title

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

Describe here your project mentioning

- the problem you are trying to solve with Machine Learning
- the Machine Learning method used in the project
- the sensor you want to use and the corresponding type of data
- the reason(s) why solving this problem is relevant, which practical applications/products would benefit from it

## Contents

`Data` 	- Folder to put your data. Add a short description

`Models` - Folder where trained models, their predictions and generated Edge code are saved. Add a short description

`PreprocessorTrack`	- Folder where pre-processed data is stored. Add a short description

`Resources`	- Folder where all extra resources/files should be placed. Add a short description

`Tools`	- Folder where all extra tools and scripts belonging to the project should be placed. Add a short description

`Units`	- Folder where custom layers and pre-processors can be added. Add a short description

## Sensor(s) & Data

Describe here data, sensor and/or device settings specifications and/or data collection (high level).

Make sure to specify the data attribution, specifying under which conditions the data can be used for commercial purposes.


## Adding More Data

Describe here how to expand the dataset of the project using Infineon boards, Studio Graph UX, and/or other tools to collect data and/or other data sources

Describe briefly how to label the new data, focusing on Studio capabilities (manual labeling and model assisted) or add and describe a script used to label the data automatically

## Steps to Production

Describe here the main steps to bring this specific project and trained model to production level, focusing on how to solve the issues which are relevant to this project.

Some points to highlight:

- increase data variability: data from different environments, devices, conditions, use cases, people, patterns. Mention in case how to use Data Augmentation functionality for audio data
- make sure Test set contains data that is not used in Train and Validation sets and that allows you to verify that model generalizes to different scenarios
- make sure to add negative data to increase model robustness


## Attributions & Citations

Credit every third-party dataset, recording, or other source used in this project. Include the license (and any commercial-use limits), a link to the original source, and enough detail that a reader can find the exact version you used. Repeat one citation block per source.

If the data was collected within Infineon / DEEPCRAFT™ (this accelerator, an evaluation kit, Graph UX, or another internal recording), say so in plain text: what was recorded, with which sensor or board, and that use is subject to the DEEPCRAFT™ Studio Terms and Conditions. Do not invent a BibTeX entry for that data.

Example:

Data in this project was collected for the accelerator using a [board or sensor] for [what was recorded]. Usage is subject to the [DEEPCRAFT™ Studio Terms and Conditions](https://developer.imagimob.com/legal/studio-terms-and-conditions).

Use BibTeX when a formal citation is available for a third-party source; otherwise list author, title, URL, license, and access date in plain text.

```bibtex
@misc{dataset_key,
  title = {Dataset Title},
  author = {Author or Organization},
  year = {YYYY},
  howpublished = {\url{https://example.com/path/to/dataset}},
  note = {License: CC BY 4.0 (replace with the actual license). Accessed YYYY-MM-DD.},
}
```


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get started quickly.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Help & Support

If you need support or if you want to know how to deploy the model onto the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
