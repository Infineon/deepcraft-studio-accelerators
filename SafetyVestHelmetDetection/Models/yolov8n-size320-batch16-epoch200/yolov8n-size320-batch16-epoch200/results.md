# Evaluation Results: yolov8n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8948 |
| F1 Score | 0.8928 |
| mAP@0.5 | 0.8783 |
| mAP@0.5:0.95 | 0.6618 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.8759 | 0.6678 |
| no_safety_vest | 0.8848 | 0.7100 |
| helmet | 0.8742 | 0.6047 |
| no_helmet | 0.8784 | 0.6649 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 523 | 646 | 521 | 282 |
| safety_vest | 400 | 3147 | 5 | 2 | 0 |
| no_safety_vest | 490 | 2 | 4462 | 2 | 1 |
| helmet | 460 | 1 | 2 | 4011 | 6 |
| no_helmet | 298 | 0 | 2 | 11 | 2387 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8323 |
| F1 Score | 0.8294 |
| mAP@0.5 | 0.7879 |
| mAP@0.5:0.95 | 0.5124 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.7896 | 0.5300 |
| no_safety_vest | 0.7582 | 0.5210 |
| helmet | 0.8137 | 0.4785 |
| no_helmet | 0.7901 | 0.5200 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 249 | 280 | 228 | 101 |
| safety_vest | 184 | 987 | 30 | 3 | 0 |
| no_safety_vest | 321 | 21 | 1326 | 2 | 1 |
| helmet | 222 | 4 | 6 | 1340 | 13 |
| no_helmet | 156 | 0 | 1 | 13 | 698 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8355 |
| F1 Score | 0.8326 |
| mAP@0.5 | 0.7959 |
| mAP@0.5:0.95 | 0.5178 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| safety_vest | 0.7875 | 0.5139 |
| no_safety_vest | 0.7720 | 0.5402 |
| helmet | 0.8127 | 0.4776 |
| no_helmet | 0.8115 | 0.5394 |

### Confusion Matrix

| True \ Pred | (none) | safety_vest | no_safety_vest | helmet | no_helmet |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 248 | 264 | 239 | 106 |
| safety_vest | 201 | 1030 | 24 | 0 | 0 |
| no_safety_vest | 309 | 14 | 1316 | 2 | 2 |
| helmet | 236 | 1 | 2 | 1295 | 4 |
| no_helmet | 143 | 0 | 1 | 15 | 758 |
