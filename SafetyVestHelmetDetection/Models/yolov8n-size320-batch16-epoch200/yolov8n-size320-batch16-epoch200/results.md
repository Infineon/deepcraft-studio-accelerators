# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8948 |
| F1 Score | 0.8926 |
| mAP@0.5 | 0.9262 |
| mAP@0.5:0.95 | 0.7378 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.9216 | 0.7406 |
| no_safety_vest | 0.9281 | 0.7845 |
| helmet | 0.9261 | 0.6828 |
| no_helmet | 0.9291 | 0.7433 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 560 | 620 | 504 | 272 |
| safety_vest | 406 | 3137 | 10 | 1 | 0 |
| no_safety_vest | 531 | 5 | 4419 | 1 | 1 |
| helmet | 459 | 1 | 7 | 4007 | 6 |
| no_helmet | 294 | 0 | 3 | 12 | 2389 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8311 |
| F1 Score | 0.8284 |
| mAP@0.5 | 0.8671 |
| mAP@0.5:0.95 | 0.6041 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8690 | 0.6152 |
| no_safety_vest | 0.8417 | 0.6152 |
| helmet | 0.8827 | 0.5706 |
| no_helmet | 0.8753 | 0.6152 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 228 | 291 | 221 | 106 |
| safety_vest | 186 | 991 | 25 | 2 | 0 |
| no_safety_vest | 327 | 19 | 1323 | 2 | 0 |
| helmet | 224 | 5 | 4 | 1341 | 11 |
| no_helmet | 142 | 0 | 1 | 13 | 712 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8333 |
| F1 Score | 0.8302 |
| mAP@0.5 | 0.8680 |
| mAP@0.5:0.95 | 0.6067 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8642 | 0.6092 |
| no_safety_vest | 0.8535 | 0.6390 |
| helmet | 0.8752 | 0.5558 |
| no_helmet | 0.8792 | 0.6227 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 243 | 277 | 244 | 118 |
| safety_vest | 196 | 1039 | 20 | 0 | 0 |
| no_safety_vest | 324 | 17 | 1299 | 3 | 0 |
| helmet | 230 | 0 | 5 | 1297 | 6 |
| no_helmet | 150 | 0 | 0 | 15 | 752 |
