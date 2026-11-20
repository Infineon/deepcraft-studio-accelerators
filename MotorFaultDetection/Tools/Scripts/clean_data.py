import argparse
import re
import csv
import pandas as pd


from pathlib import Path

current_frequency = 12800
target_frequency = 640

frequency_divisor = current_frequency // target_frequency






parser = argparse.ArgumentParser()

parser.add_argument("-i", "--input_directory", required=True, help="Directory of original dataset")
parser.add_argument("-o", "--output_directory", required=True, help="Output directory of transformed dataset")
parser.add_argument("-m", "--mapping_file_output", default=None, help="Optional directory to output mapping file. If empty no mapping file is generated")

args = parser.parse_args()





# Output location of the transformed dataset
dataset_dir = Path(args.output_directory)

# Location of the original dataset
orig_dataset_dir = Path(args.input_directory)


data_files = list(orig_dataset_dir.rglob("*.csv"))

if args.mapping_file_output:
    mapping_location = Path(args.mapping_file_output)


label_mapping = dict.fromkeys(
    [
        "bearing_outer_H_and_inner_H",
        "bearing_inner_L",
        "bearing_inner_H",
        "bearing_outer_L",
        "bearing_outer_H",
        "bearing_ball_L",
        "bearing_ball_H",
    ],
    "bearing",
)

label_mapping.update(
    dict.fromkeys(
        ["static_eccentricity_L", "static_eccentricity_H"],
        "static_eccentricity",
    )
)

label_mapping.update(
    dict.fromkeys(
        ["winding_L", "winding_H"],
        "winding",
    )
)

attributes = [
    "time",
    "speed",
    "torque",
    "motor_vibration_X",
    "motor_vibration_Y",
    "motor_vibration_Z",
    "motor_current_A",
    "motor_current_B",
    "motor_current_C",
]

mappings = []


# Failsafe for when input files DO NOT contain a code

labels = ['bearing', 'bend', 'broken_bar', 'broken_bar_and_bearing', 'dynamic_eccentricity', 'dynamic_eccentricity_and_bearing', 'health', 'static_eccentricity', 'static_eccentricity_and_bearing', 'voltage_unbalance_L', 'winding', 'winding_and_bearing']
failsafe = dict.fromkeys(labels, 0)

processed_file_codes = []


for data_file in data_files:
    label, circulation_type = re.findall(
        r"\/([^/]*)_(speed_circulation|torque_circulation)_\d.*.csv",
        data_file.as_posix(),
    )[0]
    for key in label_mapping:
        if key in label:
            label = label.replace(key, label_mapping[key])


    full_name = data_file.stem

    code = re.findall(r"_(\d*d?)$", full_name)
    # Check if the file does not have a code or if the code provided is already in use from another file
    if not code or code in processed_file_codes:
        code = f"{label}_{failsafe[label]}"
        failsafe[label] += 1
    else:
        code = code[0]
    processed_file_codes.append(code)

    data_destination = dataset_dir.joinpath(label).joinpath(code)
    data_destination.mkdir(parents=True, exist_ok=True)

    mappings.append([full_name, code])

    final_time = 0
    motor_labels = ["time", "speed","torque","motor_vibration_X","motor_vibration_Y","motor_vibration_Z","motor_current_A","motor_current_B","motor_current_C"]
    df = pd.read_csv(data_file, names=motor_labels, index_col=False)

    df = df.iloc[::frequency_divisor]
    final_time = df['time'].iloc[-1]
    df.to_csv(data_destination.joinpath("data.data"), index=False)

    with open(
        data_destination.joinpath("label.label"), "w", newline=""
    ) as data_csv:
        writer = csv.writer(data_csv, delimiter=",")
        writer.writerow(
            [
                "Time(Seconds)",
                "Length(Seconds)",
                "Label(string)",
                "Confidence(double)",
                "Comment(string)",
            ]
        )
        if label != "health":
            writer.writerow([0, final_time, label, 1.0, ""])

if args.mapping_file_output:
    with open(mapping_location.joinpath("file_mappings.csv"), "w", newline="") as data_csv:
        writer = csv.writer(data_csv, delimiter=",")
        writer.writerow([
            "Original",
            "New"
            ])
        for mapping in mappings:
            writer.writerow(mapping)
