# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 6

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.7576 |
| F1 Score | 0.7219 |
| mAP@0.5 | 0.7576 |
| mAP@0.5:0.95 | 0.5498 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.8467 | 0.6331 |
| bicycle | 0.6882 | 0.4785 |
| person | 0.7266 | 0.4792 |
| motorbike | 0.7624 | 0.5359 |
| car | 0.6840 | 0.4892 |
| bus | 0.8378 | 0.6832 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 131 | 452 | 3405 | 351 | 1112 | 128 |
| train | 113 | 506 | 0 | 1 | 2 | 3 | 12 |
| bicycle | 215 | 0 | 512 | 11 | 17 | 2 | 0 |
| person | 1498 | 0 | 12 | 4525 | 23 | 11 | 0 |
| motorbike | 156 | 1 | 41 | 38 | 476 | 13 | 0 |
| car | 747 | 6 | 2 | 8 | 4 | 1473 | 14 |
| bus | 121 | 10 | 0 | 1 | 0 | 26 | 463 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.7442 |
| F1 Score | 0.7104 |
| mAP@0.5 | 0.7442 |
| mAP@0.5:0.95 | 0.5377 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.7952 | 0.5797 |
| bicycle | 0.6913 | 0.5110 |
| person | 0.7213 | 0.4908 |
| motorbike | 0.8234 | 0.5305 |
| car | 0.6255 | 0.4518 |
| bus | 0.8086 | 0.6623 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 6 | 35 | 191 | 17 | 101 | 6 |
| train | 6 | 27 | 0 | 0 | 0 | 0 | 0 |
| bicycle | 5 | 0 | 31 | 2 | 0 | 1 | 0 |
| person | 75 | 0 | 1 | 240 | 1 | 0 | 0 |
| motorbike | 4 | 0 | 3 | 1 | 28 | 1 | 0 |
| car | 41 | 0 | 0 | 0 | 0 | 74 | 1 |
| bus | 8 | 1 | 0 | 0 | 0 | 0 | 22 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.7511 |
| F1 Score | 0.7156 |
| mAP@0.5 | 0.7511 |
| mAP@0.5:0.95 | 0.5277 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.8375 | 0.6182 |
| bicycle | 0.6715 | 0.4462 |
| person | 0.7124 | 0.4715 |
| motorbike | 0.7563 | 0.4809 |
| car | 0.7096 | 0.4746 |
| bus | 0.8192 | 0.6749 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 7 | 25 | 197 | 18 | 52 | 10 |
| train | 7 | 27 | 0 | 0 | 0 | 0 | 0 |
| bicycle | 12 | 0 | 29 | 0 | 0 | 0 | 0 |
| person | 81 | 0 | 0 | 248 | 0 | 0 | 0 |
| motorbike | 9 | 0 | 1 | 2 | 26 | 1 | 0 |
| car | 39 | 1 | 0 | 0 | 1 | 80 | 1 |
| bus | 9 | 0 | 0 | 0 | 0 | 1 | 23 |
