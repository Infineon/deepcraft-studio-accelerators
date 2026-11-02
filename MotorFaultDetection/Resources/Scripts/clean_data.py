from pathlib import Path
import shutil
import re
import csv
import shutil
import pandas as pd


current_frequency = 12800
target_frequency = 640

frequency_divisor = current_frequency // target_frequency


# Output location of the transformed dataset
dataset_dir = Path(r"[ADD PATH HERE]")

# Location of the original dataset
orig_dataset_dir = Path(r"[ADD PATH HERE]")

data_files = list(orig_dataset_dir.rglob("*.csv"))


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

w
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


current_frequency = 12800
target_frequency = 640

frequency_divisor = current_frequency // target_frequency

# Failsafe for when input files DO NOT contain a code
failsafe = 0

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
        if not code:
            code = failsafe
            failsafe += 1
        else:
            code = code[0]

    data_destination = dataset_dir.joinpath(label).joinpath(code)
    data_destination.mkdir(parents=True, exist_ok=True)

    final_time = 0
    with open(data_file, "r", newline="") as data_csv:
        csv_length = 0
        reader = csv.reader(data_csv)
        with open(
            data_destination.joinpath("data.data"), "w", newline=""
        ) as data_destination_file:
            writer = csv.writer(data_destination_file, delimiter=",")
            writer.writerow(attributes)
            for row in reader:
                if csv_length % frequency_divisor == 0:
                    writer.writerow(row)
                    final_time = row[0]
                csv_length += 1
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
            writer.writerow([0, final_time, label, 100.0, ""])
