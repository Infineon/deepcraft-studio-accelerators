# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8938 |
| F1 Score | 0.8918 |
| mAP@0.5 | 0.8749 |
| mAP@0.5:0.95 | 0.6574 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8681 | 0.6608 |
| no_safety_vest | 0.8855 | 0.7106 |
| helmet | 0.8770 | 0.6019 |
| no_helmet | 0.8688 | 0.6564 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 513 | 597 | 607 | 306 |
| safety_vest | 405 | 3141 | 6 | 2 | 0 |
| no_safety_vest | 517 | 3 | 4433 | 4 | 0 |
| helmet | 454 | 2 | 11 | 4010 | 3 |
| no_helmet | 300 | 0 | 7 | 18 | 2373 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8356 |
| F1 Score | 0.8325 |
| mAP@0.5 | 0.7930 |
| mAP@0.5:0.95 | 0.5140 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.7893 | 0.5199 |
| no_safety_vest | 0.7653 | 0.5220 |
| helmet | 0.8178 | 0.4893 |
| no_helmet | 0.7998 | 0.5248 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 241 | 273 | 235 | 97 |
| safety_vest | 192 | 980 | 30 | 2 | 0 |
| no_safety_vest | 319 | 19 | 1331 | 2 | 0 |
| helmet | 219 | 1 | 3 | 1355 | 7 |
| no_helmet | 141 | 0 | 1 | 8 | 718 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8407 |
| F1 Score | 0.8365 |
| mAP@0.5 | 0.7986 |
| mAP@0.5:0.95 | 0.5187 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.7889 | 0.5140 |
| no_safety_vest | 0.7719 | 0.5401 |
| helmet | 0.8214 | 0.4831 |
| no_helmet | 0.8123 | 0.5377 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 242 | 289 | 212 | 120 |
| safety_vest | 195 | 1036 | 22 | 2 | 0 |
| no_safety_vest | 306 | 13 | 1322 | 2 | 0 |
| helmet | 225 | 0 | 1 | 1309 | 3 |
| no_helmet | 141 | 0 | 0 | 11 | 765 |
