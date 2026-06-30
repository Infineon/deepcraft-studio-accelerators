# YOLOv5 Nano Legacy Evaluation

## Model Description

**YOLOv5n Legacy** is the original YOLOv5 Nano model with the classic **anchor-based detection head**. Unlike the updated YOLOv5nu variant, this legacy version retains the traditional anchor-box mechanism for bounding box prediction. It uses a different output tensor layout (transposed compared to newer models), resulting in a distinct post-processing pipeline. The legacy model has a notably smaller footprint, making it a good candidate for highly constrained embedded targets.

- **Architecture**: YOLOv5 (Ultralytics, original anchor-based)
- **Variant**: Nano (n) — smallest and fastest, legacy version
- **Task**: Object Detection
- **Dataset**: COCO (Common Objects in Context)
- **Number of Classes**: 80
- **Input Resolution**: 256x256 pixels
- **Quantization**: INT8

## Folder Contents

| File | Description |
|------|-------------|
| `Model/yolov5nLegacy.pt` | Original PyTorch model with anchor-based head (~3.9 MB) |
| `Model/yolov5nLegacy-int8.tflite` | INT8 quantized TFLite model for edge deployment (~2.0 MB) |
| `yolov5nLegacy-int8.improjv` | Imagimob Studio project file |
| `yolov5nLegacy-int8.imunit` | Imagimob Studio processing graph for live camera evaluation |
| `README.md` | This file |

## Processing Pipeline

The `.imunit` graph implements the following pipeline:

```
Camera (1280×720 @ 30fps) → Resize (256x256) → Cast (int8) → YOLOv5n Legacy TFLite → Dequantize (float32) → Select BBox + Classes → Detection Filter (threshold: 0.3) → Labels → Bounding Box Visualization
```

**Note:** This legacy model uses a transposed output layout compared to the updated YOLOv5nu and newer YOLO versions. The selection and concatenation operations operate along axis 0 instead of axis 1. The bounding box coordinate selection also includes 5 values (x, y, w, h, objectness) instead of 4.

## COCO 80 Classes

This model detects the following 80 object classes:

| ID | Class | ID | Class | ID | Class | ID | Class |
|----|-------|----|-------|----|-------|----|-------|
| 0 | person | 20 | elephant | 40 | wine glass | 60 | dining table |
| 1 | bicycle | 21 | bear | 41 | cup | 61 | toilet |
| 2 | car | 22 | zebra | 42 | fork | 62 | tv |
| 3 | motorcycle | 23 | giraffe | 43 | knife | 63 | laptop |
| 4 | airplane | 24 | backpack | 44 | spoon | 64 | mouse |
| 5 | bus | 25 | umbrella | 45 | bowl | 65 | remote |
| 6 | train | 26 | handbag | 46 | banana | 66 | keyboard |
| 7 | truck | 27 | tie | 47 | apple | 67 | cell phone |
| 8 | boat | 28 | suitcase | 48 | sandwich | 68 | microwave |
| 9 | traffic light | 29 | frisbee | 49 | orange | 69 | oven |
| 10 | fire hydrant | 30 | skis | 50 | broccoli | 70 | toaster |
| 11 | stop sign | 31 | snowboard | 51 | carrot | 71 | sink |
| 12 | parking meter | 32 | sports ball | 52 | hot dog | 72 | refrigerator |
| 13 | bench | 33 | kite | 53 | pizza | 73 | book |
| 14 | bird | 34 | baseball bat | 54 | donut | 74 | clock |
| 15 | cat | 35 | baseball glove | 55 | cake | 75 | vase |
| 16 | dog | 36 | skateboard | 56 | chair | 76 | scissors |
| 17 | horse | 37 | surfboard | 57 | couch | 77 | teddy bear |
| 18 | sheep | 38 | tennis racket | 58 | potted plant | 78 | hair drier |
| 19 | cow | 39 | bottle | 59 | bed | 79 | toothbrush |

## How to Use

1. Open `yolov5nLegacy-int8.imunit` from the Solution Explorer.
2. Click the **Start** button (play symbol).
3. Click the **Record** button to begin live evaluation.
4. Observe bounding box detections on the camera feed.

## Example: Adding New Classes for Detection

The default graph only selects **person** and **car** from the 80 available classes. This section explains how to add more classes to the detection output.

### Understanding the Output Tensor (Legacy Layout)

The legacy YOLOv5 model uses a **transposed output layout** compared to newer YOLO models. The output tensor contains **85 values per detection** (4 bounding box coordinates + 1 objectness score + 80 class scores), and values are arranged along **axis 0**:

| Index | Value |
|-------|-------|
| 0–3 | x, y, w, h (bounding box coordinates) |
| 4 | objectness score |
| 5 | person (COCO class 0) |
| 6 | bicycle (COCO class 1) |
| 7 | car (COCO class 2) |
| 8 | motorcycle (COCO class 3) |
| ... | ... |
| 5 + *class_id* | score for that COCO class |

**Formula:** `output_index = 5 + COCO_class_id`

> **Key differences from newer models:** The index offset is **5** (not 4) due to the extra objectness score at index 4, and all Select/Concat nodes must use **`axis: 0`** (not 1) because the output tensor is transposed.

### Steps in Imagimob Studio

1. **Open the `.imunit` graph** in Imagimob Studio.

2. **Add a new Select node** for the desired class(es):
   - Right-click on the graph canvas and add a new **Select** node (`Imaginet.Units.Math.Select`).
   - Set its parameters:
     - `index`: the output index of the first class you want (use `5 + COCO_class_id`)
     - `count`: **number of consecutive classes** to select
     - `axis`: **0** (legacy uses axis 0)

   **Single class example — adding dog (COCO ID 16):**
   - Name: **"Dog class"**
   - `index`: **21**, `count`: **1**, `axis`: **0**

   **Consecutive classes example — adding cat, dog, and horse (COCO IDs 15, 16, 17) in one Select node:**
   - Name: **"Cat+Dog+Horse classes"**
   - `index`: **20**, `count`: **3**, `axis`: **0**

   This works because cat (index 20), dog (index 21), and horse (index 22) are adjacent in the output tensor. A single Select node with `count: 3` extracts all three at once — no need for three separate Select nodes and extra Concat nodes.

3. **Connect the Dequantize output** to the new Select node:
   - Draw a connection from the **Dequantize** node's output to the new Select node's input.

4. **Add the new class(es) to the Concat chain:**
   - The existing graph concatenates person and car scores using a Concat node.
   - Add a **new Concat node** (with `axis: 0`) that takes the existing person+car Concat output as `Input 0` and the new Select node output as `Input 1`.

5. **Update the Labels node** to include the new class names. Change the `axis_labels` parameter:

   For the single dog class, change from:
   ```
   {,,,,},{x,y,w,h,person,car}
   ```
   to:
   ```
   {,,,,},{x,y,w,h,person,car,dog}
   ```

   For the consecutive cat+dog+horse group, change to:
   ```
   {,,,,},{x,y,w,h,person,car,cat,dog,horse}
   ```
   The class names should be in same order with their id numbers.
   
6. **Run the evaluation** — you should now see bounding boxes with the new labels in addition to "person" and "car".

### When to Use `count` > 1

| Scenario | Select Nodes Needed | Approach |
|----------|---------------------|----------|
| Add **dog** only (ID 16) | 1 node | `index: 21`, `count: 1` |
| Add **cat** (15) and **dog** (16) | 1 node | `index: 20`, `count: 2` (consecutive) |
| Add **cat** (15), **dog** (16), **horse** (17) | 1 node | `index: 20`, `count: 3` (consecutive) |
| Add **cat** (15) and **chair** (56) | 2 nodes | Not consecutive — use separate Select nodes with `count: 1` each |
| Add **bus** (5), **train** (6), **truck** (7) | 1 node | `index: 10`, `count: 3` (consecutive) |

Using `count` > 1 for consecutive classes keeps the graph simpler and avoids unnecessary extra Concat nodes.

### Quick Reference for Common Classes

| Class | COCO ID | Output Index (Legacy) |
|-------|---------|----------------------|
| person | 0 | 5 |
| bicycle | 1 | 6 |
| car | 2 | 7 |
| motorcycle | 3 | 8 |
| bus | 5 | 10 |
| train | 6 | 11 |
| truck | 7 | 12 |
| cat | 15 | 20 |
| dog | 16 | 21 |
| horse | 17 | 22 |
| chair | 56 | 61 |
| tv | 62 | 67 |
| laptop | 63 | 68 |
