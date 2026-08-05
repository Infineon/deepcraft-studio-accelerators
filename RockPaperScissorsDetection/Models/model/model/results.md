# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9897 |
| F1 Score | 0.9824 |
| mAP@0.5 | 0.9897 |
| mAP@0.5:0.95 | 0.7399 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.9929 | 0.7510 |
| Paper | 0.9889 | 0.7459 |
| Rock | 0.9873 | 0.7227 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 17 | 31 | 13 |
| Scissors | 2 | 953 | 1 | 0 |
| Paper | 5 | 3 | 547 | 0 |
| Rock | 0 | 1 | 0 | 578 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9699 |
| F1 Score | 0.9512 |
| mAP@0.5 | 0.9699 |
| mAP@0.5:0.95 | 0.6639 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.9773 | 0.6658 |
| Paper | 0.9710 | 0.6549 |
| Rock | 0.9615 | 0.6709 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 5 | 6 | 10 |
| Scissors | 4 | 313 | 0 | 1 |
| Paper | 7 | 2 | 175 | 1 |
| Rock | 5 | 0 | 0 | 187 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9638 |
| F1 Score | 0.9414 |
| mAP@0.5 | 0.9638 |
| mAP@0.5:0.95 | 0.6579 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.9796 | 0.6665 |
| Paper | 0.9469 | 0.6689 |
| Rock | 0.9650 | 0.6382 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 11 | 10 | 5 |
| Scissors | 5 | 312 | 1 | 1 |
| Paper | 11 | 6 | 168 | 1 |
| Rock | 7 | 4 | 2 | 179 |
