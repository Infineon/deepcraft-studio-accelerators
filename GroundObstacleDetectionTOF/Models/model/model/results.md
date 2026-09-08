# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 5

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9645 |
| F1 Score | 0.9267 |
| mAP@0.5 | 0.9645 |
| mAP@0.5:0.95 | 0.7528 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9436 | 0.7110 |
| toy | 0.9620 | 0.7568 |
| ball | 0.9698 | 0.7834 |
| human | 0.9752 | 0.7216 |
| hedgehog | 0.9719 | 0.7914 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 542 | 117 | 168 | 13 | 169 |
| obstacle | 82 | 2053 | 0 | 0 | 3 | 0 |
| toy | 23 | 8 | 1315 | 4 | 0 | 118 |
| ball | 19 | 0 | 0 | 820 | 0 | 27 |
| human | 5 | 5 | 0 | 0 | 170 | 0 |
| hedgehog | 2 | 0 | 0 | 1 | 0 | 995 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9568 |
| F1 Score | 0.9240 |
| mAP@0.5 | 0.9568 |
| mAP@0.5:0.95 | 0.7466 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9478 | 0.7063 |
| toy | 0.9705 | 0.7852 |
| ball | 0.9655 | 0.8148 |
| human | 0.9444 | 0.6680 |
| hedgehog | 0.9559 | 0.7589 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 52 | 15 | 12 | 0 | 30 |
| obstacle | 6 | 169 | 0 | 0 | 0 | 0 |
| toy | 1 | 1 | 154 | 0 | 0 | 12 |
| ball | 2 | 0 | 0 | 89 | 0 | 2 |
| human | 1 | 1 | 0 | 0 | 16 | 0 |
| hedgehog | 2 | 0 | 0 | 0 | 0 | 115 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9567 |
| F1 Score | 0.9287 |
| mAP@0.5 | 0.9567 |
| mAP@0.5:0.95 | 0.7791 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9658 | 0.7399 |
| toy | 0.9535 | 0.7984 |
| ball | 0.9595 | 0.7994 |
| human | 0.9444 | 0.7782 |
| hedgehog | 0.9600 | 0.7796 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 35 | 7 | 6 | 0 | 15 |
| obstacle | 4 | 99 | 0 | 0 | 0 | 0 |
| toy | 0 | 0 | 63 | 1 | 0 | 7 |
| ball | 3 | 0 | 0 | 42 | 0 | 1 |
| human | 1 | 0 | 0 | 0 | 8 | 0 |
| hedgehog | 2 | 0 | 0 | 0 | 0 | 55 |
