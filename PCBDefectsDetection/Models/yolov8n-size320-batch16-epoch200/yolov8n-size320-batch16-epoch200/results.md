# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 5

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9017 |
| F1 Score | 0.8988 |
| mAP@0.5 | 0.8612 |
| mAP@0.5:0.95 | 0.5987 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.8808 | 0.6011 |
| spur | 0.8109 | 0.5450 |
| missing_hole | 0.8916 | 0.6774 |
| mouse_bite | 0.8516 | 0.5841 |
| open_circuit | 0.8710 | 0.5861 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 140 | 117 | 76 | 119 | 127 |
| short | 170 | 1390 | 2 | 0 | 0 | 0 |
| spur | 254 | 16 | 1237 | 0 | 6 | 2 |
| missing_hole | 153 | 1 | 0 | 1406 | 0 | 0 |
| mouse_bite | 244 | 1 | 4 | 2 | 1563 | 44 |
| open_circuit | 206 | 2 | 0 | 0 | 22 | 1547 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8543 |
| F1 Score | 0.8499 |
| mAP@0.5 | 0.7988 |
| mAP@0.5:0.95 | 0.5221 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.7885 | 0.4697 |
| spur | 0.7317 | 0.4569 |
| missing_hole | 0.8910 | 0.6682 |
| mouse_bite | 0.7747 | 0.5067 |
| open_circuit | 0.8079 | 0.5091 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 60 | 57 | 34 | 61 | 43 |
| short | 91 | 433 | 1 | 0 | 0 | 1 |
| spur | 118 | 13 | 401 | 0 | 4 | 2 |
| missing_hole | 48 | 0 | 0 | 467 | 1 | 0 |
| mouse_bite | 111 | 2 | 5 | 3 | 476 | 18 |
| open_circuit | 90 | 4 | 1 | 0 | 16 | 492 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8426 |
| F1 Score | 0.8379 |
| mAP@0.5 | 0.7845 |
| mAP@0.5:0.95 | 0.5132 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.7744 | 0.4688 |
| spur | 0.7423 | 0.4692 |
| missing_hole | 0.8452 | 0.6278 |
| mouse_bite | 0.7565 | 0.4931 |
| open_circuit | 0.8041 | 0.5069 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 79 | 53 | 35 | 53 | 69 |
| short | 106 | 460 | 0 | 0 | 3 | 0 |
| spur | 106 | 11 | 393 | 0 | 4 | 6 |
| missing_hole | 80 | 1 | 1 | 488 | 0 | 0 |
| mouse_bite | 119 | 3 | 6 | 3 | 473 | 19 |
| open_circuit | 97 | 4 | 2 | 0 | 18 | 498 |
