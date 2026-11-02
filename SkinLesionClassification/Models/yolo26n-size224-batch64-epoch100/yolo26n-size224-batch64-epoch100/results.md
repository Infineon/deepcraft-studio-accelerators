# Evaluation Results: yolo26n-size224-batch64-epoch100

- **Project type:** ImageClassification
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.9995 |
| F1 Score | 0.9993 |

### Confusion Matrix

| True \ Pred | (none) | Benign | Normal_Skin | Suspicious |
| --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 |
| Benign | 0 | 283 | 0 | 0 |
| Normal_Skin | 0 | 0 | 300 | 0 |
| Suspicious | 0 | 1 | 0 | 1432 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9314 |
| F1 Score | 0.9190 |

### Confusion Matrix

| True \ Pred | (none) | Benign | Normal_Skin | Suspicious |
| --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 |
| Benign | 0 | 82 | 0 | 20 |
| Normal_Skin | 0 | 1 | 65 | 2 |
| Suspicious | 0 | 13 | 0 | 342 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9176 |
| F1 Score | 0.8952 |

### Confusion Matrix

| True \ Pred | (none) | Benign | Normal_Skin | Suspicious |
| --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 |
| Benign | 0 | 67 | 1 | 26 |
| Normal_Skin | 0 | 0 | 76 | 2 |
| Suspicious | 0 | 13 | 1 | 336 |
