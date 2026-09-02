"""
Splits combined_data.csv into two files:
- data.csv  : input features  ['spi_time', 'die_temp_filtered', 'dqCommand_combined', 'outputSpeed_rpm']
- label.csv : target values   ['spi_time', 'coil_temp_filtered']

Note: 'dqCommand_combined' is computed as dqCommand_imag² + dqCommand_real²

Usage:
    python 3_split_data_label.py

Input:  ../../Data/processed/2_downsampled_normalized/combined_data.csv
Output: ../../Data/processed/3_split_data_label/data.csv
        ../../Data/processed/3_split_data_label/label.csv
"""

import pandas as pd
from pathlib import Path


def generate_training_set(input_file, output_folder):
    """
    Split combined_data.csv into data.csv (input features) and label.csv (target values).

    Args:
        input_file: Path to combined_data.csv
        output_folder: Path to output folder
    """
    print(f"Reading: {input_file}")
    df = pd.read_csv(input_file)
    print(f"  Shape: {df.shape}")
    print(f"  Columns: {list(df.columns)}")

    output_folder.mkdir(parents=True, exist_ok=True)

    # Compute combined dq command feature
    df['dqCommand_combined'] = df['dqCommand_imag'] ** 2 + df['dqCommand_real'] ** 2

    # ---------- data.csv ----------
    data_columns = ['spi_time', 'die_temp_filtered', 'dqCommand_combined', 'outputSpeed_rpm']
    data_df = df[data_columns]
    data_file = output_folder / "data.csv"
    data_df.to_csv(data_file, index=False)
    print(f"\nCreated: {data_file}")
    print(f"  Columns: {list(data_df.columns)}")
    print(f"  Shape: {data_df.shape}")

    # ---------- label.csv ----------
    label_columns = ['spi_time', 'coil_temp_filtered']
    label_df = df[label_columns]
    label_file = output_folder / "label.csv"
    label_df.to_csv(label_file, index=False)
    print(f"\nCreated: {label_file}")
    print(f"  Columns: {list(label_df.columns)}")
    print(f"  Shape: {label_df.shape}")


if __name__ == "__main__":
    input_file = (
        Path(__file__).parent.parent.parent
        / "Data" / "processed" / "2_downsampled_normalized" / "combined_data.csv"
    )
    output_folder = (
        Path(__file__).parent.parent.parent
        / "Data" / "processed" / "3_split_data_label"
    )

    generate_training_set(input_file, output_folder)

    print("\n" + "=" * 60)
    print("Data and label split complete!")
    print(f"Output saved to: {output_folder}")
