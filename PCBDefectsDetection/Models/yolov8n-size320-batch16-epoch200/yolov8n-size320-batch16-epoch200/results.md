# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 5

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8932 |
| F1 Score | 0.8894 |
| mAP@0.5 | 0.9158 |
| mAP@0.5:0.95 | 0.7055 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.9311 | 0.6979 |
| spur | 0.8905 | 0.6772 |
| missing_hole | 0.9371 | 0.7721 |
| mouse_bite | 0.9043 | 0.6890 |
| open_circuit | 0.9157 | 0.6914 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 72 | 117 | 103 | 105 | 92 |
| short | 181 | 1375 | 3 | 1 | 1 | 1 |
| spur | 280 | 11 | 1217 | 0 | 7 | 0 |
| missing_hole | 160 | 1 | 0 | 1398 | 1 | 0 |
| mouse_bite | 276 | 0 | 6 | 5 | 1531 | 40 |
| open_circuit | 238 | 1 | 1 | 0 | 26 | 1511 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8384 |
| F1 Score | 0.8345 |
| mAP@0.5 | 0.8685 |
| mAP@0.5:0.95 | 0.6158 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.8724 | 0.5743 |
| spur | 0.8248 | 0.5621 |
| missing_hole | 0.9247 | 0.7386 |
| mouse_bite | 0.8440 | 0.6086 |
| open_circuit | 0.8765 | 0.5953 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 47 | 75 | 32 | 56 | 32 |
| short | 101 | 419 | 4 | 0 | 0 | 2 |
| spur | 126 | 9 | 394 | 0 | 8 | 1 |
| missing_hole | 62 | 1 | 0 | 450 | 3 | 0 |
| mouse_bite | 125 | 0 | 5 | 4 | 457 | 24 |
| open_circuit | 100 | 1 | 1 | 1 | 18 | 482 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8240 |
| F1 Score | 0.8188 |
| mAP@0.5 | 0.8565 |
| mAP@0.5:0.95 | 0.6096 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| short | 0.8530 | 0.5428 |
| spur | 0.8292 | 0.5901 |
| missing_hole | 0.9008 | 0.7077 |
| mouse_bite | 0.8344 | 0.6138 |
| open_circuit | 0.8654 | 0.5935 |

### Confusion Matrix

| True \ Pred | (none) | short | spur | missing_hole | mouse_bite | open_circuit |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 50 | 52 | 28 | 57 | 56 |
| short | 113 | 449 | 1 | 0 | 3 | 3 |
| spur | 123 | 10 | 371 | 0 | 10 | 6 |
| missing_hole | 90 | 0 | 0 | 479 | 1 | 0 |
| mouse_bite | 131 | 2 | 8 | 4 | 457 | 21 |
| open_circuit | 102 | 1 | 1 | 0 | 35 | 480 |
