# Grapevine Leaf Disease Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Grapevine Leaf Disease Detection** project builds an end-to-end system that identifies **black measles** (esca), **black rot**, **leaf blight**, and **healthy** grapevine leaves from camera or live video input.

The object detection model is YOLO-based and it can be used in applications for

- **Vineyard monitoring:** Detect diseased and healthy grapevine leaves in canopy, trellis, or handheld farm cameras
- **Precision agriculture:** Flag black measles, black rot, and leaf blight for targeted spraying and scouting
- **Quality inspection:** Screen harvested or nursery leaves before they move further in the supply chain

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT™ Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables early grapevine disease scouting from live camera feeds, provided the model is trained on images that match the deployment camera.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify black measles, black rot, leaf blight, and healthy grapevine leaves accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double-clicking the `.tflite` file; it will generate a Graph UX project to run.

## Contents

- **`Data`**: Contains data taken from Roboflow with images of grapevine leaf diseases (black measles, black rot, and leaf blight) and healthy leaves. The data consists of 4,960 annotated sessions (1,738 black_measles, 1,387 black_rot, 1,301 leaf_blight, 683 healthy bounding boxes).

	- [grape_dataset1](#grape_leaves_dataset)	- 1482 images from Roboflow (https://universe.roboflow.com/grape-rpakq/grapevine-leaves)
	- [grape_dataset2](#grape_leaf_disease_detection_dataset)	- 268 images from Roboflow (https://universe.roboflow.com/laluna/grape-leaf-disease-detection-gzafz)
	- [grape_dataset3](grape_leaf_diseases_dataset)	- 2364 images from Roboflow (https://universe.roboflow.com/skimok77/grape-leaf-diseases-tln5a)
	- [grape_dataset4](#leaf_diseases_dataset)	- 846 images from Roboflow (https://universe.roboflow.com/trial1-53ber/grape-leaf-diseases-hqlrl) 

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv` and `rename_mapping.json` which map the current session image names back to their original Roboflow source filenames.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from the trained job.
3. Double-click the `.tflite` file and it will create a Graph UX project.
4. Run the Graph UX project to evaluate model performance in real time using the selected camera.
5. Put in front of the camera pictures with grapevine leaves (healthy, black measles, black rot, and leaf blight) and observe detection from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT™ Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 4,960 sessions targeting grapevine leaf diseases (black measles, black rot, and leaf blight) and healthy leaves.

**Small-box cleaning:** Sessions were filtered so tiny labels do not remain in the training set. At the 320 px training size, images that contain any box whose shorter side is under 24 px are skipped entirely, so remaining sessions stay fully annotated. Distant specks that a 320 px detector cannot localize reliably are therefore not used as positives.

**Training augmentation:** DEEPCRAFT™ Studio Augmentation Settings in this project's `.improj` are chosen for vineyard leaves at 320 px. Rotation is mild (`degrees` 10) and translation is modest (`translate` 0.1); scale (`scale` 0.2) and mosaic (`mosaic` 0.5) stay below the YOLO defaults so small lesion boxes are not shrunk further. Flip left/right is on (`fliplr` 0.5); flip up/down, shear, and perspective are off so leaf pose stays natural. HSV saturation (`hsv_s` 0.35) and brightness (`hsv_v` 0.4) cover outdoor vineyard lighting, with a small hue shift (`hsv_h` 0.015). Parameter names follow [YOLO data augmentation](https://docs.ultralytics.com/guides/yolo-data-augmentation).

Data sources and commercial-use conditions:

- [grape_dataset1](#grape_leaves_dataset) (1482 images, CC BY 4.0): https://universe.roboflow.com/grape-rpakq/grapevine-leaves
  - Starting set: balanced close-up grapevine leaves for black measles, black rot, leaf blight, and healthy. Version 4 has no generated augmentations. Images containing any box whose shorter side is under 24 px at the 320 px training image size are skipped entirely. Near-duplicates shared with the other PlantVillage-style sources were removed after import.
- [grape_dataset2](#grape_leaf_disease_detection_dataset) (268 images, CC BY 4.0): https://universe.roboflow.com/laluna/grape-leaf-disease-detection-gzafz
  - Lesion-level boxes on grape leaves (esca/black measles, black rot, leaf blight, and healthy). Version 1 has no generated augmentations. Many frames were skipped because at least one lesion box was under 24 px at the 320 px training size, so remaining sessions stay fully annotated.
- [grape_dataset3](grape_leaf_diseases_dataset)  (2364 images, CC BY 4.0): https://universe.roboflow.com/skimok77/grape-leaf-diseases-tln5a
  - Full four-class grape leaf set (black rot, esca, leaf blight, healthy). Version 1 is used because version 2 bakes in generated augmentations. Near-duplicates of grape_dataset1 were removed after import. Images containing any box whose shorter side is under 24 px at the 320 px training image size are skipped entirely.
- [grape_dataset4](#leaf_diseases_dataset) (846 images, Public Domain): https://universe.roboflow.com/trial1-53ber/grape-leaf-diseases-hqlrl
  - Public-domain grape leaf images with Indonesian class names mapped to black rot, esca/black measles, leaf blight, and healthy. Version 1 has no generated augmentations. Near-duplicates of the PlantVillage-style sources were removed after import. Images containing any box whose shorter side is under 24 px at the 320 px training image size are skipped entirely.

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data if detection rate is low.** The starter dataset has 4,960 sessions across close-up leaves and vineyard views, but performance can drop on your target camera (for example, a fixed trellis view, drone, or low-resolution scouting phone). Collect and label images from the actual vineyard—same angle, distance, cultivar, and lighting—and retrain until diseased and healthy leaves are detected reliably in that environment.
- **Add more classes if needed.** The project currently detects `black_measles`, `black_rot`, `leaf_blight`, and `healthy` only. If your product must also catch downy mildew, powdery mildew, or pest damage, add new classes and label accordingly before retraining.
- **Add negative data, including other plants.** Include empty canopy, soil, posts, and look-alike leaves (other crops, weeds, autumn discoloration) as unlabeled negatives so the model does not treat every yellow or spotted leaf as a grapevine disease.
- **Watch black measles vs black rot confusion.** Both produce dark lesions on grape leaves; extra close-up examples from your vineyard reduce mix-ups that distant canopy shots cannot fix alone.
- **Match augmentation to outdoor variability.** Keep flip up/down off unless your camera can see the underside of the canopy; increase flip left/right for varied approach angles; adjust HSV for sun, shade, and overcast rows. Keep scale and mosaic moderate if many lesions occupy only a small part of the frame.
- **Tune confidence for your sensitivity target.** Missing a diseased leaf may delay treatment; a false detection may trigger unnecessary spraying—set thresholds for the cost you care about.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.

## Attribution & Citation


<a name="grape_leaves_dataset"> [Grape Leaves Dataset](https://universe.roboflow.com/grape-rpakq/grapevine-leaves), author: grape-rpakq, published August 2024, visited on 2026-09-08 </a> 	

<a name="grape_leaf_disease_detection_dataset"> [Grape Leaf Disease Detection Dataset](https://universe.roboflow.com/laluna/grape-leaf-disease-detection-gzafz), author: laluna, published May 2026, visited on 2026-09-08  </a>
	
<a name="grape_leaf_diseases_dataset"> [Grape Leaf Diseases Dataset](https://universe.roboflow.com/skimok77/grape-leaf-diseases-tln5a), author: skimok77, published July 2025, visited on 2026-09-08 </a>	

<a name="grape-leaf_diseases_dataset"> [grape-leaf-diseases Dataset](https://universe.roboflow.com/trial1-53ber/grape-leaf-diseases-hqlrl), author: trial1, published May 2025, visited on 2026-09-08 </a>	

   
	

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

If you need support or if you want to know how to deploy the model onto the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.