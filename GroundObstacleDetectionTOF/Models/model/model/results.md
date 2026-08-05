# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 5

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9228 |
| F1 Score | 0.8691 |
| mAP@0.5 | 0.9228 |
| mAP@0.5:0.95 | 0.5990 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.8789 | 0.5480 |
| toy | 0.9529 | 0.6800 |
| ball | 0.8467 | 0.5779 |
| human | 0.9650 | 0.5477 |
| hedgehog | 0.9706 | 0.6413 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 1226 | 247 | 674 | 72 | 232 |
| obstacle | 141 | 1985 | 5 | 4 | 3 | 0 |
| toy | 48 | 1 | 1352 | 6 | 0 | 61 |
| ball | 34 | 0 | 0 | 808 | 0 | 24 |
| human | 2 | 5 | 3 | 0 | 170 | 0 |
| hedgehog | 7 | 0 | 6 | 18 | 0 | 967 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9325 |
| F1 Score | 0.8794 |
| mAP@0.5 | 0.9325 |
| mAP@0.5:0.95 | 0.6234 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9078 | 0.5695 |
| toy | 0.9638 | 0.7072 |
| ball | 0.8873 | 0.6197 |
| human | 0.9263 | 0.6019 |
| hedgehog | 0.9772 | 0.6188 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 107 | 36 | 63 | 8 | 35 |
| obstacle | 7 | 167 | 0 | 1 | 0 | 0 |
| toy | 2 | 0 | 159 | 2 | 0 | 5 |
| ball | 2 | 0 | 0 | 88 | 0 | 3 |
| human | 0 | 1 | 2 | 0 | 15 | 0 |
| hedgehog | 1 | 0 | 0 | 5 | 0 | 111 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9399 |
| F1 Score | 0.8816 |
| mAP@0.5 | 0.9399 |
| mAP@0.5:0.95 | 0.6463 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9313 | 0.5857 |
| toy | 0.9616 | 0.7028 |
| ball | 0.8656 | 0.6141 |
| human | 0.9840 | 0.6948 |
| hedgehog | 0.9568 | 0.6343 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 63 | 17 | 23 | 1 | 25 |
| obstacle | 3 | 100 | 0 | 0 | 0 | 0 |
| toy | 0 | 0 | 67 | 1 | 0 | 3 |
| ball | 3 | 0 | 0 | 41 | 0 | 2 |
| human | 0 | 0 | 0 | 0 | 9 | 0 |
| hedgehog | 2 | 0 | 0 | 2 | 0 | 53 |
