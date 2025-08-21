# Model performance and validation report
**Source model:** C:/Users/RoserM/Documents/Code/ML/CAPSENSE/Water_detection/DEEPCRAFT_PROJECT/WaterDetection_AIKit/Model/conv1d-small-accuracy-2/conv1d-small-accuracy-2.h5  
**Generated:** 2025-07-09 10:11:13

### Memory usage
| Model | Model memory (Bytes) | Scratch memory (Bytes) |
| :--- | :--- | :--- |
| float | 66,436 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 42,383 |
| CONV_2D | 280,509 |
| CONV_2D | 492,665 |
| MAX_POOL_2D | 14,784 |
| FULLY_CONNECTED | 96,366 |
| FULLY_CONNECTED | 2,485 |
| SOFTMAX | 0 |
| **TOTAL** | **929,192** |

### Validation
**Validation data source:** Project File

| Metric | Float model |
| :--- | :--- |
| Classification difference from reference model | 0 / 1,000 |
| Relative accuracy | 100.0% |

