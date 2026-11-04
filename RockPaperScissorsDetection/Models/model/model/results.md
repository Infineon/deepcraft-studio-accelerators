# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.4001 |
| F1 Score | 0.4128 |
| mAP@0.5 | 0.4001 |
| mAP@0.5:0.95 | 0.1892 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.4404 | 0.2181 |
| Paper | 0.3727 | 0.1525 |
| Rock | 0.3872 | 0.1971 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 542 | 2830 | 156 |
| Scissors | 201 | 337 | 416 | 2 |
| Paper | 102 | 0 | 450 | 3 |
| Rock | 239 | 3 | 165 | 172 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.3528 |
| F1 Score | 0.3997 |
| mAP@0.5 | 0.3528 |
| mAP@0.5:0.95 | 0.1703 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.4031 | 0.1950 |
| Paper | 0.2933 | 0.1232 |
| Rock | 0.3619 | 0.1928 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 183 | 966 | 68 |
| Scissors | 89 | 92 | 134 | 3 |
| Paper | 36 | 0 | 149 | 0 |
| Rock | 78 | 0 | 52 | 62 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.3967 |
| F1 Score | 0.4414 |
| mAP@0.5 | 0.3967 |
| mAP@0.5:0.95 | 0.1889 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| Scissors | 0.4449 | 0.2341 |
| Paper | 0.3692 | 0.1557 |
| Rock | 0.3758 | 0.1768 |

### Confusion Matrix

| True \ Pred | (none) | Scissors | Paper | Rock |
| --- | --- | --- | --- | --- |
| (none) | 0 | 200 | 924 | 41 |
| Scissors | 71 | 127 | 119 | 2 |
| Paper | 31 | 0 | 154 | 1 |
| Rock | 81 | 1 | 63 | 47 |
