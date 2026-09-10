# Evaluation Results: yolo26n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9574 |
| F1 Score | 0.9572 |
| mAP@0.5 | 0.9721 |
| mAP@0.5:0.95 | 0.8191 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9833 | 0.8700 |
| sheep | 0.9723 | 0.7871 |
| goat | 0.9606 | 0.8001 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 341 | 325 | 294 |
| cow | 56 | 4405 | 0 | 0 |
| sheep | 78 | 0 | 3221 | 0 |
| goat | 83 | 0 | 0 | 2579 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8703 |
| F1 Score | 0.8691 |
| mAP@0.5 | 0.8517 |
| mAP@0.5:0.95 | 0.6625 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9196 | 0.7949 |
| sheep | 0.8235 | 0.5900 |
| goat | 0.8121 | 0.6025 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 135 | 169 | 180 |
| cow | 90 | 1355 | 10 | 5 |
| sheep | 154 | 1 | 934 | 9 |
| goat | 130 | 0 | 9 | 800 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8715 |
| F1 Score | 0.8701 |
| mAP@0.5 | 0.8629 |
| mAP@0.5:0.95 | 0.6679 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| cow | 0.9399 | 0.8080 |
| sheep | 0.8274 | 0.5886 |
| goat | 0.8214 | 0.6071 |

### Confusion Matrix

| True \ Pred | (none) | cow | sheep | goat |
| --- | --- | --- | --- | --- |
| (none) | 0 | 146 | 210 | 181 |
| cow | 68 | 1447 | 7 | 7 |
| sheep | 152 | 3 | 990 | 14 |
| goat | 135 | 0 | 13 | 836 |
