# Evaluation Results: yolo26n-size224-batch128-epoch200

- **Project type:** ObjectDetection
- **Classes:** 2

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9783 |
| F1 Score | 0.9783 |
| mAP@0.5 | 0.9837 |
| mAP@0.5:0.95 | 0.7993 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Drone | 0.9730 | 0.7322 |
| Bird | 0.9945 | 0.8664 |

### Confusion Matrix

| True \ Pred | (none) | Drone | Bird |
| --- | --- | --- | --- |
| (none) | 0 | 155 | 63 |
| Drone | 60 | 3125 | 0 |
| Bird | 8 | 2 | 2092 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9574 |
| F1 Score | 0.9573 |
| mAP@0.5 | 0.9566 |
| mAP@0.5:0.95 | 0.6990 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Drone | 0.9399 | 0.6418 |
| Bird | 0.9732 | 0.7562 |

### Confusion Matrix

| True \ Pred | (none) | Drone | Bird |
| --- | --- | --- | --- |
| (none) | 0 | 68 | 23 |
| Drone | 47 | 891 | 4 |
| Bird | 12 | 4 | 560 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9579 |
| F1 Score | 0.9578 |
| mAP@0.5 | 0.9602 |
| mAP@0.5:0.95 | 0.6838 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Drone | 0.9366 | 0.6057 |
| Bird | 0.9839 | 0.7619 |

### Confusion Matrix

| True \ Pred | (none) | Drone | Bird |
| --- | --- | --- | --- |
| (none) | 0 | 33 | 14 |
| Drone | 23 | 421 | 0 |
| Bird | 2 | 2 | 319 |
