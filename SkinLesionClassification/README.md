# Suspicious Skin Lesion Classification

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

The **Suspicious Skin Lesion Classification** project builds a YOLO-based model that classifies a camera image or live video as **Suspicious**, **Benign**, or **Normal_Skin**, as a first screening that groups each image before further review. **Normal_Skin** is a frame with no lesion.

This first screening helps prioritize images for further review. **Suspicious** means the lesion should be looked at more closely. It groups melanoma, basal cell carcinoma, squamous cell carcinoma, and actinic keratosis. **Benign** groups nevus and seborrheic keratosis. Actinic keratosis is in Suspicious because it is a lesion that should be examined. The cancers in the PAD-UFES-20 dataset are biopsy-proven.

The image classification model is YOLO-based and it can be used in applications for

- **Edge devices:** Run the first screening on an MCU board such as PSOC™ Edge and label each camera image Suspicious, Benign, or Normal_Skin
- **Wearables:** Screen a skin view using a wearable camera and return Suspicious, Benign, or Normal_Skin on the device
- **Clinic intake:** Mark images Suspicious, Benign, or Normal_Skin so the Suspicious ones can be reviewed first

Users can further expand this project by training their own models, importing new data, and evaluating performance using the provided tools.

This Accelerator allows you to build a model for first screening. The model uses the dataset diagnosis, grouped into Suspicious or Benign, and uses Normal_Skin for a frame with no lesion. It does not provide a medical diagnosis.

- **Machine learning method:** YOLO-based image classification trained in DEEPCRAFT™ Studio
- **Sensor and data type:** RGB camera or live video input (image data)
- **Why it matters:** Enables a first on-device screening that groups each camera image into Suspicious, Benign, or Normal_Skin, provided the model is trained on images that match the deployment camera.

## Features

1. **Real-Time Classification**: The project uses a YOLO-based model to classify a camera image as suspicious, benign, or normal skin in real time. Each image has one class name and no bounding box.
2. **Custom Data Integration**: Users can add new data through data import or by using the `Image Classification Data Collection Graph UX` template and label their own data for model training.
3. **Model Evaluation**: Evaluate trained models by double-clicking the `.tflite` file; it will generate a Graph UX project to run.

## Contents

- **`Data`**: 2,617 annotated sessions of skin lesions, grouped into issue folders under Suspicious and Benign, plus 446 `Normal_Skin` crops. Suspicious: `Melanoma` (127), `Basal_Cell_Carcinoma` (948), `Squamous_Cell_Carcinoma` (316), `Actinic_Keratosis` (747). Benign: `Nevus` (244), `Seborrheic_Keratosis` (235). Sources of the lesion photos are PAD-UFES-20, FLUO-SC, and Hospital Italiano de Buenos Aires. The folder names keep the specific issue. The label on each lesion image is Suspicious or Benign. `Data/Normal_Skin/` holds frames with no lesion. `Tools/2_crop_normal_skin.py` cuts one square of normal, clear skin from a lesion photo, at least 224×224 pixels, away from the busiest part of the image, which is where the lesion usually sits. The crop stays in the split of that photo: 300 in training, 68 in validation, and 78 in test. Validation had 68 photos with a clear enough patch to keep.

- **`Models`** - Stores the trained YOLO-based model and its quantized versions as well as their predictions.

- **`Resources`** - Folder containing supporting project files, including `rename_mapping.csv`, which maps each lesion session to its issue folder, original filename when one exists, label, split, and source dataset. `normal_skin_crops.csv` records each Normal_Skin crop, the photo it was cut from, and the split.

- **`Tools`** - `1_organize_diagnosis_folders.py` rebuilds `Data` and `SkinLesionClassification.improj` from PAD-UFES-20, FLUO-SC, and Hospital Italiano de Buenos Aires. `2_crop_normal_skin.py` adds the Normal_Skin patches from all three splits to that project file.

## Steps to get started: Model Training and Evaluation

1. Train the image classification model using the provided dataset or custom data.
2. Download the trained model `.tflite` file from the trained job.
3. Double-click the `.tflite` file and it will create a Graph UX project.
4. Run the Graph UX project to evaluate model performance in real time using the selected camera.
5. Place a picture of a skin lesion in front of the camera and observe the class.

## Sensor(s) & Data

Image data is stored as DEEPCRAFT™ Studio image-classification sessions under `Data/`. Each session contains one JPG image and a `LabelXml` class name. There is no bounding box. The project currently contains 2,617 lesion sessions and 446 Normal_Skin crops.

The training set is 1,114 suspicious and 283 benign PAD-UFES-20 photos, plus 96 FLUO-SC and 223 Hospital Italiano suspicious photos, plus 300 Normal_Skin crops. Several images often belong to one person, so every photo of a patient stays in that one split, and the extra photos stay in training with them. The validation set is 355 suspicious and 102 benign, plus 68 Normal_Skin crops, from unseen PAD-UFES-20 patients. The test set is 350 suspicious and 94 benign, plus 78 Normal_Skin crops, also unseen PAD-UFES-20 patients, and is the measure of how the model does on new people. Each Normal_Skin crop stays in the split of the lesion photo it was cut from. Validation had 68 photos with a clear enough patch to keep. `SkinLesionClassification.improj` contains the Suspicious and Benign labels after project setup, and `2_crop_normal_skin.py` adds the Normal_Skin label and crops to the same file.

The PAD-UFES-20 release is PNG. Those files are saved here as JPG at quality 90. JPEG quality runs from 0 to 100, and a higher number keeps more of the original image. Quality 90 is a high setting: the file is smaller than the PNG, and the lesion color and border stay close to the source. EXIF orientation is applied, so the camera rotation stored in the photo is written into the pixels and the image is upright. The long side is limited to 1280 pixels: a larger photo is scaled down until its longer edge is 1280, and the shape stays the same. The model is then trained at 224×224 pixels.

**Body regions:** The PAD-UFES-20 metadata records where each lesion is on the body. Counts below cover all 2,298 PAD-UFES-20 images (suspicious / benign). Over a third are on the head (face, nose, ear, lip, and scalp), so part of a nose, lip, or ear can appear around the lesion.

- Face: 570 (433 / 137)
- Forearm: 392 (361 / 31)
- Chest: 280 (220 / 60)
- Back: 248 (138 / 110)
- Arm: 192 (163 / 29)
- Nose: 158 (155 / 3)
- Hand: 126 (118 / 8)
- Neck: 93 (79 / 14)
- Ear: 73 (62 / 11)
- Thigh: 73 (46 / 27)
- Abdomen: 36 (9 / 27)
- Lip: 23 (20 / 3)
- Scalp: 18 (5 / 13)
- Foot: 16 (10 / 6)

**Training augmentation:** Values below are the DEEPCRAFT™ Studio Augmentation Settings stored in `SkinLesionClassification.improj`. They are chosen for a single skin lesion in a camera frame at 224 px: enough pose and lighting variety for a board camera, without warping the lesion outline or pasting several lesions into one image. Parameter names follow [YOLO data augmentation](https://docs.ultralytics.com/guides/yolo-data-augmentation).

- `degrees` 10 — rotation for a camera that is not perfectly level.
- `translate` 0.12 — the lesion can sit off-center in the frame.
- `scale` 0.2 — below the YOLO default (0.5) so zoom does not crop the lesion border as often.
- `shear` 0 — left off. Shear distorts the lesion outline.
- `fliplr` 0.5 — left/right flip, so the label does not depend on which side of the frame the lesion faces.
- `flipud` 0.5 — up/down flip. A single lesion has no required up direction, unlike an upright object standing on the ground.
- `perspective` 0 — left off. Perspective warp changes the lesion outline.
- `bgr` 0 — left at the default off. Channel swap is not a realistic camera mode here.
- `mosaic` 0 — left off. One image is one lesion, so four images are not tiled together.
- `mixup` 0 — left at the default off. Blending two images would overlay two lesions and confuse the label.
- `copy_paste` 0 (`CopyPasteMode` Flip) — left at the default off. Pasting a lesion onto another image is unused; the mode setting has no effect while copy-paste is 0.
- `hsv_s` 0.25 — below the YOLO default (0.7) so brown, red, and pink stay close to the captured color.
- `hsv_v` 0.45 — brightness jitter for sun, shade, and indoor light.
- `hsv_h` 0.008 — a smaller hue shift than the YOLO default (0.015) so those colors stay distinct.

For selecting the most meaningful parameters for Data Augmentations it is important to understand your dataset, the use-case and the environment setup.

**Data sources and commercial-use conditions:**

- `pad_ufes` (2,298 images, CC BY 4.0): https://data.mendeley.com/datasets/zr7vgbcyr2/1
  - Clinical photographs collected by the Dermatological and Surgical Assistance Program at the Federal University of Espírito Santo. Six diagnoses: melanoma (MEL), nevus (NEV), basal cell carcinoma (BCC), squamous cell carcinoma (SCC), actinic keratosis (ACK), and seborrheic keratosis (SEK). The paper states that the cancers are biopsy-proven. The files used here are the JPEGs prepared from that release, including the Hugging Face mirror (https://huggingface.co/datasets/SalmaneExploring/pad-ufes-20), which carries the same CC BY 4.0 license.
- `fluo` (96 suspicious images added to training only, CC BY 4.0): https://doi.org/10.17632/s8n68jj678.1
  - White-light clinical photographs from FLUO-SC: 18 melanoma and 78 squamous-cell images, labeled Suspicious. The release names the squamous-cell folder CCE. Fluorescence images were not used.
- `hiba` (223 suspicious images added to training only, CC BY): https://doi.org/10.34970/587329
  - Clinical photographs from Hospital Italiano de Buenos Aires: 57 melanoma, 46 squamous cell, 103 basal cell, and 17 actinic keratosis, labeled Suspicious. Dermoscopic photographs were not used.

## Adding More Data

You can add more data to the project following the steps below to improve classification or to include new classes.

1. Use `Image Classification Data Collection Graph UX` template to collect and label new data.
2. Import data to your project and retrain to get an updated model.

You can also import data from any other source (for example, your own images or another dataset) as long as it follows the DEEPCRAFT™ Studio image-classification format: one JPG and a `LabelXml` class name, with no bounding box. Label an image `Suspicious`, `Benign`, or `Normal_Skin`. Put a lesion under the matching issue folder, for example `Data/Suspicious/Melanoma/`, and put a frame with no lesion in `Data/Normal_Skin/`. Put every image of a new person into one split.

## Steps to Production

The recommended path to production for this project includes the following steps:

- **Collect normal skin from the deployment camera and add it to the project.** A model that only knows Suspicious and Benign has to choose one of those two labels for every frame, so bare skin is often called Suspicious. Keep **Normal_Skin** as its own label for a frame with no lesion. Record that view on the camera of the target board, such as PSOC™ Edge: face, nose, ear, neck, chest, back, abdomen, arm, forearm, hand, thigh, and foot, across skin tones, lighting, and distance. Include frames that the current model calls Suspicious. Keep every photo of one person in one split. A few hundred images from different people, on the order of 300 to 500, are a useful first set. The Normal_Skin crops already here are clear skin cut from the lesion photos. They give the label a starting set, and photos from the board camera are what make the label hold on the device.
- **Add more data if classification on your camera is weak.** Performance can drop when the deployment camera differs from the training images (angle, distance, lighting, or resolution). Collect and label images from the camera on the target board, such as PSOC™ Edge, and retrain until suspicious lesions, benign lesions, and normal skin are separated reliably in that setup.
- **Differentiate the specific issues when you have enough examples.** `SkinLesionClassification.improj` outputs `Suspicious`, `Benign`, and `Normal_Skin`. The folders already separate melanoma, basal cell carcinoma, squamous cell carcinoma, actinic keratosis, nevus, and seborrheic keratosis, so a later model can name those issues. That needs more data. Melanoma has 127 images in this project and 10 in the unseen test set. Squamous cell carcinoma has 316. Basal cell carcinoma has 948 and actinic keratosis has 747. Nevus has 244 and seborrheic keratosis has 235. Melanoma and squamous cell carcinoma are too small for a stable six-way decision on new patients. More views of the images already here do not replace new patients.
- **Match the camera.** Train and test on the same kind of view the board will see. A wide view of a face, or a dermoscope image, is a different problem from one lesion filling the frame.
- **Keep new patients out of the training split.** Several images often belong to one person.
- **Prefer a suspicious call over a missed suspicious lesion.** Missing a lesion that should be seen is the costly error. A benign lesion called suspicious is the accepted false alarm for this screening use.

Some points to highlight:

- **Increase data variability:** Collect data from different environments, cameras, lighting conditions, distances, and backgrounds. Use DEEPCRAFT™ Studio augmentation settings (flip, scale, brightness, exposure) to increase image variability for vision models.
- **Keep test data independent:** Make sure the test set is not used in train or validation and reflects scenarios where the model must generalize.
- **Do not ship this as a diagnosis.** A miss or a false call on a real patient is not something this model is built to decide.

## Attributions & Citations

```bibtex
@misc{pad_ufes_20,
  title = { PAD-UFES-20: a skin lesion dataset composed of patient data and clinical images collected from smartphones },
  type = { Open Source Dataset },
  author = { Pacheco, Andre G. C. and others },
  howpublished = { \url{ https://doi.org/10.17632/zr7vgbcyr2.1 } },
  url = { https://data.mendeley.com/datasets/zr7vgbcyr2/1 },
  journal = { Data in Brief },
  publisher = { Mendeley Data },
  year = { 2020 },
  month = { aug },
  note = { visited on 2026-10-13 },
}
```

```bibtex
@misc{fluo_sc,
  title = { FLUO-SC },
  type = { Open Source Dataset },
  howpublished = { \url{ https://doi.org/10.17632/s8n68jj678.1 } },
  url = { https://doi.org/10.17632/s8n68jj678.1 },
  publisher = { Mendeley Data },
  note = { visited on 2026-10-13 },
}
```

```bibtex
@misc{hiba_clinical,
  title = { Hospital Italiano de Buenos Aires clinical skin lesion images },
  type = { Open Source Dataset },
  author = { Hospital Italiano de Buenos Aires },
  howpublished = { \url{ https://doi.org/10.34970/587329 } },
  url = { https://doi.org/10.34970/587329 },
  year = { 2022 },
  note = { visited on 2026-10-13 },
}
```

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model onto the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
