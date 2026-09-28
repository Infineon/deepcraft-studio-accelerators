# Evaluation Results: yolo26n-size224-batch128-epoch200

- **Project type:** ObjectDetection
- **Classes:** 2

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9781 |
| F1 Score | 0.9781 |
| mAP@0.5 | 0.9838 |
| mAP@0.5:0.95 | 0.7948 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Drone | 0.9728 | 0.7245 |
| Bird | 0.9947 | 0.8652 |

### Confusion Matrix

| True \ Pred | (none) | Drone | Bird |
| --- | --- | --- | --- |
| (none) | 0 | 153 | 68 |
| Drone | 65 | 3119 | 1 |
| Bird | 10 | 5 | 2087 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9486 |
| F1 Score | 0.9486 |
| mAP@0.5 | 0.9500 |
| mAP@0.5:0.95 | 0.6964 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Drone | 0.9399 | 0.6411 |
| Bird | 0.9601 | 0.7516 |

### Confusion Matrix

| True \ Pred | (none) | Drone | Bird |
| --- | --- | --- | --- |
| (none) | 0 | 56 | 35 |
| Drone | 46 | 891 | 5 |
| Bird | 16 | 5 | 555 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9582 |
| F1 Score | 0.9580 |
| mAP@0.5 | 0.9572 |
| mAP@0.5:0.95 | 0.6849 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Drone | 0.9401 | 0.6074 |
| Bird | 0.9743 | 0.7625 |

### Confusion Matrix

| True \ Pred | (none) | Drone | Bird |
| --- | --- | --- | --- |
| (none) | 0 | 26 | 18 |
| Drone | 23 | 421 | 0 |
| Bird | 2 | 5 | 316 |
