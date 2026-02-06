/*
* DEEPCRAFT Studio 5.7.3938+5213730ae03159abbdafc49774c1243781f8a3db
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 11/27/2025 01:10:59 UTC. Any changes will be lost.
* 
* Model ID  8a0e9726-de5d-4fa6-9e82-e48344d1a635
* 
* Memory    Size                      Efficiency
* Buffers   10400 bytes (RAM)         100 %
* State     9536 bytes (RAM)          100 %
* Readonly  66224 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1dlstm-medium-accuracy-0
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | Air
* 2           | Plastic
* 3           | Wood
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [50,46]         float      dequeue
*    window_shape = [50,46]
*    stride = 230
*    buffer_multiplier = 1
* Input Layer                    [50,46]         float      dequeue
*    shape = [50,46]
* Convolution 1D                 [25,12]         float      dequeue
*    filters = 12
*    kernel_size = 5
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[5,46,12]
* Batch Normalization            [25,12]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[12]
*    beta = float[12]
*    mean = float[12]
*    variance = float[12]
* Activation                     [25,12]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [13,24]         float      dequeue
*    filters = 24
*    kernel_size = 5
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[5,12,24]
* Batch Normalization            [13,24]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[24]
*    beta = float[24]
*    mean = float[24]
*    variance = float[24]
* Activation                     [13,24]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [7,24]          float      dequeue
*    filters = 24
*    kernel_size = 5
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[5,24,24]
* Batch Normalization            [7,24]          float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[24]
*    beta = float[24]
*    mean = float[24]
*    variance = float[24]
* Activation                     [7,24]          float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [7,32]          float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,24,32]
* Batch Normalization            [7,32]          float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [7,32]          float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [7,32]          float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [7,32]          float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [7,32]          float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [3,32]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [3,32]          float      dequeue
*    rate = 0.05
*    trainable = True
* Long Short-Term Memory         [16]            float      dequeue
*    units = 16
*    activation = tanh
*    recurrent_activation = sigmoid
*    use_bias = True
*    return_sequences = False
*    return_state = False
*    stateful = False
*    go_backwards = False
*    trainable = True
*    kernel = float[32,64]
*    recurrent_kernel = float[16,64]
*    bias = float[64]
* Flatten                        [16]            float      dequeue
* Dense                          [40]            float      dequeue
*    units = 40
*    use_bias = False
*    activation = linear
*    trainable = True
*    weight = float[16,40]
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
*    rate = 0.2
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
*    Parameter data_in is Input of size float[46].
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
* (ACC) Accuracy 96.241 %
* (F1S) F1 Score 96.268 %
* 
* Name of class                                            (unlabelled)              Air          Plastic             Wood
* (TP) True Positive or Correct Positive Prediction               22567             9747             8138             7329
* (FN) False Negative or Incorrect Negative Prediction             1261               43              227              335
* (FP) False Positive or Incorrect Positive Prediction               54              365              781              666
* (TN) True Negative or Correct Negative Prediction               25765            39492            40501            41317
* (TPR) True Positive Rate or Sensitivity, Recall               94.71 %          99.56 %          97.29 %          95.63 %
* (TNR) True Negative Rate or Specificity, Selectivity          99.79 %          99.08 %          98.11 %          98.41 %
* (PPV) Positive Predictive Value or Precision                  99.76 %          96.39 %          91.24 %          91.67 %
* (NPV) Negative Predictive Value                               95.33 %          99.89 %          99.44 %          99.20 %
* (FNR) False Negative Rate or Miss Rate                         5.29 %           0.44 %           2.71 %           4.37 %
* (FPR) False Positive Rate or Fall-Out                          0.21 %           0.92 %           1.89 %           1.59 %
* (FDR) False Discovery Rate                                     0.24 %           3.61 %           8.76 %           8.33 %
* (FOR) False Omission Rate                                      4.67 %           0.11 %           0.56 %           0.80 %
* (F1S) F1 Score                                                97.17 %          97.95 %          94.17 %          93.61 %
*/


#define IMAI_TEST_AVG_ACC 0.9624146474107197 // Accuracy
#define IMAI_TEST_AVG_F1S 0.9626754744130283 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "(unlabelled)", TP: 22567, FN: 1261, FP: 54, TN: 25765, TPR: 0.9470790666442, TNR: 0.9979085169836, PPV: 0.9976128376287, NPV: 0.9533412269666, FNR: 0.0529209333557, FPR: 0.0020914830163, FDR: 0.0023871623712, FOR: 0.0466587730333, F1S: 0.9716893797498, }, \
 {name: "Air", TP: 9747, FN: 43, FP: 365, TN: 39492, TPR: 0.9956077630234, TNR: 0.9908422610833, PPV: 0.9639042721518, NPV: 0.9989123561401, FNR: 0.0043922369765, FPR: 0.0091577389166, FDR: 0.0360957278481, FOR: 0.0010876438598, F1S: 0.9794995477841, }, \
 {name: "Plastic", TP: 8138, FN: 227, FP: 781, TN: 40501, TPR: 0.9728631201434, TNR: 0.9810813429581, PPV: 0.9124341293867, NPV: 0.9944264388135, FNR: 0.0271368798565, FPR: 0.0189186570418, FDR: 0.0875658706132, FOR: 0.0055735611864, F1S: 0.9416801666280, }, \
 {name: "Wood", TP: 7329, FN: 335, FP: 666, TN: 41317, TPR: 0.9562891440501, TNR: 0.9841364361765, PPV: 0.9166979362101, NPV: 0.9919571689234, FNR: 0.0437108559498, FPR: 0.0158635638234, FDR: 0.0833020637898, FOR: 0.0080428310765, F1S: 0.9360751005811, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 97.018 %
* (F1S) F1 Score 97.029 %
* 
* Name of class                                            (unlabelled)              Air          Plastic             Wood
* (TP) True Positive or Correct Positive Prediction               74577            26924            27216            27558
* (FN) False Negative or Incorrect Negative Prediction             3660               80              276              788
* (FP) False Positive or Incorrect Positive Prediction              169              984             2102             1549
* (TN) True Negative or Correct Negative Prediction               82673           133091           131485           131184
* (TPR) True Positive Rate or Sensitivity, Recall               95.32 %          99.70 %          99.00 %          97.22 %
* (TNR) True Negative Rate or Specificity, Selectivity          99.80 %          99.27 %          98.43 %          98.83 %
* (PPV) Positive Predictive Value or Precision                  99.77 %          96.47 %          92.83 %          94.68 %
* (NPV) Negative Predictive Value                               95.76 %          99.94 %          99.79 %          99.40 %
* (FNR) False Negative Rate or Miss Rate                         4.68 %           0.30 %           1.00 %           2.78 %
* (FPR) False Positive Rate or Fall-Out                          0.20 %           0.73 %           1.57 %           1.17 %
* (FDR) False Discovery Rate                                     0.23 %           3.53 %           7.17 %           5.32 %
* (FOR) False Omission Rate                                      4.24 %           0.06 %           0.21 %           0.60 %
* (F1S) F1 Score                                                97.50 %          98.06 %          95.81 %          95.93 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9701761247586588 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9702926189919973 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 74577, FN: 3660, FP: 169, TN: 82673, TPR: 0.9532190651482, TNR: 0.9979599719948, PPV: 0.9977390094453, NPV: 0.9576060139228, FNR: 0.0467809348517, FPR: 0.0020400280051, FDR: 0.0022609905546, FOR: 0.0423939860771, F1S: 0.9749710752175, }, \
 {name: "Air", TP: 26924, FN: 80, FP: 984, TN: 133091, TPR: 0.9970374759294, TNR: 0.9926608241655, PPV: 0.9647412928192, NPV: 0.9993992686095, FNR: 0.0029625240705, FPR: 0.0073391758344, FDR: 0.0352587071807, FOR: 0.0006007313904, F1S: 0.9806235431235, }, \
 {name: "Plastic", TP: 27216, FN: 276, FP: 2102, TN: 131485, TPR: 0.9899607158446, TNR: 0.9842649359593, PPV: 0.9283034313391, NPV: 0.9979052982293, FNR: 0.0100392841553, FPR: 0.0157350640406, FDR: 0.0716965686608, FOR: 0.0020947017706, F1S: 0.9581411723288, }, \
 {name: "Wood", TP: 27558, FN: 788, FP: 1549, TN: 131184, TPR: 0.9722006632329, TNR: 0.9883299556252, PPV: 0.9467825608960, NPV: 0.9940290364622, FNR: 0.0277993367670, FPR: 0.0116700443747, FDR: 0.0532174391039, FOR: 0.0059709635377, F1S: 0.9593232729361, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 96.358 %
* (F1S) F1 Score 96.381 %
* 
* Name of class                                            (unlabelled)              Air          Plastic             Wood
* (TP) True Positive or Correct Positive Prediction               23300             7599             8877            10229
* (FN) False Negative or Incorrect Negative Prediction             1186               27              273              404
* (FP) False Positive or Incorrect Positive Prediction               49              347              820              674
* (TN) True Negative or Correct Negative Prediction               27360            43922            41925            40588
* (TPR) True Positive Rate or Sensitivity, Recall               95.16 %          99.65 %          97.02 %          96.20 %
* (TNR) True Negative Rate or Specificity, Selectivity          99.82 %          99.22 %          98.08 %          98.37 %
* (PPV) Positive Predictive Value or Precision                  99.79 %          95.63 %          91.54 %          93.82 %
* (NPV) Negative Predictive Value                               95.85 %          99.94 %          99.35 %          99.01 %
* (FNR) False Negative Rate or Miss Rate                         4.84 %           0.35 %           2.98 %           3.80 %
* (FPR) False Positive Rate or Fall-Out                          0.18 %           0.78 %           1.92 %           1.63 %
* (FDR) False Discovery Rate                                     0.21 %           4.37 %           8.46 %           6.18 %
* (FOR) False Omission Rate                                      4.15 %           0.06 %           0.65 %           0.99 %
* (F1S) F1 Score                                                97.42 %          97.60 %          94.20 %          94.99 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.9635803063878986 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.9638073803542205 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 23300, FN: 1186, FP: 49, TN: 27360, TPR: 0.9515641591113, TNR: 0.9982122660440, PPV: 0.9979014090539, NPV: 0.9584530231906, FNR: 0.0484358408886, FPR: 0.0017877339559, FDR: 0.0020985909460, FOR: 0.0415469768093, F1S: 0.9741820842479, }, \
 {name: "Air", TP: 7599, FN: 27, FP: 347, TN: 43922, TPR: 0.9964594807238, TNR: 0.9921615577492, PPV: 0.9563302290460, NPV: 0.9993856515506, FNR: 0.0035405192761, FPR: 0.0078384422507, FDR: 0.0436697709539, FOR: 0.0006143484493, F1S: 0.9759825327510, }, \
 {name: "Plastic", TP: 8877, FN: 273, FP: 820, TN: 41925, TPR: 0.9701639344262, TNR: 0.9808164697625, PPV: 0.9154377642569, NPV: 0.9935304990757, FNR: 0.0298360655737, FPR: 0.0191835302374, FDR: 0.0845622357430, FOR: 0.0064695009242, F1S: 0.9420066854141, }, \
 {name: "Wood", TP: 10229, FN: 404, FP: 674, TN: 40588, TPR: 0.9620050785291, TNR: 0.9836653579564, PPV: 0.9381821517013, NPV: 0.9901444184231, FNR: 0.0379949214708, FPR: 0.0163346420435, FDR: 0.0618178482986, FOR: 0.0098555815768, F1S: 0.9499442793462, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"unlabelled", "Air", "Plastic", "Wood"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0x26, 0x97, 0x0e, 0x8a, 0x5d, 0xde, 0xa6, 0x4f, 0x9e, 0x82, 0xe4, 0x83, 0x44, 0xd1, 0xa6, 0x35}

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

// data_in [46] (184 bytes)
#define IMAI_DATA_IN_COUNT (46)
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

#define IMAI_KEY_MAX (97)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out);
int IMAI_enqueue(const float *restrict data_in);
void IMAI_init(void);

#endif /* _IMAI_MODEL_H_ */
