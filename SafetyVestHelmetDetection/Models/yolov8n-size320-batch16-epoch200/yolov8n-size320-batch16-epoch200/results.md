# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9033 |
| F1 Score | 0.9016 |
| mAP@0.5 | 0.9335 |
| mAP@0.5:0.95 | 0.7509 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.9295 | 0.7551 |
| no_safety_vest | 0.9388 | 0.7964 |
| helmet | 0.9336 | 0.6970 |
| no_helmet | 0.9322 | 0.7553 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 482 | 604 | 515 | 277 |
| safety_vest | 371 | 3176 | 5 | 1 | 1 |
| no_safety_vest | 458 | 6 | 4487 | 4 | 2 |
| helmet | 427 | 2 | 12 | 4032 | 7 |
| no_helmet | 279 | 0 | 2 | 9 | 2408 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8398 |
| F1 Score | 0.8364 |
| mAP@0.5 | 0.8761 |
| mAP@0.5:0.95 | 0.6156 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8745 | 0.6229 |
| no_safety_vest | 0.8496 | 0.6378 |
| helmet | 0.8972 | 0.5802 |
| no_helmet | 0.8829 | 0.6213 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 221 | 278 | 211 | 109 |
| safety_vest | 180 | 996 | 23 | 5 | 0 |
| no_safety_vest | 316 | 19 | 1336 | 0 | 0 |
| helmet | 203 | 0 | 5 | 1371 | 6 |
| no_helmet | 144 | 0 | 2 | 9 | 713 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8425 |
| F1 Score | 0.8380 |
| mAP@0.5 | 0.8770 |
| mAP@0.5:0.95 | 0.6135 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8684 | 0.6114 |
| no_safety_vest | 0.8623 | 0.6478 |
| helmet | 0.8934 | 0.5658 |
| no_helmet | 0.8841 | 0.6289 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 215 | 259 | 216 | 115 |
| safety_vest | 202 | 1032 | 18 | 3 | 0 |
| no_safety_vest | 298 | 15 | 1329 | 0 | 1 |
| helmet | 227 | 1 | 2 | 1305 | 3 |
| no_helmet | 145 | 0 | 2 | 16 | 754 |
