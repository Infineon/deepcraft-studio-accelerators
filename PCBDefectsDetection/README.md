# PCB Defects Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **PCB Defects Detection** project detects PCB manufacturing defects—short, spur, missing hole, mouse bite, and open circuit—from AOI inspection imagery.

The object detection model is YOLO-based and it can be used in applications for

- **AOI inspection:** Flag solder bridges, broken traces, and drill errors on production lines
- **Quality assurance:** Automate visual PCB defect screening before assembly or shipment

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

- **Machine learning method:** YOLO-based object detection trained in DEEPCRAFT Studio
- **Sensor and data type:** Fixed AOI camera, microscope, or top-down RGB inspection imagery (image data)
- **Why it matters:** Enables automated visual inspection to flag solder bridges, broken traces, and drill errors on production lines before assembly or shipment.

## Features

1. **Real-Time Detection**: The project uses a YOLO-based model to detect and classify PCB manufacturing defects (short, spur, missing hole, mouse bite, and open circuit) accurately and in real-time.
2. **Custom Data Integration**: Users can add new data through the data import or using `Object Detection Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double click `.tflite` file, and it will generate a Graph Ux project to run.

## Contents

- **`Data`**: Contains data taken from Roboflow with PCB manufacturing defects (short, spur, missing hole, mouse bite, and open circuit) images: [PCB defect detection datasets](https://universe.roboflow.com/search?q=pcb+defects). Data consists of 4,811 sessions (3,263 with defect labels, 1,548 defect-free negatives).

	- pcb_dataset1	- 577 images from Roboflow (https://universe.roboflow.com/nitw-tfufy/pcb-dataset-defect-fa2h3)
	- pcb_dataset2	- 1496 images from Roboflow (https://universe.roboflow.com/dataset-7wlmu/deeppcb-4dhir-ic1ay)
	- pcb_dataset3	- 500 images from Roboflow (https://universe.roboflow.com/ma007/hripcb)
	- pcb_dataset4	- 690 images from Roboflow (https://universe.roboflow.com/pcb-rfgn5/pcb-defect-detection-fyopy)
	- pcb_neg_dataset1	- 116 images from Roboflow (https://universe.roboflow.com/nitw-tfufy/pcb-dataset-defect-fa2h3)
	- pcb_neg_dataset2	- 232 images from Roboflow (https://universe.roboflow.com/ma007/hripcb)
	- pcb_neg_dataset3	- 1200 images from Roboflow (https://universe.roboflow.com/pcb-rfgn5/pcb-defect-detection-fyopy)

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv` and `rename_mapping.json` which map the current session image names back to their original Roboflow source filenames.

## Steps to get started: Model Training and Evaluation

1. Train the YOLO-based model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from trained job.
3. Double click the `.tflite` file and it will create a Graph Ux project.
4. Run the Graph UX project to evaluate model performance in real time using selected camera.
5. Put in front of the camera pictures with PCB manufacturing defects (short, spur, missing hole, mouse bite, and open circuit) and observe detection from live camera.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT Studio object-detection sessions under `Data/`. Each session contains a JPG image and `LabelXml` annotations with normalized center bounding boxes (`X`, `Y`, `Width`, `Height`). The project currently contains 4,811 sessions targeting PCB manufacturing defects (short, spur, missing hole, mouse bite, and open circuit): 3,263 defect-labeled and 1,548 in-domain defect-free negatives.

Data sources and commercial-use conditions:

- `pcb_dataset1` (577 images, CC BY 4.0): https://universe.roboflow.com/nitw-tfufy/pcb-dataset-defect-fa2h3
  - Academic PCB-DATASET benchmark (Ironbrotherstyle/PCB-DATASET); standard six-class AOI labels filtered to the five project classes on import.
- `pcb_dataset2` (1,496 images, CC BY 4.0): https://universe.roboflow.com/dataset-7wlmu/deeppcb-4dhir-ic1ay
  - DeepPCB public benchmark; class names normalized (open→open_circuit, mousebite→mouse_bite, pin-hole→missing_hole).
- `pcb_dataset3` (500 images, CC BY 4.0): https://universe.roboflow.com/ma007/hripcb
  - HRIPCB research benchmark; supplemental balanced AOI imagery beyond PCB-DATASET and DeepPCB.
- `pcb_dataset4` (690 images, CC BY 4.0): https://universe.roboflow.com/pcb-rfgn5/pcb-defect-detection-fyopy
  - Supplemental AOI defects with balanced session coverage across all five classes (no short-only prioritization).
- `pcb_neg_dataset1` (116 images, CC BY 4.0): https://universe.roboflow.com/nitw-tfufy/pcb-dataset-defect-fa2h3
  - In-domain defect-free negatives from PCB-DATASET (spurious_copper-only or unlabeled frames).
- `pcb_neg_dataset2` (232 images, CC BY 4.0): https://universe.roboflow.com/ma007/hripcb
  - In-domain defect-free negatives from HRIPCB (spurious_copper-only or unlabeled frames).
- `pcb_neg_dataset3` (1,200 images, CC BY 4.0): https://universe.roboflow.com/pcb-rfgn5/pcb-defect-detection-fyopy
  - In-domain defect-free negatives from the PCB defect AOI set (empty or spurious_copper-only frames).

## Adding More Data

You can add more data to the project following the steps below to improve detection or to include new classes.

1. Use `Object Detection Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT Studio object-detection format: images with matching `LabelXml` annotations using normalized center coordinates (`X`, `Y`, `Width`, `Height`). See [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Add more data if detection rate is low.** The starter dataset has 4,811 sessions from research-grade PCB defect benchmarks plus in-domain defect-free negatives, but performance can drop on your target camera (fixed AOI rig, conveyor top view, microscope feed, or different board colors and finishes). Collect and label images from the actual inspection line—same magnification, lighting, and board types—and retrain until all five defect classes are detected reliably.
- **Add more classes if needed.** The project detects `short`, `spur`, `missing_hole`, `mouse_bite`, and `open_circuit`. If your AOI process must also catch spurious copper, component misalignment, or other fault types, add classes and label accordingly before retraining.
- **Add negative data to reduce false positives.** The project includes 1,548 in-domain defect-free negatives (empty or spurious_copper-only frames from the same AOI datasets). Add hard negatives—pad rings, via patterns, dense trace areas—if `missing_hole` or other classes still false-alarm on background.
- **Use YOLOv8 with Mosaic = 0.5.** On the starter data this improved mAP@50 from ~73% (YOLOv5n legacy) to ~92%, with F1 ~83% across train/val/test. Keep flip-up-down off; Mosaic 0.5 balances context diversity without destroying tiny defects the way Mosaic 1.0 can.
- **Watch small defect boxes.** Roughly 26% of labels cover less than 0.1% of the image area. At ImageSize 320 this is demanding; increase to 416/640 if mAP@50-95 or distant defects need further improvement.
- **Tune advanced training settings for your yield target.** Use the confidence threshold to trade off missed defects vs. false rejects (higher = fewer false positives). Adjust IoU threshold when multiple defects appear close together.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Add negative data:** Include images without the target objects and common look-alikes to improve robustness against false positives.

## Attribution & Citation

@misc{
pcb-dataset-defect-fa2h3_dataset,
title = { PCB Dataset Defect Dataset },
type = { Open Source Dataset },
author = { NITW },
howpublished = { \url{ https://universe.roboflow.com/nitw-tfufy/pcb-dataset-defect-fa2h3 } },
url = { https://universe.roboflow.com/nitw-tfufy/pcb-dataset-defect-fa2h3 },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2026 },
month = { feb },
note = { visited on 2026-07-09 },
}


@misc{
deeppcb-4dhir-ic1ay_dataset,
title = { DeepPCB Dataset },
type = { Open Source Dataset },
author = { dataset },
howpublished = { \url{ https://universe.roboflow.com/dataset-7wlmu/deeppcb-4dhir-ic1ay } },
url = { https://universe.roboflow.com/dataset-7wlmu/deeppcb-4dhir-ic1ay },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2025 },
month = { jan },
note = { visited on 2026-07-09 },
}


@misc{
hripcb_dataset,
title = { HRIPCB Dataset },
type = { Open Source Dataset },
author = { MA007 },
howpublished = { \url{ https://universe.roboflow.com/ma007/hripcb } },
url = { https://universe.roboflow.com/ma007/hripcb },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2023 },
month = { apr },
note = { visited on 2026-07-09 },
}


@misc{
pcb-defect-detection-fyopy_dataset,
title = { PCB Defect detection Dataset },
type = { Open Source Dataset },
author = { PCB },
howpublished = { \url{ https://universe.roboflow.com/pcb-rfgn5/pcb-defect-detection-fyopy } },
url = { https://universe.roboflow.com/pcb-rfgn5/pcb-defect-detection-fyopy },
journal = { Roboflow Universe },
publisher = { Roboflow },
year = { 2024 },
month = { apr },
note = { visited on 2026-07-09 },
}


## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

For object-detection data formats, see [Bring your own data for object detection projects](https://developer.imagimob.com/deepcraft-studio/data-preparation/bring-your-data/bring-your-own-data-object-detection).

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page.
