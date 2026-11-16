# Evaluation Results: yolo26n-size224-batch64-epoch100

- **Project type:** ImageClassification
- **Classes:** 3

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 1.0000 |
| F1 Score | 1.0000 |

### Confusion Matrix

| True \ Pred | (none) | Benign | Normal_Skin | Suspicious |
| --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 |
| Benign | 0 | 283 | 0 | 0 |
| Normal_Skin | 0 | 0 | 300 | 0 |
| Suspicious | 0 | 0 | 0 | 1433 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.9295 |
| F1 Score | 0.9176 |

### Confusion Matrix

| True \ Pred | (none) | Benign | Normal_Skin | Suspicious |
| --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 |
| Benign | 0 | 81 | 0 | 21 |
| Normal_Skin | 0 | 0 | 66 | 2 |
| Suspicious | 0 | 13 | 1 | 341 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.9310 |
| F1 Score | 0.9129 |

### Confusion Matrix

| True \ Pred | (none) | Benign | Normal_Skin | Suspicious |
| --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 |
| Benign | 0 | 73 | 1 | 20 |
| Normal_Skin | 0 | 0 | 75 | 3 |
| Suspicious | 0 | 11 | 1 | 338 |
