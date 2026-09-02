# Emergency Vehicle Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Emergency Vehicle Detection** project detects ambulances, fire trucks, and police cars from live video input.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Detecting emergency vehicles in real time lets autonomous systems and smart-city infrastructure yield right-of-way, clear intersections, and prioritize ambulances, fire trucks, and police cars, improving road safety and emergency response times.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify ambulances, fire trucks, and police cars accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double click `.tflite` file, and it will generate a Graph Ux project to run.

## Contents

- **`Data`**: Contains data taken from Roboflow with ambulances, fire trucks, and police cars images: [Self-driving emergency vehicle datasets](https://universe.roboflow.com/search?q=like-tag%3Aself-driving+emergency). Data consists of 3,510 sessions with balanced classes (ambulance 1287, fire_truck 816, police_car 1514).

	- emerg_dataset1	- 495 images from Roboflow (https://universe.roboflow.com/fyp-traffic-management-system/ambulances-23fqp)
	- emerg_dataset2	- 200 images from Roboflow (https://universe.roboflow.com/gezamelijke-brandweer/cameramodel)
	- emerg_dataset3	- 711 images from Roboflow (https://universe.roboflow.com/yolov8-etfar/emergency-vehicles-detection-xockh-af7sr-kvfuf)
	- emerg_dataset4	- 317 images from Roboflow (https://universe.roboflow.com/national-school-of-applied-science-zh1i1/nn-ln8ka)
	- emerg_dataset5	- 432 images from Roboflow (https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania)
	- emerg_dataset6	- 304 images from Roboflow (https://universe.roboflow.com/fyp-tc-idn2o/police-cars-sumfm)
	- emerg_dataset7	- 597 images from Roboflow (https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania)
	- emerg_dataset8	- 235 images from Roboflow (https://universe.roboflow.com/smartire/veicoliemergenza)
	- emerg_dataset9	- 57 images from Roboflow (https://universe.roboflow.com/erknnung/polizei-bkn68)
	- emerg_dataset10	- 53 images from Roboflow (https://universe.roboflow.com/smartire/emergencyvehicledetection-wuasv)
	- emerg_dataset11	- 109 images from Roboflow (https://universe.roboflow.com/central-university/firetruck2)

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv` and `rename_mapping.json`, which map each imported session filename back to its original Roboflow export filename.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from trained job.
3. Double click the `.tflite` file and it will create a Graph Ux project.
4. Run the Graph UX project to evaluate model performance in real time using selected camera.
5. Put in front of the camera pictures with ambulances, fire trucks, and police cars and observe detection from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 3,510 sessions targeting ambulances, fire trucks, and police cars.

Data sources and commercial-use conditions:

- `emerg_dataset1` (495 images, MIT): https://universe.roboflow.com/fyp-traffic-management-system/ambulances-23fqp
  - Replaces grayscale team-7 dataset; RGB street-scene ambulance images.
- `emerg_dataset2` (200 images, CC BY 4.0): https://universe.roboflow.com/gezamelijke-brandweer/cameramodel
  - Self-driving camera model dataset; fire-truck and police-car labels used.
- `emerg_dataset3` (711 images, CC BY 4.0): https://universe.roboflow.com/yolov8-etfar/emergency-vehicles-detection-xockh-af7sr-kvfuf
- `emerg_dataset4` (317 images, CC BY 4.0): https://universe.roboflow.com/national-school-of-applied-science-zh1i1/nn-ln8ka
- `emerg_dataset5` (432 images, CC BY 4.0): https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania
  - RGB street-scene police car images; added to balance underrepresented police_car class.
- `emerg_dataset6` (304 images, CC BY 4.0): https://universe.roboflow.com/fyp-tc-idn2o/police-cars-sumfm
  - Emergency Vehicle labels mapped to police_car; RGB dashcam and street scenes.
- `emerg_dataset7` (597 images, CC BY 4.0): https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania
  - Additional European (Romanian) police-car images; extends emerg_dataset5 (offset 500) with distinct RGB street scenes.
- `emerg_dataset8` (235 images, CC BY 4.0): https://universe.roboflow.com/smartire/veicoliemergenza
  - Italian emergency vehicles (visually verified): AMBULANZA ambulances, Vigili del Fuoco fire trucks, and Carabinieri police cars. Non-augmented version 2. 88 video-frame/stock-watermarked screenshots were manually removed after import (654 -> 566).
- `emerg_dataset9` (57 images, CC BY 4.0): https://universe.roboflow.com/erknnung/polizei-bkn68
  - German POLIZEI patrol vehicles (visually verified); mapped to police_car.
- `emerg_dataset10` (53 images, CC BY 4.0): https://universe.roboflow.com/smartire/emergencyvehicledetection-wuasv
  - Additional Italian ambulances (visually verified): AMBULANZA / Misericordia / Croce Verde / Croce Rossa vehicles in Italian cities (Florence, Milano, Bologna, Genova, Livorno, Catanzaro). Same Italian author as emerg_dataset8 but no overlapping images (0 shared filenames/hashes). The 'EmergencyVehicleDetection' label is the project name mis-applied to ambulances, so it is aliased to ambulance.
- `emerg_dataset11` (109 images, CC BY 4.0): https://universe.roboflow.com/central-university/firetruck2
  - French Sapeurs-Pompiers fire trucks (visually verified): red French fire engines (Renault/Iveco liveries, 'SAPEURS POMPIERS' markings). Non-augmented version 1. The project's default class label 'Priority-Vehicles-Pompier - v1 ...' is aliased to fire_truck. A few frames carry third-party watermarks (alamy, DEFENSE-ARAB) that content-based cleaning does not catch; the dedicated clean script removes only dark/washed-out/duplicate/corrupt images.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data if detection rate is low.** The starter dataset has 3,510 RGB sessions across urban, highway, and mixed lighting conditions, but performance can drop on your target camera (dashcam, fixed intersection view, or low-resolution feed). Collect and label images from the actual deployment scene—same angle, distance, and lighting—and retrain until emergency vehicles are detected reliably.
- **Add more classes if needed.** The project detects `ambulance`, `fire_truck`, and `police_car` only. If your product must distinguish siren states, vehicle subtypes, or other traffic classes, add labels and retrain accordingly.
- **Add negative data to reduce false positives.** Include regular cars, trucks, buses, and reflective or similarly colored vehicles so the model learns not to alarm on non-emergency traffic. This is especially important for always-on dashcam and intersection cameras.
- **Try different augmentation settings to match real-world variability.** Emergency vehicles appear at many scales, orientations, and lighting levels. Increase flip left/right for varied poses; adjust brightness and HSV augmentation for day/night and weather transitions; consider blur augmentation for motion-heavy camera feeds.
- **Tune advanced training settings for your safety target.** Use the confidence threshold to trade off missed emergency vehicles vs. false alarms (higher = fewer false positives). Adjust IoU threshold when multiple vehicles overlap. Experiment with training duration if one class (often distant or partially occluded police cars) lags behind the others.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.

## Attribution & Citation

@misc{
ambulances-23fqp_dataset,
title = { Ambulances Dataset },
type = { Open Source Dataset },
author = { FYP Traffic Management System },
howpublished = { \url{ https://universe.roboflow.com/fyp-traffic-management-system/ambulances-23fqp } },
url = { https://universe.roboflow.com/fyp-traffic-management-system/ambulances-23fqp },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { jan },
note = { visited on 2026-07-14 },
}


@misc{
cameramodel_dataset,
title = { cameramodel Dataset },
type = { Open Source Dataset },
author = { Gezamelijke Brandweer },
howpublished = { \url{ https://universe.roboflow.com/gezamelijke-brandweer/cameramodel } },
url = { https://universe.roboflow.com/gezamelijke-brandweer/cameramodel },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { jan },
note = { visited on 2026-07-14 },
}


@misc{
emergency-vehicles-detection-xockh-af7sr-kvfuf_dataset,
title = { Emergency Vehicles Detection Dataset },
type = { Open Source Dataset },
author = { yolov8 },
howpublished = { \url{ https://universe.roboflow.com/yolov8-etfar/emergency-vehicles-detection-xockh-af7sr-kvfuf } },
url = { https://universe.roboflow.com/yolov8-etfar/emergency-vehicles-detection-xockh-af7sr-kvfuf },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { jan },
note = { visited on 2026-07-14 },
}


@misc{
nn-ln8ka_dataset,
title = { nn Dataset },
type = { Open Source Dataset },
author = { national school of applied science },
howpublished = { \url{ https://universe.roboflow.com/national-school-of-applied-science-zh1i1/nn-ln8ka } },
url = { https://universe.roboflow.com/national-school-of-applied-science-zh1i1/nn-ln8ka },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { sep },
note = { visited on 2026-07-14 },
}


@misc{
police-cars-romania_dataset,
title = { police-cars-romania Dataset },
type = { Open Source Dataset },
author = { Bogdan Andrei },
howpublished = { \url{ https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania } },
url = { https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { oct },
note = { visited on 2026-07-14 },
}


@misc{
police-cars-sumfm_dataset,
title = { Police Cars Dataset },
type = { Open Source Dataset },
author = { FYP TC },
howpublished = { \url{ https://universe.roboflow.com/fyp-tc-idn2o/police-cars-sumfm } },
url = { https://universe.roboflow.com/fyp-tc-idn2o/police-cars-sumfm },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2022 },
month = { jan },
note = { visited on 2026-07-14 },
}


@misc{
police-cars-romania_dataset,
title = { police-cars-romania Dataset },
type = { Open Source Dataset },
author = { Bogdan Andrei },
howpublished = { \url{ https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania } },
url = { https://universe.roboflow.com/bogdan-andrei-470kt/police-cars-romania },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { oct },
note = { visited on 2026-07-14 },
}


@misc{
veicoliemergenza_dataset,
title = { VeicoliEmergenza Dataset },
type = { Open Source Dataset },
author = { smartire },
howpublished = { \url{ https://universe.roboflow.com/smartire/veicoliemergenza } },
url = { https://universe.roboflow.com/smartire/veicoliemergenza },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2026 },
month = { may },
note = { visited on 2026-07-14 },
}


@misc{
polizei-bkn68_dataset,
title = { polizei Dataset },
type = { Open Source Dataset },
author = { erknnung },
howpublished = { \url{ https://universe.roboflow.com/erknnung/polizei-bkn68 } },
url = { https://universe.roboflow.com/erknnung/polizei-bkn68 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { aug },
note = { visited on 2026-07-14 },
}


@misc{
emergencyvehicledetection-wuasv_dataset,
title = { EmergencyVehicleDetection Dataset },
type = { Open Source Dataset },
author = { smartire },
howpublished = { \url{ https://universe.roboflow.com/smartire/emergencyvehicledetection-wuasv } },
url = { https://universe.roboflow.com/smartire/emergencyvehicledetection-wuasv },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2026 },
month = { apr },
note = { visited on 2026-07-14 },
}


@misc{
firetruck2_dataset,
title = { firetruck2 Dataset },
type = { Open Source Dataset },
author = { central university },
howpublished = { \url{ https://universe.roboflow.com/central-university/firetruck2 } },
url = { https://universe.roboflow.com/central-university/firetruck2 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { may },
note = { visited on 2026-07-14 },
}


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
