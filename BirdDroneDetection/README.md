# Bird-Drone Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Bird-Drone Detection** project builds an end-to-end system that identifies **birds** and **drones** from camera or live video input. This is coming of increasing concern as drones continue to grow in popularity amongst both the civilian and military population.

The object detection model is YOLO-based and it can be used in applications for

- **Safety monitoring:** Detect drones over sites where unauthorized flight is a risk
- **Privacy:** Flag drones approaching an area of interest
- **Airspace awareness:** Separate drones from birds flying over the same scene

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT™ Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables fast detection and classification of drones, separating them from birds flying over the area of interest, provided the model is trained on images that match the deployment camera.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify birds and drones accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through data import or by using the `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double-clicking the `.tflite` file; it will generate a Graph UX project to run.

## Contents

- **`Data`**: Contains starter data from Roboflow with images of flying birds and drones: [Drone-Detection with Birds](https://universe.roboflow.com/workspace-ajksm/drone-detection-with-birds). Data consists of 7,395 annotated sessions (3,001 bird and 4,571 drone bounding boxes), grouped by label:

 - `bird` — 3,001 sessions with bird boxes only
 - `drone` — 4,351 sessions with drone boxes only

 No session contains both classes. License: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv` which map the current session image names back to their original Roboflow source filenames.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from the trained job.
3. Double-click the `.tflite` file and it will create a Graph UX project.
4. Run the Graph UX project to evaluate model performance in real time using the selected camera.
5. Place pictures of birds and drones in front of the camera and observe detection from the live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT™ Studio object-detection sessions under `Data/`, grouped by label into `Data/bird/` and `Data/drone/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). Session folders are named `bird_<n>` or `drone_<n>`. The project currently contains 7,352 sessions targeting birds and drones. No image in this set is labeled with both classes.

**Training augmentation:** Values below are the DEEPCRAFT™ Studio Augmentation Settings stored in `BirdDroneDetection.improj`. They are chosen for sky and outdoor views at 224 px: enough lighting and viewpoint variety for cameras looking up or across an open scene, without turning birds or drones upside down. Parameter names follow [YOLO data augmentation](https://docs.ultralytics.com/guides/yolo-data-augmentation).

- `degrees` 0 — left at the default off. The source images already vary in orientation, and it is unlikely a bird or drone must be classified upside down.
- `translate` 0.1 — default shift, so targets can appear off-center as they do when flying through a frame.
- `scale` 0.3 — below the YOLO default (0.5) so zoom-out does not shrink already-small airborne objects further at 224 px.
- `shear` 0 — left at the default off. Shear distorts silhouette and would make bird vs drone harder to tell apart.
- `fliplr` 0.5 — default left/right flip, so the model does not depend on which way the target is flying.
- `flipud` 0 — left at the default off. Typical cameras see birds and drones flying upright, not inverted.
- `perspective` 0.00025 — kept very low to simulate slight camera-angle change without warping silhouettes.
- `bgr` 0 — left at the default off. Channel swap is not a realistic camera failure mode here.
- `mosaic` 1 — YOLO default (1.0). Mosaic is kept high so distant drones still appear as small tiles the detector must find.
- `mixup` 0 — left at the default off. Blending two images would overlay birds and drones and confuse box labels.
- `copy_paste` 0 (`CopyPasteMode` Flip) — left at the default off. Pasting objects onto other scenes is unused; the mode setting has no effect while copy-paste is 0.
- `hsv_s` 0.7 — default saturation jitter for outdoor sky and vegetation color.
- `hsv_v` 0.4 — default brightness jitter for sun, shade, and overcast conditions.
- `hsv_h` 0.02 — small hue shift (near the YOLO default of 0.015) so outdoor white-balance changes are covered.

For selecting the most meaningful parameters for Data Augmentations it is important to understand your dataset, the use-case and the environment setup.

**Data sources and commercial-use conditions:**

- [Drone-Detection with Birds](https://universe.roboflow.com/workspace-ajksm/drone-detection-with-birds) (7,395 sessions, [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)): Roboflow Universe lists this dataset under CC BY 4.0, which allows commercial use with attribution. Sessions were renamed to `bird_<n>` / `drone_<n>`; original Roboflow filenames are in `Resources/rename_mapping.csv` and `Resources/rename_mapping.json`. Some original names look YouTube-derived; confirm source rights if you need a stricter provenance trail than the Universe listing.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT™ Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data if detection rate is low.** The starter dataset has 7,395 sessions of birds and drones, but performance can drop on your target camera (for example, a fixed skyward view, PTZ, or low-resolution feed). Collect and label images from the actual deployment scene—same angle, distance, and lighting—and retrain until birds and drones are detected reliably in that environment.
- **Add more classes if needed.** The project currently detects `Drone` and `Bird` only. If your product must also detect other airborne targets, e.g. planes or helicopters, add new classes and label accordingly before retraining.
- **Add negative data, including look-alikes.** Include empty sky under various weather conditions, skylines with buildings, and look-alikes so the model does not treat every airborne shape as a bird or drone. For a more robust model, add images of **other objects**—aircraft, kites, insects, balloons, and similar silhouettes that can appear in the same view—as unlabeled negatives, then retrain.
- **Watch bird vs drone confusion.** Distant drones and birds overlap in size and outline; extra examples from your camera at typical operating distances reduce mix-ups that close-up stock photos cannot fix alone.
- **Match augmentation to outdoor variability.** Keep flip up/down off for upright flight; increase flip left/right for varied approach angles; adjust HSV for sun, shade, and overcast sky. Keep mosaic high if many drones occupy only a small part of the frame.
- **Tune confidence for your sensitivity target.** Missing a drone may be more detrimental than misidentifying a bird—set thresholds for the cost you care about.


## Attributions & Citations

```bibtex
@misc{ drone-detection-with-birds_dataset,
  title = { Drone-Detection with Birds Dataset },
  type = { Open Source Dataset },
  author = { Workspace },
  howpublished = { \url{ https://universe.roboflow.com/workspace-ajksm/drone-detection-with-birds } },
  url = { https://universe.roboflow.com/workspace-ajksm/drone-detection-with-birds },
  journal = { Roboflow Universe },
  publisher = { Roboflow },
  year = { 2025 },
  month = { dec },
  note = { visited on 2026-09-24 },
}
```

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Help & Support

If you need support or if you want to know how to deploy the model onto the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
