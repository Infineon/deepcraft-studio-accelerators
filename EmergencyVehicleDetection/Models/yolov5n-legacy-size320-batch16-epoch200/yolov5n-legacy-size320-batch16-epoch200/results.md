# Evaluation Results: yolov5n-legacy-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9346 |
| F1 Score | 0.8889 |
| mAP@0.5 | 0.9346 |
| mAP@0.5:0.95 | 0.7140 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| ambulance | 0.9456 | 0.7625 |
| fire_truck | 0.9204 | 0.6787 |
| police_car | 0.9377 | 0.7007 |

### Confusion Matrix

| True \ Pred | (none) | ambulance | fire_truck | police_car |
| --- | --- | --- | --- | --- |
| (none) | 0 | 275 | 161 | 197 |
| ambulance | 48 | 909 | 7 | 4 |
| fire_truck | 56 | 9 | 589 | 0 |
| police_car | 75 | 8 | 4 | 955 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8900 |
| F1 Score | 0.8362 |
| mAP@0.5 | 0.8900 |
| mAP@0.5:0.95 | 0.6718 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| ambulance | 0.8871 | 0.7057 |
| fire_truck | 0.8758 | 0.6501 |
| police_car | 0.9072 | 0.6596 |

### Confusion Matrix

| True \ Pred | (none) | ambulance | fire_truck | police_car |
| --- | --- | --- | --- | --- |
| (none) | 0 | 83 | 58 | 84 |
| ambulance | 35 | 282 | 5 | 6 |
| fire_truck | 28 | 4 | 187 | 0 |
| police_car | 35 | 7 | 0 | 313 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9090 |
| F1 Score | 0.8651 |
| mAP@0.5 | 0.9090 |
| mAP@0.5:0.95 | 0.6835 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| ambulance | 0.8905 | 0.7081 |
| fire_truck | 0.9203 | 0.6795 |
| police_car | 0.9163 | 0.6627 |

### Confusion Matrix

| True \ Pred | (none) | ambulance | fire_truck | police_car |
| --- | --- | --- | --- | --- |
| (none) | 0 | 89 | 64 | 67 |
| ambulance | 40 | 296 | 6 | 4 |
| fire_truck | 18 | 6 | 197 | 0 |
| police_car | 31 | 7 | 0 | 319 |
