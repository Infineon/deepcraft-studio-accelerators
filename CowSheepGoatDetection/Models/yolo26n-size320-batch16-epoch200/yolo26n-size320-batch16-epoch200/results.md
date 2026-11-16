# Evaluation Results: yolo26n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9600 |
| F1 Score | 0.9600 |
| mAP@0.5 | 0.9722 |
| mAP@0.5:0.95 | 0.8221 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9837 | 0.8685 |
| sheep | 0.9721 | 0.7892 |
| goat | 0.9609 | 0.8086 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 243 | 279 | 271 |
| cow | 61 | 4400 | 0 | 0 |
| sheep | 83 | 0 | 3216 | 0 |
| goat | 81 | 0 | 0 | 2581 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8732 |
| F1 Score | 0.8720 |
| mAP@0.5 | 0.8546 |
| mAP@0.5:0.95 | 0.6642 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9303 | 0.7988 |
| sheep | 0.8225 | 0.5884 |
| goat | 0.8110 | 0.6053 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 129 | 170 | 171 |
| cow | 86 | 1362 | 3 | 9 |
| sheep | 157 | 2 | 929 | 10 |
| goat | 131 | 0 | 5 | 803 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8762 |
| F1 Score | 0.8749 |
| mAP@0.5 | 0.8551 |
| mAP@0.5:0.95 | 0.6620 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9306 | 0.8051 |
| sheep | 0.8158 | 0.5808 |
| goat | 0.8188 | 0.6002 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 119 | 184 | 168 |
| cow | 75 | 1438 | 11 | 5 |
| sheep | 165 | 2 | 978 | 14 |
| goat | 144 | 0 | 8 | 832 |
