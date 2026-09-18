# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 5

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9852 |
| F1 Score | 0.9664 |
| mAP@0.5 | 0.9852 |
| mAP@0.5:0.95 | 0.7742 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9737 | 0.7548 |
| toy | 0.9899 | 0.8048 |
| ball | 0.9882 | 0.7716 |
| human | 0.9826 | 0.7171 |
| hedgehog | 0.9917 | 0.8226 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 404 | 74 | 183 | 28 | 47 |
| obstacle | 31 | 2104 | 0 | 0 | 3 | 0 |
| toy | 20 | 1 | 1443 | 1 | 0 | 3 |
| ball | 3 | 0 | 0 | 858 | 0 | 5 |
| human | 3 | 0 | 1 | 0 | 176 | 0 |
| hedgehog | 6 | 0 | 1 | 3 | 0 | 988 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9770 |
| F1 Score | 0.9520 |
| mAP@0.5 | 0.9770 |
| mAP@0.5:0.95 | 0.7703 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9592 | 0.7265 |
| toy | 0.9892 | 0.8127 |
| ball | 0.9819 | 0.8019 |
| human | 0.9646 | 0.7096 |
| hedgehog | 0.9899 | 0.8010 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 41 | 9 | 16 | 3 | 8 |
| obstacle | 2 | 173 | 0 | 0 | 0 | 0 |
| toy | 3 | 0 | 165 | 0 | 0 | 0 |
| ball | 0 | 0 | 0 | 92 | 0 | 1 |
| human | 1 | 0 | 0 | 0 | 17 | 0 |
| hedgehog | 1 | 0 | 1 | 0 | 0 | 115 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9661 |
| F1 Score | 0.9361 |
| mAP@0.5 | 0.9661 |
| mAP@0.5:0.95 | 0.7665 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| obstacle | 0.9276 | 0.7180 |
| toy | 0.9808 | 0.8284 |
| ball | 0.9681 | 0.7733 |
| human | 0.9750 | 0.7062 |
| hedgehog | 0.9788 | 0.8066 |

### Confusion Matrix

| True \ Pred | (none) | obstacle | toy | ball | human | hedgehog |
| --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 25 | 9 | 7 | 4 | 6 |
| obstacle | 1 | 102 | 0 | 0 | 0 | 0 |
| toy | 1 | 0 | 69 | 1 | 0 | 0 |
| ball | 1 | 0 | 0 | 44 | 0 | 1 |
| human | 0 | 0 | 0 | 0 | 9 | 0 |
| hedgehog | 2 | 0 | 0 | 1 | 0 | 54 |
