# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 5

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9152 |
| F1 Score | 0.9129 |
| mAP@0.5 | 0.8767 |
| mAP@0.5:0.95 | 0.6494 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.9028 | 0.6573 |
| spur | 0.8321 | 0.6033 |
| missing_hole | 0.9030 | 0.7068 |
| mouse_bite | 0.8727 | 0.6412 |
| open_circuit | 0.8728 | 0.6386 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 73 | 84 | 70 | 87 | 83 |
| short | 137 | 1424 | 1 | 0 | 0 | 0 |
| spur | 232 | 11 | 1270 | 0 | 2 | 0 |
| missing_hole | 146 | 0 | 0 | 1414 | 0 | 0 |
| mouse_bite | 201 | 0 | 3 | 1 | 1628 | 25 |
| open_circuit | 185 | 1 | 0 | 1 | 24 | 1566 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8679 |
| F1 Score | 0.8623 |
| mAP@0.5 | 0.8107 |
| mAP@0.5:0.95 | 0.5353 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.8083 | 0.4904 |
| spur | 0.7408 | 0.4769 |
| missing_hole | 0.9131 | 0.6811 |
| mouse_bite | 0.7664 | 0.5158 |
| open_circuit | 0.8247 | 0.5125 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 45 | 50 | 32 | 38 | 25 |
| short | 92 | 432 | 2 | 0 | 0 | 0 |
| spur | 115 | 10 | 405 | 0 | 7 | 1 |
| missing_hole | 44 | 1 | 0 | 470 | 1 | 0 |
| mouse_bite | 116 | 1 | 3 | 1 | 473 | 21 |
| open_circuit | 83 | 1 | 2 | 0 | 15 | 502 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8575 |
| F1 Score | 0.8527 |
| mAP@0.5 | 0.7964 |
| mAP@0.5:0.95 | 0.5313 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.7929 | 0.4764 |
| spur | 0.7473 | 0.4915 |
| missing_hole | 0.8561 | 0.6388 |
| mouse_bite | 0.7783 | 0.5282 |
| open_circuit | 0.8073 | 0.5214 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 51 | 38 | 35 | 43 | 39 |
| short | 97 | 468 | 2 | 0 | 2 | 0 |
| spur | 106 | 9 | 396 | 0 | 4 | 5 |
| missing_hole | 74 | 0 | 0 | 495 | 1 | 0 |
| mouse_bite | 115 | 3 | 8 | 0 | 482 | 15 |
| open_circuit | 86 | 2 | 2 | 0 | 26 | 503 |
