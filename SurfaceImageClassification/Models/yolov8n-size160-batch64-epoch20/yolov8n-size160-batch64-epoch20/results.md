# Evaluation Results: yolov8n-size160-batch64-epoch20

- **Project type:** ImageClassification
- **Classes:** 27

## Train

| Metric | Value |
| --- | --- |
| Accuracy | 0.5214 |
| F1 Score | 0.0000 |

### Confusion Matrix

| True \ Pred | (none) | dry_asphalt_severe | dry_asphalt_slight | dry_asphalt_smooth | dry_concrete_severe | dry_concrete_slight | dry_concrete_smooth | dry_gravel | dry_mud | fresh_snow | ice | melted_snow | water_asphalt_severe | water_asphalt_slight | water_asphalt_smooth | water_concrete_severe | water_concrete_slight | water_concrete_smooth | water_gravel | water_mud | wet_asphalt_severe | wet_asphalt_slight | wet_asphalt_smooth | wet_concrete_severe | wet_concrete_slight | wet_concrete_smooth | wet_gravel | wet_mud |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| dry_asphalt_severe | 0 | 78 | 9 | 3 | 7 | 10 | 1 | 2 | 3 | 1 | 6 | 1 | 3 | 5 | 5 | 3 | 5 | 2 | 1 | 0 | 20 | 7 | 0 | 6 | 2 | 0 | 0 | 3 |
| dry_asphalt_slight | 0 | 1 | 72 | 9 | 6 | 14 | 4 | 19 | 1 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 22 | 20 | 2 | 2 | 2 | 2 | 2 | 3 |
| dry_asphalt_smooth | 0 | 2 | 3 | 52 | 0 | 6 | 2 | 2 | 1 | 3 | 0 | 1 | 0 | 3 | 10 | 0 | 1 | 4 | 1 | 0 | 5 | 8 | 52 | 1 | 3 | 19 | 3 | 1 |
| dry_concrete_severe | 0 | 3 | 8 | 2 | 108 | 20 | 1 | 0 | 8 | 0 | 4 | 1 | 4 | 2 | 0 | 1 | 2 | 1 | 1 | 2 | 7 | 2 | 0 | 3 | 1 | 0 | 0 | 2 |
| dry_concrete_slight | 0 | 3 | 13 | 1 | 40 | 58 | 2 | 8 | 5 | 1 | 8 | 0 | 2 | 2 | 2 | 0 | 2 | 4 | 0 | 2 | 12 | 4 | 0 | 2 | 10 | 1 | 1 | 0 |
| dry_concrete_smooth | 0 | 3 | 0 | 6 | 1 | 4 | 107 | 0 | 0 | 8 | 0 | 0 | 0 | 4 | 10 | 0 | 0 | 6 | 0 | 4 | 1 | 1 | 1 | 0 | 1 | 26 | 0 | 0 |
| dry_gravel | 0 | 5 | 2 | 12 | 3 | 2 | 0 | 69 | 10 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 3 | 4 | 10 | 0 | 10 | 3 | 21 | 26 |
| dry_mud | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 5 | 92 | 4 | 3 | 1 | 1 | 0 | 0 | 1 | 0 | 10 | 1 | 1 | 0 | 1 | 0 | 8 | 10 | 3 | 6 | 33 |
| fresh_snow | 0 | 1 | 0 | 0 | 0 | 0 | 15 | 0 | 0 | 146 | 7 | 0 | 0 | 4 | 9 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| ice | 0 | 1 | 0 | 5 | 1 | 0 | 4 | 0 | 9 | 4 | 134 | 12 | 0 | 1 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 3 | 4 | 0 | 2 |
| melted_snow | 0 | 0 | 2 | 2 | 0 | 0 | 0 | 4 | 2 | 0 | 3 | 160 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 1 | 2 | 0 | 0 | 0 | 0 | 0 | 2 | 3 |
| water_asphalt_severe | 0 | 2 | 0 | 0 | 1 | 1 | 0 | 1 | 0 | 3 | 2 | 0 | 79 | 9 | 4 | 6 | 6 | 4 | 21 | 5 | 26 | 7 | 0 | 3 | 1 | 1 | 0 | 1 |
| water_asphalt_slight | 0 | 2 | 4 | 2 | 3 | 0 | 3 | 0 | 1 | 0 | 1 | 0 | 9 | 78 | 10 | 7 | 3 | 13 | 17 | 0 | 1 | 14 | 2 | 6 | 0 | 5 | 2 | 0 |
| water_asphalt_smooth | 0 | 2 | 0 | 2 | 0 | 0 | 1 | 0 | 0 | 5 | 4 | 0 | 2 | 7 | 111 | 4 | 2 | 15 | 8 | 2 | 1 | 2 | 2 | 0 | 0 | 10 | 2 | 1 |
| water_concrete_severe | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 1 | 0 | 0 | 15 | 14 | 4 | 55 | 12 | 15 | 37 | 6 | 5 | 2 | 0 | 10 | 1 | 1 | 0 | 3 |
| water_concrete_slight | 0 | 5 | 1 | 0 | 5 | 2 | 0 | 6 | 0 | 0 | 4 | 1 | 2 | 13 | 0 | 6 | 45 | 6 | 50 | 2 | 1 | 1 | 0 | 5 | 19 | 4 | 2 | 5 |
| water_concrete_smooth | 0 | 2 | 1 | 5 | 0 | 0 | 10 | 0 | 4 | 3 | 0 | 0 | 2 | 7 | 27 | 5 | 5 | 103 | 11 | 6 | 5 | 3 | 4 | 8 | 0 | 24 | 1 | 3 |
| water_gravel | 0 | 0 | 0 | 0 | 4 | 7 | 0 | 1 | 2 | 1 | 0 | 0 | 8 | 10 | 0 | 15 | 4 | 2 | 258 | 6 | 2 | 4 | 3 | 5 | 4 | 2 | 5 | 4 |
| water_mud | 0 | 0 | 0 | 0 | 8 | 4 | 3 | 1 | 9 | 6 | 2 | 0 | 5 | 0 | 0 | 5 | 1 | 1 | 37 | 85 | 0 | 1 | 0 | 2 | 5 | 0 | 3 | 13 |
| wet_asphalt_severe | 0 | 0 | 10 | 3 | 0 | 1 | 0 | 2 | 5 | 0 | 0 | 0 | 9 | 1 | 4 | 2 | 0 | 4 | 0 | 1 | 120 | 11 | 0 | 4 | 2 | 2 | 2 | 0 |
| wet_asphalt_slight | 0 | 0 | 9 | 9 | 2 | 0 | 1 | 1 | 3 | 0 | 0 | 2 | 2 | 0 | 4 | 0 | 0 | 6 | 0 | 0 | 19 | 91 | 8 | 4 | 2 | 3 | 16 | 1 |
| wet_asphalt_smooth | 0 | 0 | 0 | 8 | 0 | 0 | 2 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 9 | 0 | 0 | 4 | 1 | 1 | 6 | 1 | 126 | 0 | 0 | 19 | 3 | 0 |
| wet_concrete_severe | 0 | 1 | 4 | 0 | 10 | 1 | 0 | 8 | 3 | 0 | 0 | 0 | 7 | 0 | 0 | 1 | 4 | 7 | 9 | 2 | 10 | 13 | 0 | 71 | 17 | 0 | 10 | 5 |
| wet_concrete_slight | 0 | 0 | 0 | 5 | 5 | 11 | 0 | 6 | 5 | 0 | 2 | 0 | 0 | 2 | 0 | 1 | 3 | 3 | 9 | 0 | 2 | 6 | 1 | 25 | 72 | 1 | 15 | 9 |
| wet_concrete_smooth | 0 | 0 | 0 | 9 | 0 | 2 | 3 | 0 | 1 | 4 | 0 | 0 | 2 | 2 | 10 | 1 | 1 | 17 | 2 | 0 | 3 | 1 | 10 | 3 | 3 | 105 | 2 | 2 |
| wet_gravel | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 10 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 5 | 1 | 10 | 0 | 0 | 0 | 18 | 3 | 14 | 5 | 105 | 8 |
| wet_mud | 0 | 2 | 0 | 0 | 2 | 0 | 1 | 1 | 18 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 1 | 6 | 1 | 4 | 0 | 0 | 0 | 2 | 6 | 6 | 15 | 116 |

## Validation

| Metric | Value |
| --- | --- |
| Accuracy | 0.4977 |
| F1 Score | 0.0000 |

### Confusion Matrix

| True \ Pred | (none) | dry_asphalt_severe | dry_asphalt_slight | dry_asphalt_smooth | dry_concrete_severe | dry_concrete_slight | dry_concrete_smooth | dry_gravel | dry_mud | fresh_snow | ice | melted_snow | water_asphalt_severe | water_asphalt_slight | water_asphalt_smooth | water_concrete_severe | water_concrete_slight | water_concrete_smooth | water_gravel | water_mud | wet_asphalt_severe | wet_asphalt_slight | wet_asphalt_smooth | wet_concrete_severe | wet_concrete_slight | wet_concrete_smooth | wet_gravel | wet_mud |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| dry_asphalt_severe | 0 | 18 | 0 | 1 | 0 | 4 | 0 | 2 | 2 | 1 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 4 | 0 | 1 | 0 | 0 | 1 | 0 |
| dry_asphalt_slight | 0 | 0 | 18 | 1 | 0 | 3 | 1 | 2 | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 5 | 5 | 1 | 0 | 1 | 0 | 0 | 0 |
| dry_asphalt_smooth | 0 | 1 | 0 | 17 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 3 | 1 | 10 | 0 | 0 | 4 | 1 | 0 |
| dry_concrete_severe | 0 | 1 | 2 | 0 | 21 | 4 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 2 | 0 | 1 | 0 | 0 | 5 | 0 | 0 | 0 | 0 |
| dry_concrete_slight | 0 | 0 | 4 | 0 | 5 | 11 | 1 | 2 | 0 | 0 | 5 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 0 | 2 | 1 | 3 | 0 |
| dry_concrete_smooth | 0 | 0 | 0 | 2 | 0 | 0 | 16 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 6 | 0 | 0 | 5 | 0 | 1 | 0 | 1 | 0 | 0 | 1 | 6 | 0 | 0 |
| dry_gravel | 0 | 1 | 1 | 4 | 1 | 3 | 0 | 11 | 3 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 3 | 1 | 4 | 4 |
| dry_mud | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 5 | 16 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 1 | 2 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 2 | 5 |
| fresh_snow | 0 | 0 | 0 | 0 | 0 | 0 | 5 | 0 | 0 | 29 | 2 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| ice | 0 | 0 | 0 | 1 | 0 | 1 | 4 | 0 | 1 | 0 | 30 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| melted_snow | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 34 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
| water_asphalt_severe | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 18 | 0 | 0 | 2 | 0 | 2 | 3 | 0 | 8 | 1 | 0 | 1 | 1 | 1 | 0 | 0 |
| water_asphalt_slight | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 1 | 10 | 2 | 0 | 0 | 0 | 12 | 0 | 0 | 6 | 1 | 2 | 0 | 2 | 0 | 0 |
| water_asphalt_smooth | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 18 | 1 | 0 | 8 | 1 | 2 | 2 | 0 | 1 | 0 | 0 | 4 | 0 | 0 |
| water_concrete_severe | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 2 | 2 | 3 | 11 | 3 | 1 | 7 | 1 | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 5 |
| water_concrete_slight | 0 | 1 | 0 | 0 | 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 3 | 10 | 3 | 10 | 0 | 1 | 0 | 0 | 0 | 4 | 0 | 1 | 1 |
| water_concrete_smooth | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 1 | 1 | 0 | 1 | 2 | 3 | 2 | 0 | 24 | 3 | 1 | 0 | 0 | 0 | 1 | 0 | 8 | 0 | 2 |
| water_gravel | 0 | 0 | 0 | 0 | 3 | 2 | 0 | 1 | 0 | 0 | 0 | 0 | 4 | 1 | 0 | 0 | 1 | 0 | 56 | 0 | 2 | 2 | 0 | 0 | 1 | 0 | 1 | 1 |
| water_mud | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 2 | 0 | 0 | 2 | 0 | 1 | 0 | 1 | 12 | 14 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 5 |
| wet_asphalt_severe | 0 | 0 | 1 | 2 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 23 | 6 | 0 | 1 | 1 | 1 | 0 | 0 |
| wet_asphalt_slight | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 1 | 3 | 0 | 0 | 2 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 7 | 19 | 1 | 0 | 0 | 0 | 1 | 0 |
| wet_asphalt_smooth | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 1 | 0 | 2 | 0 | 0 | 22 | 0 | 0 | 7 | 1 | 0 |
| wet_concrete_severe | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 1 | 1 | 7 | 1 | 0 | 20 | 1 | 0 | 1 | 0 |
| wet_concrete_slight | 0 | 0 | 0 | 1 | 0 | 7 | 0 | 3 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 1 | 0 | 3 | 14 | 0 | 2 | 4 |
| wet_concrete_smooth | 0 | 0 | 1 | 2 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 2 | 0 | 0 | 4 | 0 | 0 | 1 | 0 | 1 | 1 | 1 | 23 | 1 | 0 |
| wet_gravel | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 3 | 0 | 3 | 0 | 23 | 4 |
| wet_mud | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 4 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 3 | 3 | 24 |

## Test

| Metric | Value |
| --- | --- |
| Accuracy | 0.4777 |
| F1 Score | 0.0000 |

### Confusion Matrix

| True \ Pred | (none) | dry_asphalt_severe | dry_asphalt_slight | dry_asphalt_smooth | dry_concrete_severe | dry_concrete_slight | dry_concrete_smooth | dry_gravel | dry_mud | fresh_snow | ice | melted_snow | water_asphalt_severe | water_asphalt_slight | water_asphalt_smooth | water_concrete_severe | water_concrete_slight | water_concrete_smooth | water_gravel | water_mud | wet_asphalt_severe | wet_asphalt_slight | wet_asphalt_smooth | wet_concrete_severe | wet_concrete_slight | wet_concrete_smooth | wet_gravel | wet_mud |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| (none) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| dry_asphalt_severe | 0 | 16 | 4 | 0 | 0 | 5 | 0 | 0 | 1 | 0 | 2 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 3 | 0 | 2 | 1 | 0 | 0 | 0 |
| dry_asphalt_slight | 0 | 0 | 15 | 4 | 2 | 1 | 4 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 7 | 0 | 2 | 0 | 0 | 0 | 0 |
| dry_asphalt_smooth | 0 | 0 | 0 | 6 | 0 | 0 | 2 | 2 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 16 | 1 | 1 | 4 | 1 | 0 |
| dry_concrete_severe | 0 | 0 | 0 | 0 | 24 | 2 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 3 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 0 | 2 | 0 | 0 | 0 | 1 |
| dry_concrete_slight | 0 | 2 | 2 | 1 | 7 | 10 | 1 | 0 | 1 | 0 | 3 | 0 | 2 | 0 | 1 | 0 | 0 | 2 | 0 | 0 | 0 | 2 | 0 | 1 | 3 | 0 | 0 | 0 |
| dry_concrete_smooth | 0 | 1 | 0 | 0 | 0 | 1 | 22 | 0 | 0 | 1 | 0 | 0 | 1 | 2 | 2 | 0 | 0 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 5 | 0 | 0 |
| dry_gravel | 0 | 0 | 0 | 5 | 1 | 0 | 0 | 12 | 2 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 3 | 2 | 4 | 0 | 5 | 2 |
| dry_mud | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 3 | 13 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 4 | 0 | 1 | 0 | 0 | 0 | 3 | 2 | 0 | 3 | 6 |
| fresh_snow | 0 | 0 | 0 | 0 | 0 | 1 | 7 | 0 | 0 | 26 | 1 | 0 | 1 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| ice | 0 | 1 | 0 | 1 | 1 | 0 | 1 | 0 | 3 | 1 | 25 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 2 | 0 | 0 |
| melted_snow | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 32 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 2 |
| water_asphalt_severe | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 9 | 2 | 1 | 1 | 3 | 1 | 8 | 0 | 8 | 3 | 0 | 1 | 0 | 0 | 0 | 0 |
| water_asphalt_slight | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 19 | 3 | 1 | 1 | 1 | 3 | 0 | 1 | 3 | 0 | 1 | 0 | 1 | 0 | 0 |
| water_asphalt_smooth | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 22 | 0 | 0 | 6 | 3 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 1 | 0 |
| water_concrete_severe | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 4 | 2 | 1 | 11 | 3 | 3 | 11 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 0 |
| water_concrete_slight | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 0 | 1 | 14 | 3 | 10 | 0 | 0 | 0 | 0 | 2 | 1 | 0 | 0 | 2 |
| water_concrete_smooth | 0 | 0 | 0 | 3 | 0 | 0 | 3 | 0 | 2 | 1 | 0 | 0 | 0 | 3 | 3 | 1 | 0 | 20 | 3 | 3 | 0 | 0 | 0 | 2 | 0 | 6 | 0 | 0 |
| water_gravel | 0 | 0 | 1 | 0 | 1 | 1 | 0 | 2 | 0 | 0 | 0 | 0 | 6 | 2 | 0 | 5 | 1 | 0 | 50 | 2 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
| water_mud | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 3 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 11 | 13 | 0 | 0 | 0 | 2 | 0 | 0 | 1 | 6 |
| wet_asphalt_severe | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 29 | 4 | 0 | 0 | 0 | 1 | 0 | 0 |
| wet_asphalt_slight | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 2 | 0 | 0 | 4 | 19 | 2 | 0 | 2 | 0 | 4 | 0 |
| wet_asphalt_smooth | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 2 | 1 | 23 | 1 | 0 | 7 | 1 | 0 |
| wet_concrete_severe | 0 | 0 | 1 | 0 | 2 | 1 | 0 | 2 | 0 | 0 | 0 | 1 | 2 | 0 | 0 | 0 | 1 | 2 | 1 | 0 | 7 | 1 | 0 | 11 | 5 | 0 | 1 | 0 |
| wet_concrete_slight | 0 | 0 | 1 | 0 | 0 | 5 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 3 | 1 | 0 | 0 | 0 | 0 | 1 | 6 | 11 | 0 | 4 | 3 |
| wet_concrete_smooth | 0 | 0 | 0 | 1 | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 4 | 2 | 0 | 6 | 0 | 0 | 0 | 0 | 2 | 1 | 1 | 16 | 1 | 0 |
| wet_gravel | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 2 | 0 | 2 | 1 | 25 | 3 |
| wet_mud | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 1 | 1 | 2 | 3 | 20 |
