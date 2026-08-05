# Evaluation Results: yolov5n-legacy-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9034 |
| F1 Score | 0.8518 |
| mAP@0.5 | 0.9034 |
| mAP@0.5:0.95 | 0.6496 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| ambulance | 0.9230 | 0.7026 |
| fire_truck | 0.8842 | 0.6105 |
| police_car | 0.9030 | 0.6356 |

### Confusion Matrix

| True \ Pred | (none) | ambulance | fire_truck | police_car |
| --- | --- | --- | --- | --- |
| (none) | 0 | 615 | 344 | 334 |
| ambulance | 45 | 904 | 11 | 8 |
| fire_truck | 58 | 6 | 587 | 3 |
| police_car | 92 | 17 | 2 | 931 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8616 |
| F1 Score | 0.8110 |
| mAP@0.5 | 0.8616 |
| mAP@0.5:0.95 | 0.6019 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| ambulance | 0.8897 | 0.6736 |
| fire_truck | 0.8212 | 0.5414 |
| police_car | 0.8739 | 0.5907 |

### Confusion Matrix

| True \ Pred | (none) | ambulance | fire_truck | police_car |
| --- | --- | --- | --- | --- |
| (none) | 0 | 167 | 142 | 113 |
| ambulance | 20 | 288 | 16 | 4 |
| fire_truck | 21 | 3 | 193 | 2 |
| police_car | 32 | 9 | 0 | 314 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8795 |
| F1 Score | 0.8316 |
| mAP@0.5 | 0.8795 |
| mAP@0.5:0.95 | 0.6216 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| ambulance | 0.8809 | 0.6623 |
| fire_truck | 0.8784 | 0.5967 |
| police_car | 0.8792 | 0.6059 |

### Confusion Matrix

| True \ Pred | (none) | ambulance | fire_truck | police_car |
| --- | --- | --- | --- | --- |
| (none) | 0 | 137 | 123 | 105 |
| ambulance | 37 | 295 | 8 | 6 |
| fire_truck | 20 | 5 | 195 | 1 |
| police_car | 43 | 11 | 0 | 303 |
