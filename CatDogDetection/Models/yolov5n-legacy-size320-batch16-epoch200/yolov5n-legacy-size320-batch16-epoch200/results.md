# Evaluation Results: yolov5n-legacy-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 2

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9480 |
| F1 Score | 0.9161 |
| mAP@0.5 | 0.9480 |
| mAP@0.5:0.95 | 0.7032 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cat | 0.9573 | 0.7322 |
| dog | 0.9387 | 0.6741 |

### Confusion Matrix

| True \ Pred | (none) | cat | dog |
| --- | --- | --- | --- |
| (none) | 0 | 201 | 128 |
| cat | 69 | 1343 | 14 |
| dog | 40 | 0 | 625 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8580 |
| F1 Score | 0.8326 |
| mAP@0.5 | 0.8580 |
| mAP@0.5:0.95 | 0.5870 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cat | 0.8939 | 0.6293 |
| dog | 0.8221 | 0.5447 |

### Confusion Matrix

| True \ Pred | (none) | cat | dog |
| --- | --- | --- | --- |
| (none) | 0 | 41 | 29 |
| cat | 46 | 398 | 14 |
| dog | 26 | 18 | 157 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8184 |
| F1 Score | 0.7816 |
| mAP@0.5 | 0.8184 |
| mAP@0.5:0.95 | 0.5488 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cat | 0.8520 | 0.5878 |
| dog | 0.7849 | 0.5098 |

### Confusion Matrix

| True \ Pred | (none) | cat | dog |
| --- | --- | --- | --- |
| (none) | 0 | 132 | 30 |
| cat | 60 | 413 | 22 |
| dog | 32 | 16 | 161 |
