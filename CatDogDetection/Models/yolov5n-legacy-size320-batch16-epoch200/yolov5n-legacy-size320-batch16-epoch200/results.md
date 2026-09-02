# Evaluation Results: yolov5n-legacy-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 2

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9106 |
| F1 Score | 0.8604 |
| mAP@0.5 | 0.9106 |
| mAP@0.5:0.95 | 0.6399 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cat | 0.9438 | 0.6908 |
| dog | 0.8775 | 0.5889 |

### Confusion Matrix

| True \ Pred | (none) | cat | dog |
| --- | --- | --- | --- |
| (none) | 0 | 321 | 275 |
| cat | 70 | 1346 | 10 |
| dog | 63 | 27 | 575 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.7978 |
| F1 Score | 0.7601 |
| mAP@0.5 | 0.7978 |
| mAP@0.5:0.95 | 0.5445 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cat | 0.8626 | 0.6009 |
| dog | 0.7329 | 0.4881 |

### Confusion Matrix

| True \ Pred | (none) | cat | dog |
| --- | --- | --- | --- |
| (none) | 0 | 97 | 36 |
| cat | 42 | 409 | 7 |
| dog | 39 | 38 | 124 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.7699 |
| F1 Score | 0.7201 |
| mAP@0.5 | 0.7699 |
| mAP@0.5:0.95 | 0.5067 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cat | 0.8345 | 0.5584 |
| dog | 0.7054 | 0.4550 |

### Confusion Matrix

| True \ Pred | (none) | cat | dog |
| --- | --- | --- | --- |
| (none) | 0 | 183 | 43 |
| cat | 65 | 424 | 6 |
| dog | 44 | 31 | 134 |
