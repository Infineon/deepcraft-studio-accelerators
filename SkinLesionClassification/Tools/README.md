# Tools

Run the commands in the sections below to reconstruct `Data` and `.improj` file.

## 1. Project setup with Suspicious and Benign data: `1_organize_diagnosis_folders.py`

Rebuilds the lesion sessions from the published datasets: PAD-UFES-20, the FLUO-SC clinical photos, and the Hospital Italiano clinical photos. It writes `Data/Suspicious/`, `Data/Benign/`, `Resources/rename_mapping.csv`, and `SkinLesionClassification.improj`.

```text
python 1_organize_diagnosis_folders.py
```

Requires Python packages `Pillow` and `requests`. The script stops when `Data/` or `SkinLesionClassification.improj` is already present.

## 2. Normal_Skin data: `2_crop_normal_skin.py`

Cuts one square of clear skin from each selected lesion photo and labels it `Normal_Skin`. The crop stays in the split of the source photo: 300 training, 68 validation, and 78 test when that many clear patches exist. It writes the images to `Data/Normal_Skin/`, the list to `Resources/normal_skin_crops.csv`, and the three-label project to `SkinLesionClassification.improj`.

```text
python 2_crop_normal_skin.py
```

Requires Python packages `Pillow` and `numpy`. Running it again replaces `Data/Normal_Skin/`, the crop list, and `SkinLesionClassification.improj`. The lesion sessions stay as they are.
