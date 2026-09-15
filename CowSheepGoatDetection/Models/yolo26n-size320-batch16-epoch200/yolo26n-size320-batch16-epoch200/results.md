# Evaluation Results: yolo26n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9506 |
| F1 Score | 0.9505 |
| mAP@0.5 | 0.9645 |
| mAP@0.5:0.95 | 0.8049 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9830 | 0.8560 |
| sheep | 0.9618 | 0.7712 |
| goat | 0.9488 | 0.7875 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 343 | 297 | 339 |
| cow | 74 | 4387 | 0 | 0 |
| sheep | 105 | 0 | 3194 | 0 |
| goat | 108 | 0 | 0 | 2554 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8696 |
| F1 Score | 0.8688 |
| mAP@0.5 | 0.8540 |
| mAP@0.5:0.95 | 0.6582 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9293 | 0.7943 |
| sheep | 0.8110 | 0.5752 |
| goat | 0.8216 | 0.6049 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 138 | 180 | 179 |
| cow | 89 | 1362 | 1 | 8 |
| sheep | 163 | 2 | 917 | 16 |
| goat | 124 | 0 | 5 | 810 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8721 |
| F1 Score | 0.8712 |
| mAP@0.5 | 0.8588 |
| mAP@0.5:0.95 | 0.6626 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9390 | 0.7911 |
| sheep | 0.8181 | 0.5901 |
| goat | 0.8192 | 0.6068 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 135 | 194 | 166 |
| cow | 76 | 1441 | 8 | 4 |
| sheep | 153 | 5 | 985 | 16 |
| goat | 146 | 0 | 8 | 830 |
