# Prepare MCC5-THU recordings

`clean_data.py` prepares the MCC5-THU motor recordings used in this project so they can be imported into DEEPCRAFT™ Studio. It merges severity labels, keeps every 20th sample (12.8 kHz to 640 Hz), and writes `data.data` and `label.label` for each recording. Importing those files in Studio creates the session files.

## Requirements

- Python 3
- pandas

Install pandas if it is not already available:

```bash
pip install pandas
```

## Usage

Run the script from this folder. `-i` and `-o` are required. `-m` is optional.

```bash
python clean_data.py -i "input_dataset_dir" -o "output_dir" -m "mapping_dir"
```

| Argument | Required | Description |
| --- | --- | --- |
| `-i`, `--input_directory` | Yes | Folder of source CSVs. The search includes subfolders. |
| `-o`, `--output_directory` | Yes | Folder where the class directories are written. |
| `-m`, `--mapping_file_output` | No | Existing folder for `file_mappings.csv`. Omit it to skip the mapping file. |

## Source files

Each source file is a CSV with no header and nine columns, in this order:

`time`, `speed`, `torque`, `motor_vibration_X`, `motor_vibration_Y`, `motor_vibration_Z`, `motor_current_A`, `motor_current_B`, `motor_current_C`

The file name must contain `_speed_circulation_` or `_torque_circulation_`, followed by the load and speed, and usually a timestamp:

`bearing_inner_H_speed_circulation_20Nm_1000rpm_250707143259.csv`

The folder name is that trailing timestamp, including a final `d` when the source name has one. A recording with no timestamp, or a timestamp already given to an earlier file, is named `<class>_0`, `<class>_1`, and so on. Which of two files with the same timestamp keeps that timestamp depends on which file is found first. In this dataset, `bearing_outer_H_and_inner_H_speed_circulation_20Nm_1000rpm` has no timestamp. The two `bearing_outer_L` speed recordings that both end in `250708094556` share a timestamp.

## Output

```text
output_dir/
  bearing/
    250707143259/
      data.data
      label.label
  health/
    250702161631/
      data.data
      label.label
```

`data.data` is the decimated recording at 640 Hz. A fault `label.label` has one row covering the recording, with confidence `1.0`. A `health` recording has a header-only label file, so Studio reads it as `unlabeled` after import.

These source labels are merged:

| Source label | Session class |
| --- | --- |
| `bearing_inner_L`, `bearing_inner_H`, `bearing_outer_L`, `bearing_outer_H`, `bearing_ball_L`, `bearing_ball_H`, `bearing_outer_H_and_inner_H` | `bearing` |
| `static_eccentricity_L`, `static_eccentricity_H` | `static_eccentricity` |
| `winding_L`, `winding_H` | `winding` |

Other names, such as `bend` and `broken_bar_and_bearing`, are kept as they are.

When `-m` is set, the script writes `file_mappings.csv` in that folder with two columns, `Original` and `New`.
