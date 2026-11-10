# Evaluation Results: yolo26n-size320-batch16-epoch200

- **Project type:** ObjectDetection
- **Classes:** 4

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9949 |
| F1 Score | 0.9949 |
| mAP@0.5 | 0.9949 |
| mAP@0.5:0.95 | 0.9002 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| black_measles | 0.9947 | 0.8886 |
| black_rot | 0.9950 | 0.9019 |
| leaf_blight | 0.9950 | 0.9275 |
| healthy | 0.9950 | 0.8829 |

### Confusion Matrix

| True \ Pred | (none) | black_measles | black_rot | leaf_blight | healthy |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 92 | 19 | 7 | 5 |
| black_measles | 3 | 1036 | 0 | 0 | 0 |
| black_rot | 1 | 0 | 833 | 0 | 0 |
| leaf_blight | 0 | 0 | 0 | 779 | 0 |
| healthy | 0 | 0 | 0 | 0 | 407 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9823 |
| F1 Score | 0.9822 |
| mAP@0.5 | 0.9709 |
| mAP@0.5:0.95 | 0.8772 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| black_measles | 0.9226 | 0.8312 |
| black_rot | 0.9711 | 0.8836 |
| leaf_blight | 0.9950 | 0.9261 |
| healthy | 0.9950 | 0.8678 |

### Confusion Matrix

| True \ Pred | (none) | black_measles | black_rot | leaf_blight | healthy |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 24 | 3 | 4 | 1 |
| black_measles | 26 | 319 | 0 | 0 | 0 |
| black_rot | 7 | 0 | 268 | 0 | 0 |
| leaf_blight | 0 | 0 | 0 | 259 | 0 |
| healthy | 0 | 0 | 0 | 0 | 135 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9807 |
| F1 Score | 0.9805 |
| mAP@0.5 | 0.9655 |
| mAP@0.5:0.95 | 0.8677 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| black_measles | 0.9013 | 0.7996 |
| black_rot | 0.9707 | 0.8793 |
| leaf_blight | 0.9950 | 0.9246 |
| healthy | 0.9950 | 0.8672 |

### Confusion Matrix

| True \ Pred | (none) | black_measles | black_rot | leaf_blight | healthy |
| --- | --- | --- | --- | --- | --- |
| (none) | 0 | 23 | 4 | 5 | 1 |
| black_measles | 32 | 322 | 0 | 0 | 0 |
| black_rot | 6 | 0 | 271 | 0 | 1 |
| leaf_blight | 0 | 0 | 0 | 263 | 0 |
| healthy | 1 | 0 | 0 | 0 | 140 |
