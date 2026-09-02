# Cat Dog Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Cat Dog Detection** project builds a robust end-to-end system that identifies cats and dogs from live video input.

The object detection model is YOLO-based and it can be used in applications for

- **Pet monitoring:** Detect cats and dogs in home or garden cameras
- **Smart home automation:** Trigger actions when pets are detected

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables pet monitoring and smart-home automation from live camera feeds.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify cats and dogs accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double click `.tflite` file, and it will generate a Graph Ux project to run.

## Contents

- **`Data`**: Contains data taken from Roboflow with cats and dogs images: [Cat dog datasets](https://universe.roboflow.com/search?q=cat%20dog%20object%20detection). Data consists of 3,090 annotated sessions (2,377 cat, 1,063 dog bounding boxes).

	- catdog_dataset1	- 649 images from Roboflow (https://universe.roboflow.com/cats-and-dogs-detection/object-detection-cat-and-dogs)
	- catdog_dataset2	- 200 images from Roboflow (https://universe.roboflow.com/boram-prebk/230518_catdog-d8fif)
	- catdog_dataset3	- 1141 images from Roboflow (https://universe.roboflow.com/personal-buhbs/dogs-vs-cats)
	- catdog_dataset4	- 1100 images from Roboflow (https://universe.roboflow.com/mohamed-traore-2ekkp/cats-n9b87)

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv` and `rename_mapping.json` which map the current session image names back to their original Roboflow source filenames.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from trained job.
3. Double click the `.tflite` file and it will create a Graph Ux project.
4. Run the Graph UX project to evaluate model performance in real time using selected camera.
5. Put in front of the camera pictures with cats and dogs and observe detection from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT™ Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 3,090 sessions targeting cats and dogs.

Data sources and commercial-use conditions:

- `catdog_dataset1` (649 images, CC BY 4.0): https://universe.roboflow.com/cats-and-dogs-detection/object-detection-cat-and-dogs
- `catdog_dataset2` (200 images, CC BY 4.0): https://universe.roboflow.com/boram-prebk/230518_catdog-d8fif
- `catdog_dataset3` (1141 images, CC BY 4.0): https://universe.roboflow.com/personal-buhbs/dogs-vs-cats
  - Replaced pet-detect-pbkw9; full-body cat and dog boxes (median area ~0.63).
- `catdog_dataset4` (1100 images, CC BY 4.0): https://universe.roboflow.com/mohamed-traore-2ekkp/cats-n9b87
  - Derived from the Oxford-IIIT Pet Dataset (upstream CC BY-SA 4.0); the Roboflow export used here is CC BY 4.0.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data if detection rate is low.** The starter dataset has 3,090 sessions across indoor, outdoor, and mixed lighting conditions, but performance can drop on your target camera (for example, a fixed garden view, doorbell camera, or low-resolution feed). Collect and label images from the actual deployment scene—same angle, distance, and lighting—and retrain until cats and dogs are detected reliably in that environment.
- **Add more classes if needed.** The project currently detects `cat` and `dog` only. If your product must distinguish breeds, separate indoor/outdoor pets, or treat all pets as one trigger, add new classes and label accordingly before retraining.
- **Add negative data to reduce false positives.** Include images without pets and common look-alikes (stuffed animals, pet photos on screens, wildlife) so the model learns not to alarm on non-target objects.
- **Try different augmentation settings to match real-world variability.** Increase flip left/right and flip up/down; adjust brightness and exposure for day/night and indoor/outdoor transitions.
- **Tune advanced training settings for your sensitivity target.** Use confidence and IoU thresholds to trade off missed detections vs. false alarms.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.

## Attribution & Citation

@misc{
object-detection-cat-and-dogs_dataset,
title = { Object Detection Cat and Dogs Dataset },
type = { Open Source Dataset },
author = { Cats and Dogs Detection },
howpublished = { \url{ https://universe.roboflow.com/cats-and-dogs-detection/object-detection-cat-and-dogs } },
url = { https://universe.roboflow.com/cats-and-dogs-detection/object-detection-cat-and-dogs },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { sep },
note = { visited on 2026-07-07 },
}


@misc{
230518_catdog-d8fif_dataset,
title = { 230518_catdog Dataset },
type = { Open Source Dataset },
author = { BORAM },
howpublished = { \url{ https://universe.roboflow.com/boram-prebk/230518_catdog-d8fif } },
url = { https://universe.roboflow.com/boram-prebk/230518_catdog-d8fif },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { may },
note = { visited on 2026-07-07 },
}


@misc{
dogs-vs-cats_dataset,
title = { Dogs vs Cats Dataset },
type = { Open Source Dataset },
author = { personal },
howpublished = { \url{ https://universe.roboflow.com/personal-buhbs/dogs-vs-cats } },
url = { https://universe.roboflow.com/personal-buhbs/dogs-vs-cats },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2022 },
month = { aug },
note = { visited on 2026-07-07 },
}


@misc{
cats-n9b87_dataset,
title = { Cats Dataset },
type = { Open Source Dataset },
author = { Mohamed Traore },
howpublished = { \url{ https://universe.roboflow.com/mohamed-traore-2ekkp/cats-n9b87 } },
url = { https://universe.roboflow.com/mohamed-traore-2ekkp/cats-n9b87 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2022 },
month = { nov },
note = { visited on 2026-07-07 },
}


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
