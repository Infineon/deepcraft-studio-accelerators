# Car Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio).

## Overview - Use-Case

This Studio Accelerator provides general guidance on how to develop a Computer Vision project for car detection with an RGB camera.

The task is framed as an object detection project: a type of Computer Vision task with the goal of classifying and locating objects in the image frame. For this project, one class is used: `car`.

The object detection model is YOLO-based and it can be used in applications for

- **Traffic and parking monitoring:** Detect cars in parking lots, roads, or indoor spaces
- **Robotics and vehicles:** Detect cars from a camera mounted on a robot or a vehicle
- **Prototyping vision products:** Start from a ready object-detection pipeline and adapt it to a specific environment

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT™ Studio (YOLOv5n legacy in this starter)
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables car detection and counting workflows from camera feeds, with a path from prototype data to on-device inference

### How can I know if this project fits my use case?

You can use this starter project if:

- You need to build a Computer Vision project for detecting or counting cars in a specific environment;
- You have the possibility of collecting additional data, either from the real world or via simulated environments.

If you cannot collect a sufficient amount of representative data, this project might not provide accurate results.

### How can this project ease my go-to-production journey?

This project demonstrates how to approach the task from a Computer Vision perspective. If you start from this project, you will have:

- A ready framework for performing Object Detection (YOLO-based);
- Some data already collected and ready to be used;
- Data augmentation and model training parameters already set;
- An easy pipeline allowing you to collect or import more data as needed.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect cars accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double click `.tflite` file, and it will generate a Graph UX project to run.

## Contents

- **`Data`**: Folder for your data. This project contains **3,274** annotated object-detection sessions (JPG + `LabelXml`), using a single target class (`car`):
	- `img*` — 1,400 images from Roboflow ([Car Detection Model](https://app.roboflow.com/lolepls/car-detection-model-bwjpb-92kbi/train))
	- `pc*` — 1,771 images from Roboflow ([Car Detection](https://app.roboflow.com/lolepls/car-detection-5fc7i-vtlqe/train))
	- `20260218_*` — 103 images collected by Infineon on a small toy-car demo setup
- **`Models`**: Folder where trained models, their predictions, quantized versions, and generated Edge code are saved.
- **`Tools`**: Folder containing additional tools. `Tools/rename_dataset.py` shortens image file names in a Roboflow/COCO export before you import the data into Studio (see [Renaming a COCO export](#renaming-a-coco-export)).

## Steps to get started: Model Training and Evaluation

1. Open `CarDetection.improj` in DEEPCRAFT™ Studio.
2. Train the YOLO-based model using the provided dataset or custom data (or inspect the included trained model under `Models/`).
3. Download the trained model `.tflite` file from the trained job.
4. Double-click the `.tflite` file; it will create a Graph UX project.
5. Run the Graph UX project to evaluate model performance in real time using the selected camera.
6. Put pictures of cars in front of the camera (laptop or phone screen), or use toy cars, and observe detection from the live camera.

## Sensor(s) & Data

This accelerator is based on RGB images of cars from three sources: 2 public datasets from Roboflow and a dataset collected at Infineon.

Image data is stored as DEEPCRAFT™ Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 3,274 sessions targeting cars.

The `.improj` already defines train, validation, and test splits. Keep the test set independent of train and validation when you add your own data.

Data sources:

- Roboflow Car Detection Model (`img*` sessions): https://app.roboflow.com/lolepls/car-detection-model-bwjpb-92kbi/train
- Roboflow Car Detection (`pc*` sessions): https://app.roboflow.com/lolepls/car-detection-5fc7i-vtlqe/train
- Infineon toy-car demo setup (`20260218_*` sessions)

Public web photos and a tabletop toy-car setup will not automatically transfer to parking lots, roads, or a different camera. Collect data in the target environment before expecting production-level accuracy.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use the `Object Detection Data Collection Graph UX` template (Studio live data collection for Computer Vision projects) to collect and label new data in real time with a camera.
2. Import data to your project and retrain to get an updated model.

Having some cars available is optional, but you may need them to test the model and collect additional data. If you want to test the project out of the box, you can also show the camera pictures of cars on your laptop screen or phone, or use toy cars.

You can also import a dataset collected with other means. If you want to import data collected externally, for example with a mobile phone or a camera in the field, please refer to [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT™ Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`).

Hint: if you collect data with a mobile phone or another camera, try to set the camera to provide square images. This will make image processing easier and avoid unwanted stretching.

### Renaming a COCO export

Roboflow and other COCO exports often use long or hashed image file names. `Tools/rename_dataset.py` renames those files to short, sequential names and keeps the annotations in sync. In this project, the Roboflow Car Detection Model export was renamed with prefix `img` and the Roboflow Car Detection export with prefix `pc` (`img0001.jpg`, `pc00001.jpg`, …).

The script does **not** operate on the Studio `Data/` folder (those are already per-session JPG + `LabelXml` files). Use it on a COCO dataset **before** import: a folder that contains split subfolders such as `train`, `valid`, and/or `test`, each with images and an `_annotations.coco.json` file.

For every split it finds, the script:

1. Reads `_annotations.coco.json` and sorts images by their COCO `id` so the order is stable.
2. Maps each `file_name` to `{prefix}{number}{extension}`, keeping the original extension (`.jpg`, `.png`, …). Zero-padding is at least 3 digits, or wider if the dataset has 1000+ images, so names sort correctly (`img001`, `img010`, `img100`).
3. Renames files on disk in two steps (temporary `.rntmp` names first) so existing files are not overwritten if a target name already exists.
4. Writes the new names back into `_annotations.coco.json` (`file_name`, and `extra.name` when that field is present). Bounding boxes and image ids are left unchanged.

By default a **single counter runs across all splits**, so names stay unique (for example train ends at `img800` and valid starts at `img801`). That matches how this project's `img*` and `pc*` folders are numbered.

Run it from the dataset root (the parent of the split folders), or pass `--root`:

```bash
python Tools/rename_dataset.py img --root path/to/coco_dataset
```

Useful options:

- `--dry-run` — print `old -> new` mappings without renaming anything. Use this first.
- `--per-split` — restart numbering from 1 in each split folder instead of one continuous counter.
- `--root` — dataset root if you are not already in that directory.

If an image is listed in the JSON but missing on disk, the script warns and still updates the annotation entry. It exits with an error if no split folders with `_annotations.coco.json` are found.

## Steps to Production

To bring this project to a production-level system, follow these general steps:

1. Identify the environment or setting where you want this model to operate. Define whether the camera will be fixed, mounted on a robot, installed on a vehicle, or used to monitor parking lots, roads, indoor spaces, or other scenarios.

2. Collect data for a prototype application.

Collect a representative amount of data in a setting as close as possible to the final setup, to fine-tune the model to specific angles, light conditions, and scene details. If detection accuracy is low or the model is confused, add negative examples to improve performance when cars are not present.

3. Import your data and train the prototype model.

Import the data you collected in DEEPCRAFT™ Studio. You can then follow the standard DEEPCRAFT™ Studio steps for processing, training, and deploying your Computer Vision model.

4. Deploy and do a real-time test of your prototype model.

The last step in the prototyping phase is to deploy the model to the device by leveraging the template application already available in ModusToolbox: [MTB Example ML Imagimob MTBML Deploy](https://github.com/Infineon/mtb-example-ml-imagimob-mtbml-deploy). Deploy and test the firmware on the hardware. The display will show real-time detection bounding boxes.

5. Move to the production board system.

The final production setup will likely place the camera in a different position than the prototyping phase. If you can get as close as possible to production conditions during prototyping, you will be able to reuse the same model on the production board with little to no additional training or data. If not, you may need a new data collection step to capture the nuances of the final setup. Repeat steps 2, 3, and 4 for the production setup to reach a functioning application.

Note: All subsequent ML system lifetime monitoring procedures must be defined and implemented by you according to your needs, requirements, and targets.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT™ Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.


## Attribution & Citation


@misc{car-detection-model-bwjpb-92kbi,
  title = {Car Detection Model Dataset},
  type = {Open Source Dataset},
  author = {lolepls},
  howpublished = {\url{https://app.roboflow.com/lolepls/car-detection-model-bwjpb-92kbi/train}},
  url = {https://app.roboflow.com/lolepls/car-detection-model-bwjpb-92kbi/train},
  journal = {Roboflow Universe},
  publisher = {Roboflow},
  year = {2026},
  month = {jul},
  note = {visited on 2026-07-21; used for img* sessions},
}

@misc{car-detection-5fc7i-vtlqe,
  title = {Car Detection Dataset},
  type = {Open Source Dataset},
  author = {lolepls},
  howpublished = {\url{https://app.roboflow.com/lolepls/car-detection-5fc7i-vtlqe/train}},
  url = {https://app.roboflow.com/lolepls/car-detection-5fc7i-vtlqe/train},
  journal = {Roboflow Universe},
  publisher = {Roboflow},
  year = {2026},
  month = {jul},
  note = {visited on 2026-07-21; used for pc* sessions},
}


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get started quickly.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Help & Support

If you need support or if you want to know how to deploy the model on the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
