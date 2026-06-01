"""
Training Set Splitter

Splits data.csv and label.csv from the 3_split_data_label folder into at least
`min_datasets` numbered subfolders (dataset01, dataset02, ...).

Each output file contains only ascending spi_time values. The algorithm:
  1. Detects natural monotonic segments (where spi_time resets / decreases).
  2. Subdivides each segment into roughly equal sub-parts so that the total
     number of output folders is >= min_datasets.
  3. Files are not required to be equal in length.

Usage:
    python 4_generate_training_set.py

Input:  ../../Data/processed/3_split_data_label/data.csv
Output: ../../Data/processed/4_training_set/dataset001/data.csv
        ../../Data/processed/4_training_set/dataset001/label.csv
        ...
"""

import math
import pandas as pd
import numpy as np
from pathlib import Path


def find_monotonic_segments(spi_time_series):
    """
    Return a list of (start, end) row index pairs for each monotonically
    increasing segment. A new segment begins wherever spi_time decreases.

    Args:
        spi_time_series: pandas Series of spi_time values

    Returns:
        List of (start_idx, end_idx) tuples (end_idx is exclusive).
    """
    n = len(spi_time_series)
    diffs = spi_time_series.diff()
    reset_positions = [0] + diffs[diffs < 0].index.tolist() + [n]
    return [(reset_positions[i], reset_positions[i + 1])
            for i in range(len(reset_positions) - 1)]


def split_into_parts(input_folder, output_folder, min_datasets=100):
    """
    Split data.csv and label.csv into at least min_datasets subfolders,
    with each subfolder containing only ascending spi_time rows.

    Args:
        input_folder:  Path containing data.csv and label.csv
        output_folder: Path where datasetXXX subfolders will be created
        min_datasets:  Minimum number of output dataset folders (default: 100)
    """
    data_file  = input_folder / "data.csv"
    label_file = input_folder / "label.csv"

    if not data_file.exists():
        print(f"Error: {data_file} not found.")
        return
    if not label_file.exists():
        print(f"Error: {label_file} not found.")
        return

    data_df  = pd.read_csv(data_file)
    label_df = pd.read_csv(label_file)

    if len(data_df) != len(label_df):
        print(f"Warning: data.csv ({len(data_df)} rows) and label.csv "
              f"({len(label_df)} rows) have different lengths. "
              f"Proceeding with the shorter length.")
        n_rows = min(len(data_df), len(label_df))
        data_df  = data_df.iloc[:n_rows].reset_index(drop=True)
        label_df = label_df.iloc[:n_rows].reset_index(drop=True)

    print(f"Input data.csv  shape: {data_df.shape}")
    print(f"Input label.csv shape: {label_df.shape}")

    if 'spi_time' not in data_df.columns:
        print("Error: 'spi_time' column not found in data.csv.")
        return

    # Step 1: find natural monotonic segments
    segments = find_monotonic_segments(data_df['spi_time'])
    n_segments = len(segments)
    print(f"Detected {n_segments} natural monotonic segment(s)")

    # Step 2: decide how many sub-parts per segment so total >= min_datasets
    sub_parts_per_segment = math.ceil(min_datasets / n_segments)
    total_parts = n_segments * sub_parts_per_segment
    print(f"Sub-parts per segment: {sub_parts_per_segment}  "
          f"(total output folders: {total_parts})")
    print("=" * 60)

    output_folder.mkdir(parents=True, exist_ok=True)

    dataset_idx = 1
    for seg_num, (seg_start, seg_end) in enumerate(segments, start=1):
        seg_length = seg_end - seg_start
        # Split this segment's row range into sub_parts_per_segment chunks
        sub_indices = np.array_split(np.arange(seg_start, seg_end),
                                     sub_parts_per_segment)

        for sub_idx in sub_indices:
            if len(sub_idx) == 0:
                continue

            folder_name = f"dataset{dataset_idx:03d}"
            part_folder = output_folder / folder_name
            part_folder.mkdir(parents=True, exist_ok=True)

            data_part  = data_df.iloc[sub_idx].reset_index(drop=True)
            label_part = label_df.iloc[sub_idx].reset_index(drop=True)

            data_part.to_csv(part_folder / "data.csv",  index=False)
            label_part.to_csv(part_folder / "label.csv", index=False)

            print(f"  {folder_name}: segment {seg_num}, "
                  f"rows {sub_idx[0]}-{sub_idx[-1]} "
                  f"({len(sub_idx)} rows)")
            dataset_idx += 1

    actual_total = dataset_idx - 1
    print("=" * 60)
    print(f"Done. {actual_total} dataset folder(s) created in: {output_folder}")


if __name__ == "__main__":
    input_folder = (
        Path(__file__).parent.parent.parent
        / "Data" / "processed" / "3_split_data_label"
    )
    output_folder = (
        Path(__file__).parent.parent.parent
        / "Data" / "processed" / "4_training_set"
    )

    split_into_parts(input_folder, output_folder, min_datasets=100)
