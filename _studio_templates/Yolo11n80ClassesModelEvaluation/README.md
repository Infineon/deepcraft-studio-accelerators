# YOLO11 Nano Evaluation

## Model Description

**YOLO11n** (YOLO11 Nano) is the latest generation of the YOLO object detection family. It introduces architectural improvements over YOLOv8 with enhanced feature extraction and more efficient attention mechanisms, while maintaining a compact model size suitable for edge and embedded deployment.

- **Architecture**: YOLO11 (Ultralytics)
- **Variant**: Nano (n) — smallest and fastest
- **Task**: Object Detection
- **Dataset**: COCO (Common Objects in Context)
- **Number of Classes**: 80
- **Input Resolution**: 64x64 pixels
- **Quantization**: INT8

## Folder Contents

| File | Description |
|------|-------------|
| `Model/yolo11n.pt` | Original PyTorch model (~5.4 MB) |
| `Model/yolo11n_int8.tflite` | INT8 quantized TFLite model for edge deployment (~2.8 MB) |
| `yolo11n_int8.improjv` | Imagimob Studio project file |
| `yolo11n_int8.imunit` | Imagimob Studio processing graph for live camera evaluation |
| `README.md` | This file |

## Processing Pipeline

The `.imunit` graph implements the following pipeline:

```
Camera (640×360 @ 15fps) → Resize (64x64) → Cast (int8) → YOLO11n TFLite → Dequantize (float32) → Select BBox + Classes → Detection Filter (threshold: 0.3) → Labels → Bounding Box Visualization
```

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

1. Open `yolo11n_int8.imunit` from the Solution Explorer.
2. Click the **Start** button (play symbol).
3. Click the **Record** button to begin live evaluation.
4. Observe bounding box detections on the camera feed.

## Example: Adding New Classes for Detection

The default graph only selects **person** and **car** from the 80 available classes. This section explains how to add more classes to the detection output.

### Understanding the Output Tensor

The model output tensor contains **84 values per detection** (4 bounding box coordinates + 80 class scores):

| Index | Value |
|-------|-------|
| 0–3 | x, y, w, h (bounding box coordinates) |
| 4 | person (COCO class 0) |
| 5 | bicycle (COCO class 1) |
| 6 | car (COCO class 2) |
| 7 | motorcycle (COCO class 3) |
| ... | ... |
| 4 + *class_id* | score for that COCO class |

**Formula:** `output_index = 4 + COCO_class_id`

### Steps in Imagimob Studio

1. **Open the `.imunit` graph** in Imagimob Studio.

2. **Add a new Select node** for the desired class(es):
   - Right-click on the graph canvas and add a new **Select** node (`Imaginet.Units.Math.Select`).
   - Set its parameters:
     - `index`: the output index of the first class you want (use `4 + COCO_class_id`)
     - `count`: **number of consecutive classes** to select
     - `axis`: **1**

   **Single class example — adding dog (COCO ID 16):**
   - Name: **"Dog class"**
   - `index`: **20**, `count`: **1**, `axis`: **1**

   **Consecutive classes example — adding cat, dog, and horse (COCO IDs 15, 16, 17) in one Select node:**
   - Name: **"Cat+Dog+Horse classes"**
   - `index`: **19**, `count`: **3**, `axis`: **1**

   This works because cat (index 19), dog (index 20), and horse (index 21) are adjacent in the output tensor. A single Select node with `count: 3` extracts all three at once — no need for three separate Select nodes and extra Concat nodes.

3. **Connect the Dequantize output** to the new Select node:
   - Draw a connection from the **Dequantize** node's output to the new Select node's input.

4. **Add the new class(es) to the Concat chain:**
   - The existing graph concatenates person and car scores using a Concat node.
   - Add a **new Concat node** that takes the existing person+car Concat output as `Input 0` and the new Select node output as `Input 1`.

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
| Add **dog** only (ID 16) | 1 node | `index: 20`, `count: 1` |
| Add **cat** (15) and **dog** (16) | 1 node | `index: 19`, `count: 2` (consecutive) |
| Add **cat** (15), **dog** (16), **horse** (17) | 1 node | `index: 19`, `count: 3` (consecutive) |
| Add **cat** (15) and **chair** (56) | 2 nodes | Not consecutive — use separate Select nodes with `count: 1` each |
| Add **bus** (5), **train** (6), **truck** (7) | 1 node | `index: 9`, `count: 3` (consecutive) |

Using `count` > 1 for consecutive classes keeps the graph simpler and avoids unnecessary extra Concat nodes.

### Quick Reference for Common Classes


| Class | COCO ID | Output Index |
|-------|---------|--------------|
| person | 0 | 4 |
| bicycle | 1 | 5 |
| car | 2 | 6 |
| motorcycle | 3 | 7 |
| bus | 5 | 9 |
| train | 6 | 10 |
| truck | 7 | 11 |
| cat | 15 | 19 |
| dog | 16 | 20 |
| horse | 17 | 21 |
| chair | 56 | 60 |
| tv | 62 | 66 |
| laptop | 63 | 67 |
