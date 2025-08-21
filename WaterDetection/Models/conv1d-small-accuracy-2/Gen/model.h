/*
* DEEPCRAFT Studio 5.5.3243+76c4d63272120e1aa149b27cfceadaf33de9e42c
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 07/09/2025 12:38:09 UTC. Any changes will be lost.
* 
* Model ID  7c3df5d5-7cc9-40fc-8678-7477a9568692
* 
* Memory    Size                      Efficiency
* Buffers   5440 bytes (RAM)          80 %
* State     480 bytes (RAM)           100 %
* Readonly  60896 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-small-accuracy-2
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | Dry
* 2           | Wet
* 3           | Touch
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [34,2]          float      dequeue
*    window_shape = [34,2]
*    stride = 14
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [34,2]          float      dequeue
*    contextual_length_sec = 0.5
*    prediction_freq = 10
* Input Layer                    [34,2]          float      dequeue
*    shape = [34,2]
* Convolution 1D                 [17,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,2,16]
* Batch Normalization            [17,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [17,16]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [17,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,32]
* Batch Normalization            [17,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [17,32]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [17,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [17,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [17,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [8,32]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Flatten                        [256]           float      dequeue
* Dense                          [40]            float      dequeue
*    units = 40
*    use_bias = False
*    activation = linear
*    trainable = True
*    weight = float[256,40]
* Batch Normalization            [40]            float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 1
*    gamma = float[40]
*    beta = float[40]
*    mean = float[40]
*    variance = float[40]
* Activation                     [40]            float      dequeue
*    activation = relu
*    trainable = True
* Dropout                        [40]            float      dequeue
*    rate = 0.1
*    trainable = True
* Dense                          [4]             float      dequeue
*    units = 4
*    use_bias = False
*    activation = linear
*    trainable = True
*    weight = float[40,4]
* Activation                     [4]             float      dequeue
*    activation = softmax
*    trainable = True
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[4].
* 
* int IMAI_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[2].
* 
* void IMAI_init(void)
*    Description: Initializes buffers to initial state. This function also works as a reset function.
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#ifndef _IMAI_MODEL_H_
#define _IMAI_MODEL_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>

typedef struct {    
    char *name;
    double TP; // True Positive or Correct Positive Prediction
    double FN; // False Negative or Incorrect Negative Prediction
    double FP; // False Positive or Incorrect Positive Prediction
    double TN; // True Negative or Correct Negative Prediction
    double TPR; // True Positive Rate or Sensitivity, Recall
    double TNR; // True Negative Rate or Specificity, Selectivity
    double PPV; // Positive Predictive Value or Precision
    double NPV; // Negative Predictive Value
    double FNR; // False Negative Rate or Miss Rate
    double FPR; // False Positive Rate or Fall-Out
    double FDR; // False Discovery Rate
    double FOR; // False Omission Rate
    double F1S; // F1 Score
} IMAI_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 91.032 %
* (F1S) F1 Score 90.804 %
* 
* Name of class                                            (unlabelled)              Dry            Touch              Wet
* (TP) True Positive or Correct Positive Prediction                2091             2516              217             3469
* (FN) False Negative or Incorrect Negative Prediction              738                0               24               55
* (FP) False Positive or Incorrect Positive Prediction               79               82              133              523
* (TN) True Negative or Correct Negative Prediction                6202             6512             8736             5063
* (TPR) True Positive Rate or Sensitivity, Recall               73.91 %         100.00 %          90.04 %          98.44 %
* (TNR) True Negative Rate or Specificity, Selectivity          98.74 %          98.76 %          98.50 %          90.64 %
* (PPV) Positive Predictive Value or Precision                  96.36 %          96.84 %          62.00 %          86.90 %
* (NPV) Negative Predictive Value                               89.37 %         100.00 %          99.73 %          98.93 %
* (FNR) False Negative Rate or Miss Rate                        26.09 %           0.00 %           9.96 %           1.56 %
* (FPR) False Positive Rate or Fall-Out                          1.26 %           1.24 %           1.50 %           9.36 %
* (FDR) False Discovery Rate                                     3.64 %           3.16 %          38.00 %          13.10 %
* (FOR) False Omission Rate                                     10.63 %           0.00 %           0.27 %           1.07 %
* (F1S) F1 Score                                                83.66 %          98.40 %          73.43 %          92.31 %
*/


#define IMAI_TEST_AVG_ACC 0.9103183315038419 // Accuracy
#define IMAI_TEST_AVG_F1S 0.9080438588821956 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "(unlabelled)", TP: 2091, FN: 738, FP: 79, TN: 6202, TPR: 0.7391304347826, TNR: 0.9874223849705, PPV: 0.9635944700460, NPV: 0.8936599423631, FNR: 0.2608695652173, FPR: 0.0125776150294, FDR: 0.0364055299539, FOR: 0.1063400576368, F1S: 0.8365673134626, }, \
 {name: "Dry", TP: 2516, FN: 0, FP: 82, TN: 6512, TPR: 1, TNR: 0.9875644525326, PPV: 0.9684372594303, NPV: 1, FNR: 0, FPR: 0.0124355474673, FDR: 0.0315627405696, FOR: 0, F1S: 0.9839655846695, }, \
 {name: "Wet", TP: 3469, FN: 55, FP: 523, TN: 5063, TPR: 0.9843927355278, TNR: 0.9063730755460, PPV: 0.8689879759519, NPV: 0.9892536146932, FNR: 0.0156072644721, FPR: 0.0936269244539, FDR: 0.1310120240480, FOR: 0.0107463853067, F1S: 0.9230973922299, }, \
 {name: "Touch", TP: 217, FN: 24, FP: 133, TN: 8736, TPR: 0.9004149377593, TNR: 0.9850039463299, PPV: 0.62, NPV: 0.9972602739726, FNR: 0.0995850622406, FPR: 0.0149960536700, FDR: 0.38, FOR: 0.0027397260273, F1S: 0.7343485617597, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 92.817 %
* (F1S) F1 Score 92.616 %
* 
* Name of class                                            (unlabelled)              Dry            Touch              Wet
* (TP) True Positive or Correct Positive Prediction                6731             8603              831             8527
* (FN) False Negative or Incorrect Negative Prediction             1792               41               70                8
* (FP) False Positive or Incorrect Positive Prediction              119              411              120             1261
* (TN) True Negative or Correct Negative Prediction               17961            17548            25582            16807
* (TPR) True Positive Rate or Sensitivity, Recall               78.97 %          99.53 %          92.23 %          99.91 %
* (TNR) True Negative Rate or Specificity, Selectivity          99.34 %          97.71 %          99.53 %          93.02 %
* (PPV) Positive Predictive Value or Precision                  98.26 %          95.44 %          87.38 %          87.12 %
* (NPV) Negative Predictive Value                               90.93 %          99.77 %          99.73 %          99.95 %
* (FNR) False Negative Rate or Miss Rate                        21.03 %           0.47 %           7.77 %           0.09 %
* (FPR) False Positive Rate or Fall-Out                          0.66 %           2.29 %           0.47 %           6.98 %
* (FDR) False Discovery Rate                                     1.74 %           4.56 %          12.62 %          12.88 %
* (FOR) False Omission Rate                                      9.07 %           0.23 %           0.27 %           0.05 %
* (F1S) F1 Score                                                87.57 %          97.44 %          89.74 %          93.07 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9281659963162049 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9261626740088496 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 6731, FN: 1792, FP: 119, TN: 17961, TPR: 0.7897453948140, TNR: 0.9934181415929, PPV: 0.9826277372262, NPV: 0.9092796030982, FNR: 0.2102546051859, FPR: 0.0065818584070, FDR: 0.0173722627737, FOR: 0.0907203969017, F1S: 0.8756911468158, }, \
 {name: "Dry", TP: 8603, FN: 41, FP: 411, TN: 17548, TPR: 0.9952568255437, TNR: 0.9771145386714, PPV: 0.9544042600399, NPV: 0.9976689976689, FNR: 0.0047431744562, FPR: 0.0228854613285, FDR: 0.0455957399600, FOR: 0.0023310023310, F1S: 0.9744025370936, }, \
 {name: "Wet", TP: 8527, FN: 8, FP: 1261, TN: 16807, TPR: 0.9990626830697, TNR: 0.9302081027230, PPV: 0.8711687780956, NPV: 0.9995242343146, FNR: 0.0009373169302, FPR: 0.0697918972769, FDR: 0.1288312219043, FOR: 0.0004757656853, F1S: 0.9307427822954, }, \
 {name: "Touch", TP: 831, FN: 70, FP: 120, TN: 25582, TPR: 0.9223085460599, TNR: 0.9953311026379, PPV: 0.8738170347003, NPV: 0.9972711679401, FNR: 0.0776914539400, FPR: 0.0046688973620, FDR: 0.1261829652996, FOR: 0.0027288320598, F1S: 0.8974082073434, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 92.395 %
* (F1S) F1 Score 92.387 %
* 
* Name of class                                            (unlabelled)              Dry            Touch              Wet
* (TP) True Positive or Correct Positive Prediction                2945             2767              234             2886
* (FN) False Negative or Incorrect Negative Prediction              502               27               21              177
* (FP) False Positive or Incorrect Positive Prediction              225              255              112              135
* (TN) True Negative or Correct Negative Prediction                5887             6510             9192             6361
* (TPR) True Positive Rate or Sensitivity, Recall               85.44 %          99.03 %          91.76 %          94.22 %
* (TNR) True Negative Rate or Specificity, Selectivity          96.32 %          96.23 %          98.80 %          97.92 %
* (PPV) Positive Predictive Value or Precision                  92.90 %          91.56 %          67.63 %          95.53 %
* (NPV) Negative Predictive Value                               92.14 %          99.59 %          99.77 %          97.29 %
* (FNR) False Negative Rate or Miss Rate                        14.56 %           0.97 %           8.24 %           5.78 %
* (FPR) False Positive Rate or Fall-Out                          3.68 %           3.77 %           1.20 %           2.08 %
* (FDR) False Discovery Rate                                     7.10 %           8.44 %          32.37 %           4.47 %
* (FOR) False Omission Rate                                      7.86 %           0.41 %           0.23 %           2.71 %
* (F1S) F1 Score                                                89.01 %          95.15 %          77.87 %          94.87 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.9239460194581023 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.9238730880567009 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 2945, FN: 502, FP: 225, TN: 5887, TPR: 0.8543661154627, TNR: 0.9631871727748, PPV: 0.9290220820189, NPV: 0.9214274534355, FNR: 0.1456338845372, FPR: 0.0368128272251, FDR: 0.0709779179810, FOR: 0.0785725465644, F1S: 0.8901314795224, }, \
 {name: "Dry", TP: 2767, FN: 27, FP: 255, TN: 6510, TPR: 0.9903364352183, TNR: 0.9623059866962, PPV: 0.9156187954996, NPV: 0.9958696649839, FNR: 0.0096635647816, FPR: 0.0376940133037, FDR: 0.0843812045003, FOR: 0.0041303350160, F1S: 0.9515130674002, }, \
 {name: "Wet", TP: 2886, FN: 177, FP: 135, TN: 6361, TPR: 0.9422135161606, TNR: 0.9792179802955, PPV: 0.9553128103277, NPV: 0.9729275007647, FNR: 0.0577864838393, FPR: 0.0207820197044, FDR: 0.0446871896722, FOR: 0.0270724992352, F1S: 0.9487179487179, }, \
 {name: "Touch", TP: 234, FN: 21, FP: 112, TN: 9192, TPR: 0.9176470588235, TNR: 0.9879621668099, PPV: 0.6763005780346, NPV: 0.9977206121784, FNR: 0.0823529411764, FPR: 0.0120378331900, FDR: 0.3236994219653, FOR: 0.0022793878215, F1S: 0.7787021630615, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"unlabelled", "Dry", "Wet", "Touch"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0xd5, 0xf5, 0x3d, 0x7c, 0xc9, 0x7c, 0xfc, 0x40, 0x86, 0x78, 0x74, 0x77, 0xa9, 0x56, 0x86, 0x92}

// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_QDYN8	(0x31)
#define IMAGINET_TYPES_QDYN16	(0x32)
#define IMAGINET_TYPES_QDYN32	(0x34)

// data_in [2] (8 bytes)
#define IMAI_DATA_IN_COUNT (2)
#define IMAI_DATA_IN_TYPE float
#define IMAI_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_IN_SCALE (1)
#define IMAI_DATA_IN_OFFSET (0)
#define IMAI_DATA_IN_IS_QUANTIZED (0)

// data_out [4] (16 bytes)
#define IMAI_DATA_OUT_COUNT (4)
#define IMAI_DATA_OUT_TYPE float
#define IMAI_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_OUT_SCALE (1)
#define IMAI_DATA_OUT_OFFSET (0)
#define IMAI_DATA_OUT_IS_QUANTIZED (0)

#define IMAI_KEY_MAX (38)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out);
int IMAI_enqueue(const float *restrict data_in);
void IMAI_init(void);

#endif /* _IMAI_MODEL_H_ */
