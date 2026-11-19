# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8965 |
| F1 Score | 0.8946 |
| mAP@0.5 | 0.8806 |
| mAP@0.5:0.95 | 0.6607 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8761 | 0.6661 |
| no_safety_vest | 0.8854 | 0.7116 |
| helmet | 0.8823 | 0.6028 |
| no_helmet | 0.8786 | 0.6623 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 543 | 677 | 560 | 274 |
| safety_vest | 390 | 3159 | 5 | 0 | 0 |
| no_safety_vest | 499 | 4 | 4451 | 3 | 0 |
| helmet | 458 | 2 | 3 | 4012 | 5 |
| no_helmet | 288 | 0 | 4 | 15 | 2391 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8375 |
| F1 Score | 0.8341 |
| mAP@0.5 | 0.7947 |
| mAP@0.5:0.95 | 0.5152 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.7927 | 0.5268 |
| no_safety_vest | 0.7560 | 0.5216 |
| helmet | 0.8193 | 0.4864 |
| no_helmet | 0.8108 | 0.5261 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 231 | 292 | 223 | 109 |
| safety_vest | 180 | 985 | 35 | 4 | 0 |
| no_safety_vest | 322 | 19 | 1330 | 0 | 0 |
| helmet | 221 | 1 | 3 | 1355 | 5 |
| no_helmet | 137 | 0 | 1 | 9 | 721 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8408 |
| F1 Score | 0.8373 |
| mAP@0.5 | 0.7989 |
| mAP@0.5:0.95 | 0.5148 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.7878 | 0.5133 |
| no_safety_vest | 0.7826 | 0.5365 |
| helmet | 0.8139 | 0.4766 |
| no_helmet | 0.8111 | 0.5328 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 217 | 285 | 221 | 118 |
| safety_vest | 199 | 1033 | 21 | 2 | 0 |
| no_safety_vest | 309 | 14 | 1318 | 1 | 1 |
| helmet | 231 | 1 | 4 | 1300 | 2 |
| no_helmet | 142 | 0 | 1 | 17 | 757 |
