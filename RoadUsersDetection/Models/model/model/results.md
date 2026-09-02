# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 6

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.7577 |
| F1 Score | 0.7222 |
| mAP@0.5 | 0.7577 |
| mAP@0.5:0.95 | 0.5499 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.8469 | 0.6330 |
| bicycle | 0.6881 | 0.4785 |
| person | 0.7267 | 0.4794 |
| motorbike | 0.7629 | 0.5350 |
| car | 0.6840 | 0.4888 |
| bus | 0.8378 | 0.6844 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 129 | 452 | 3410 | 346 | 1118 | 129 |
| train | 113 | 506 | 0 | 1 | 2 | 3 | 12 |
| bicycle | 215 | 0 | 512 | 10 | 17 | 3 | 0 |
| person | 1494 | 0 | 13 | 4529 | 22 | 11 | 0 |
| motorbike | 153 | 1 | 41 | 40 | 477 | 13 | 0 |
| car | 746 | 6 | 2 | 8 | 5 | 1473 | 14 |
| bus | 121 | 10 | 0 | 1 | 0 | 26 | 463 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.7438 |
| F1 Score | 0.7112 |
| mAP@0.5 | 0.7438 |
| mAP@0.5:0.95 | 0.5360 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.7932 | 0.5785 |
| bicycle | 0.6904 | 0.5096 |
| person | 0.7210 | 0.4895 |
| motorbike | 0.8247 | 0.5306 |
| car | 0.6246 | 0.4486 |
| bus | 0.8086 | 0.6592 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 6 | 35 | 191 | 17 | 103 | 6 |
| train | 6 | 27 | 0 | 0 | 0 | 0 | 0 |
| bicycle | 5 | 0 | 31 | 2 | 0 | 1 | 0 |
| person | 75 | 0 | 1 | 240 | 1 | 0 | 0 |
| motorbike | 4 | 0 | 3 | 1 | 28 | 1 | 0 |
| car | 41 | 0 | 0 | 0 | 0 | 74 | 1 |
| bus | 8 | 1 | 0 | 0 | 0 | 0 | 22 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.7489 |
| F1 Score | 0.7156 |
| mAP@0.5 | 0.7489 |
| mAP@0.5:0.95 | 0.5276 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.8365 | 0.6170 |
| bicycle | 0.6738 | 0.4477 |
| person | 0.7130 | 0.4733 |
| motorbike | 0.7429 | 0.4793 |
| car | 0.7080 | 0.4732 |
| bus | 0.8192 | 0.6749 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 7 | 25 | 195 | 18 | 54 | 10 |
| train | 7 | 27 | 0 | 0 | 0 | 0 | 0 |
| bicycle | 12 | 0 | 29 | 0 | 0 | 0 | 0 |
| person | 81 | 0 | 0 | 248 | 0 | 0 | 0 |
| motorbike | 9 | 0 | 1 | 2 | 26 | 1 | 0 |
| car | 39 | 1 | 0 | 0 | 1 | 80 | 1 |
| bus | 9 | 0 | 0 | 0 | 0 | 1 | 23 |
