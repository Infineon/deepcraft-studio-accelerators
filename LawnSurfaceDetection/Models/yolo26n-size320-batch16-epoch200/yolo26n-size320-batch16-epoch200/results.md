# Evaluation Results: yolo26n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8610 |
| F1 Score | 0.8609 |
| mAP@0.5 | 0.8968 |
| mAP@0.5:0.95 | 0.7118 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| grass | 0.9406 | 0.8476 |
| soil | 0.9118 | 0.8377 |
| road | 0.9154 | 0.6659 |
| flower | 0.8194 | 0.4960 |

### Confusion Matrix

| True \ Pred | (none) | grass | soil | road | flower |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 542 | 720 | 519 | 199 |
| grass | 63 | 1420 | 0 | 0 | 0 |
| soil | 62 | 2 | 1436 | 0 | 0 |
| road | 2 | 0 | 0 | 898 | 0 |
| flower | 253 | 3 | 0 | 0 | 1392 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8309 |
| F1 Score | 0.8307 |
| mAP@0.5 | 0.8523 |
| mAP@0.5:0.95 | 0.6774 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| grass | 0.9392 | 0.8281 |
| soil | 0.8908 | 0.8153 |
| road | 0.9057 | 0.6624 |
| flower | 0.6735 | 0.4039 |

### Confusion Matrix

| True \ Pred | (none) | grass | soil | road | flower |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 201 | 244 | 195 | 120 |
| grass | 15 | 472 | 0 | 0 | 0 |
| soil | 27 | 1 | 472 | 0 | 0 |
| road | 1 | 0 | 0 | 299 | 0 |
| flower | 164 | 2 | 0 | 0 | 442 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8343 |
| F1 Score | 0.8341 |
| mAP@0.5 | 0.8558 |
| mAP@0.5:0.95 | 0.6770 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| grass | 0.9202 | 0.8206 |
| soil | 0.9018 | 0.8107 |
| road | 0.9018 | 0.6562 |
| flower | 0.6994 | 0.4205 |

### Confusion Matrix

| True \ Pred | (none) | grass | soil | road | flower |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 189 | 255 | 186 | 96 |
| grass | 30 | 461 | 0 | 0 | 0 |
| soil | 20 | 0 | 480 | 0 | 0 |
| road | 1 | 0 | 0 | 299 | 0 |
| flower | 137 | 0 | 0 | 0 | 417 |
