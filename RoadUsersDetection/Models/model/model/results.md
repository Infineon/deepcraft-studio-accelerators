# Evaluation Results: model

- **Project type:** ObjectDetection
- **Classes:** 6

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.7559 |
| F1 Score | 0.7196 |
| mAP@0.5 | 0.7559 |
| mAP@0.5:0.95 | 0.5499 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.8490 | 0.6333 |
| bicycle | 0.6838 | 0.4765 |
| person | 0.7277 | 0.4805 |
| motorbike | 0.7635 | 0.5389 |
| car | 0.6811 | 0.4890 |
| bus | 0.8304 | 0.6811 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 133 | 462 | 3245 | 326 | 1033 | 125 |
| train | 116 | 507 | 0 | 1 | 2 | 2 | 9 |
| bicycle | 218 | 0 | 511 | 10 | 16 | 2 | 0 |
| person | 1523 | 0 | 9 | 4509 | 19 | 9 | 0 |
| motorbike | 159 | 0 | 38 | 40 | 477 | 11 | 0 |
| car | 784 | 4 | 3 | 8 | 6 | 1434 | 15 |
| bus | 128 | 13 | 0 | 2 | 0 | 27 | 451 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.7426 |
| F1 Score | 0.7059 |
| mAP@0.5 | 0.7426 |
| mAP@0.5:0.95 | 0.5359 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.7893 | 0.5741 |
| bicycle | 0.6846 | 0.4909 |
| person | 0.7215 | 0.4905 |
| motorbike | 0.8190 | 0.5396 |
| car | 0.6367 | 0.4640 |
| bus | 0.8048 | 0.6561 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 6 | 38 | 178 | 22 | 89 | 7 |
| train | 7 | 26 | 0 | 0 | 0 | 0 | 0 |
| bicycle | 5 | 0 | 30 | 3 | 0 | 1 | 0 |
| person | 75 | 0 | 1 | 241 | 0 | 0 | 0 |
| motorbike | 4 | 0 | 3 | 1 | 27 | 2 | 0 |
| car | 40 | 0 | 1 | 0 | 0 | 74 | 1 |
| bus | 8 | 1 | 0 | 0 | 0 | 0 | 22 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.7539 |
| F1 Score | 0.7097 |
| mAP@0.5 | 0.7539 |
| mAP@0.5:0.95 | 0.5342 |

### Per-class mAP

| Class | mAP@0.5 | mAP@0.5:0.95 |
| --- | --- | --- |
| train | 0.8391 | 0.6343 |
| bicycle | 0.6815 | 0.4617 |
| person | 0.7121 | 0.4747 |
| motorbike | 0.7695 | 0.5053 |
| car | 0.7068 | 0.4696 |
| bus | 0.8143 | 0.6596 |

### Confusion Matrix

| True \ Pred | (none) | train | bicycle | person | motorbike | car | bus |
| --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 8 | 23 | 193 | 18 | 56 | 9 |
| train | 7 | 26 | 0 | 1 | 0 | 0 | 0 |
| bicycle | 13 | 0 | 28 | 0 | 0 | 0 | 0 |
| person | 82 | 0 | 0 | 247 | 0 | 0 | 0 |
| motorbike | 10 | 0 | 1 | 2 | 26 | 0 | 0 |
| car | 39 | 0 | 0 | 0 | 2 | 79 | 2 |
| bus | 9 | 0 | 0 | 0 | 0 | 1 | 23 |
