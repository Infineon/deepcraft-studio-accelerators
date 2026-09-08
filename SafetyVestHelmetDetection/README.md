# Safety Vest Helmet Detection (Combined-PPE Data)

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Safety Vest Helmet Detection (Combined-PPE Data)** project detects safety vests and hard hats (with and without PPE) from live video input.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables real-time detection of safety vests and hard hats (with and without PPE) for applications such as construction-site safety monitoring and workplace PPE-compliance enforcement.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify safety vests and hard hats (with and without PPE) accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double click `.tflite` file, and it will generate a Graph Ux project to run.

## Contents

- **`Data`**: Contains data taken from Roboflow with safety vests and hard hats (with and without PPE) images: [PPE safety vest and hard hat datasets](https://universe.roboflow.com/search?q=construction%20site%20safety%20ppe%20object%20detection). Data consists of 6,310 sessions. Bounding-box counts per class: helmet 7,604, no_helmet 4,483, no_safety_vest 8,273, safety_vest 6,010.

	- ppe_site_dataset1	- 370 images from Roboflow (https://universe.roboflow.com/roboflow-universe-projects/construction-site-safety)
	- ppe_site_dataset2	- 1162 images from Roboflow (https://universe.roboflow.com/hssedemo/constuction-safety)
	- ppe_site_dataset3	- 189 images from Roboflow (https://universe.roboflow.com/construction-ppe-dataset/construction-safety-gears-vcbdq)
	- ppe_site_dataset4	- 2387 images from Roboflow (https://universe.roboflow.com/safety-object-detection-app/construction-site-safety-ccp7o)
	- ppe_site_dataset5	- 2202 images from Roboflow (https://universe.roboflow.com/fahim-shahriar-2frao/construction-site-safety-v5wfl)

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - This variant re-sources the data from **combined-PPE datasets** where helmet and vest presence/absence are labeled together in the same frame, avoiding the missing-label conflict that arises when single-purpose (vest-only / helmet-only) datasets are merged.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from trained job.
3. Double click the `.tflite` file and it will create a Graph Ux project.
4. Run the Graph UX project to evaluate model performance in real time using selected camera.
5. Put in front of the camera pictures with safety vests and hard hats (with and without PPE) and observe detection from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 6,310 sessions targeting safety vests and hard hats (with and without PPE).

Data sources and commercial-use conditions:

- `ppe_site_dataset1` (370 images, CC BY 4.0): https://universe.roboflow.com/roboflow-universe-projects/construction-site-safety
  - Combined construction-site scenes with hard hat and safety vest labels (present and absent), filtered to the four project classes on import.
- `ppe_site_dataset2` (1162 images, CC BY 4.0): https://universe.roboflow.com/hssedemo/constuction-safety
  - Combined construction PPE scenes labeling helmet/vest presence and absence in each frame.
- `ppe_site_dataset3` (189 images, CC BY 4.0): https://universe.roboflow.com/construction-ppe-dataset/construction-safety-gears-vcbdq
  - Combined construction PPE gear scenes with hard hat and safety vest labels (present and absent).
- `ppe_site_dataset4` (2387 images, CC BY 4.0): https://universe.roboflow.com/safety-object-detection-app/construction-site-safety-ccp7o
  - Combined construction-site scenes labeling hard hat and safety vest presence and absence in each frame (Hardhat/NO-Hardhat/Safety Vest/NO-Safety Vest).
- `ppe_site_dataset5` (2202 images, CC BY 4.0): https://universe.roboflow.com/fahim-shahriar-2frao/construction-site-safety-v5wfl
  - Large combined PPE dataset; head/vest protection classes mapped to helmet/safety_vest and their negatives. Imported prioritizing the under-represented no_helmet and no_safety_vest classes.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data if detection rate is low.** The starter dataset has 6,310 sessions from combined construction/industrial PPE scenes. Performance can drop on your target camera (fixed overhead view, wide-angle site camera, or low-resolution feed). Collect and label images from the actual deployment scene—same angle, distance, lighting, and PPE colors—and retrain.
- **Prefer fully-labeled frames.** Because every image here labels both helmet and vest (present and absent), the model gets consistent supervision. If you add more data, keep this property: label all four classes in each frame rather than mixing single-purpose datasets.
- **Watch small/distant boxes.** This project and data work well for boxes above ~10px at ImageSize 320; for smaller/more distant workers, add data with small labels and consider upgrading YOLO version or ImageSize.
- **Add negative data to reduce false positives.** Include workers in partial PPE, reflective jackets that are not vests (e.g. fireman coats), background clutter, and people-free scenes.
- **Tune advanced training settings for your compliance target.** Use the confidence threshold to trade off missed PPE violations vs. false alarms; adjust IoU threshold when workers overlap.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.

## Attribution & Citation

@misc{
construction-site-safety_dataset,
title = { Construction Site Safety Dataset },
type = { Open Source Dataset },
author = { Roboflow Universe Projects },
howpublished = { \url{ https://universe.roboflow.com/roboflow-universe-projects/construction-site-safety } },
url = { https://universe.roboflow.com/roboflow-universe-projects/construction-site-safety },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2022 },
month = { dec },
note = { visited on 2026-07-15 },
}


@misc{
constuction-safety_dataset,
title = { constuction-safety Dataset },
type = { Open Source Dataset },
author = { HSSEdemo },
howpublished = { \url{ https://universe.roboflow.com/hssedemo/constuction-safety } },
url = { https://universe.roboflow.com/hssedemo/constuction-safety },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { jul },
note = { visited on 2026-07-15 },
}


@misc{
construction-safety-gears-vcbdq_dataset,
title = { construction safety gears Dataset },
type = { Open Source Dataset },
author = { construction PPE dataset },
howpublished = { \url{ https://universe.roboflow.com/construction-ppe-dataset/construction-safety-gears-vcbdq } },
url = { https://universe.roboflow.com/construction-ppe-dataset/construction-safety-gears-vcbdq },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { jun },
note = { visited on 2026-07-15 },
}


@misc{
construction-site-safety-ccp7o_dataset,
title = { Construction Site Safety Dataset },
type = { Open Source Dataset },
author = { Safety Object Detection App },
howpublished = { \url{ https://universe.roboflow.com/safety-object-detection-app/construction-site-safety-ccp7o } },
url = { https://universe.roboflow.com/safety-object-detection-app/construction-site-safety-ccp7o },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { apr },
note = { visited on 2026-07-15 },
}


@misc{
construction-site-safety-v5wfl_dataset,
title = { Construction Site Safety Dataset },
type = { Open Source Dataset },
author = { Fahim Shahriar },
howpublished = { \url{ https://universe.roboflow.com/fahim-shahriar-2frao/construction-site-safety-v5wfl } },
url = { https://universe.roboflow.com/fahim-shahriar-2frao/construction-site-safety-v5wfl },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { nov },
note = { visited on 2026-07-15 },
}


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
