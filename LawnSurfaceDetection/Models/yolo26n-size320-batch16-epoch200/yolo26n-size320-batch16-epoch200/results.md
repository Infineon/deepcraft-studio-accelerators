# Evaluation Results: yolo26n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.8804 |
| F1 Score | 0.8804 |
| mAP@0.5 | 0.9099 |
| mAP@0.5:0.95 | 0.7346 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| grass | 0.9493 | 0.8400 |
| soil | 0.9545 | 0.9041 |
| road | 0.8737 | 0.6541 |
| flower | 0.8620 | 0.5403 |

### Confusion Matrix

| True \ Pred | (none) | grass | soil | road | flower |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 405 | 335 | 365 | 183 |
| grass | 44 | 1439 | 0 | 0 | 0 |
| soil | 53 | 0 | 1447 | 0 | 0 |
| road | 33 | 0 | 0 | 867 | 0 |
| flower | 200 | 1 | 0 | 0 | 1447 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.8446 |
| F1 Score | 0.8446 |
| mAP@0.5 | 0.8542 |
| mAP@0.5:0.95 | 0.6796 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| grass | 0.9420 | 0.8135 |
| soil | 0.9236 | 0.8757 |
| road | 0.8565 | 0.6188 |
| flower | 0.6947 | 0.4103 |

### Confusion Matrix

| True \ Pred | (none) | grass | soil | road | flower |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 158 | 117 | 127 | 133 |
| grass | 12 | 475 | 0 | 0 | 0 |
| soil | 23 | 0 | 477 | 0 | 0 |
| road | 15 | 0 | 0 | 285 | 0 |
| flower | 155 | 0 | 0 | 0 | 453 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.8587 |
| F1 Score | 0.8583 |
| mAP@0.5 | 0.8717 |
| mAP@0.5:0.95 | 0.7000 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| grass | 0.9399 | 0.8229 |
| soil | 0.9616 | 0.8894 |
| road | 0.8825 | 0.6519 |
| flower | 0.7027 | 0.4359 |

### Confusion Matrix

| True \ Pred | (none) | grass | soil | road | flower |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 125 | 113 | 124 | 109 |
| grass | 22 | 468 | 1 | 0 | 0 |
| soil | 10 | 0 | 490 | 0 | 0 |
| road | 8 | 0 | 0 | 292 | 0 |
| flower | 135 | 0 | 1 | 0 | 418 |
