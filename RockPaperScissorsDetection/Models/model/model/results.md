# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9786 |
| F1 Score | 0.9605 |
| mAP@0.5 | 0.9786 |
| mAP@0.5:0.95 | 0.6970 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.9889 | 0.7101 |
| Paper | 0.9771 | 0.7098 |
| Rock | 0.9699 | 0.6711 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 12 | 38 | 39 |
| Scissors | 12 | 939 | 2 | 3 |
| Paper | 16 | 1 | 536 | 2 |
| Rock | 16 | 0 | 2 | 561 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9567 |
| F1 Score | 0.9202 |
| mAP@0.5 | 0.9567 |
| mAP@0.5:0.95 | 0.6414 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.9607 | 0.6443 |
| Paper | 0.9728 | 0.6618 |
| Rock | 0.9364 | 0.6181 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 5 | 18 | 21 |
| Scissors | 11 | 303 | 0 | 4 |
| Paper | 6 | 1 | 176 | 2 |
| Rock | 12 | 0 | 1 | 179 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9576 |
| F1 Score | 0.9268 |
| mAP@0.5 | 0.9576 |
| mAP@0.5:0.95 | 0.6365 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.9741 | 0.6548 |
| Paper | 0.9548 | 0.6595 |
| Rock | 0.9439 | 0.5951 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 10 | 16 | 15 |
| Scissors | 11 | 307 | 0 | 1 |
| Paper | 5 | 8 | 170 | 3 |
| Rock | 13 | 2 | 1 | 176 |
