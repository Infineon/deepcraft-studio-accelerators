"""
CSV File Splitter - Multiple Parts with ID/TD Separation

This script splits CSV files into multiple parts (default: 50) with ID/TD separation.
Useful for parallel processing or managing large datasets with memory constraints.

Usage:
    python 4_split_csv_multiple_parts.py

Input Folder:  ../../Data/processed/2_downsampled_normalized/ (downsampled and normalized CSV files)
Output Folder: ../../Data/processed/4_training_data_set/part##_filename/ (data.csv and label.csv in each subfolder)

Project: DEEPCRAFT - Virtual Winding Temperature Sensing v2
"""

import pandas as pd
from pathlib import Path

def split_csv_into_parts(csv_file_path, output_folder, num_parts=5, prefix="part"):
    """
    Split a CSV file into N parts, keeping headers in all files.
    
    Args:
        csv_file_path: Path to the CSV file
        output_folder: Path to output folder
        num_parts: Number of parts to split into
        prefix: Prefix for output files
    """
    df = pd.read_csv(csv_file_path)
    base_name = csv_file_path.stem
    output_folder.mkdir(parents=True, exist_ok=True)
    total_rows = len(df)
    part_size = (total_rows + num_parts - 1) // num_parts  # ceil division

    for i in range(num_parts):
        start = i * part_size
        end = min(start + part_size, total_rows)
        part_df = df.iloc[start:end]
        part_file = output_folder / f"{prefix}{i+1}_{base_name}.csv"
        part_df.to_csv(part_file, index=False)
        print(f"Created: {part_file.name} (rows {start} to {end-1})")
        print(f"  Shape: {part_df.shape}")
    print("-" * 50)

def split_csv_and_create_subfolders(csv_file_path, output_folder, num_parts=50):
    """
    Split a CSV file into N parts, then for each part create a subfolder with two files:
    - data.csv file with specified columns (ID/input data)
    - label.csv file with specified columns (TD/target data)
    
    Args:
        csv_file_path: Path to the CSV file
        output_folder: Path to output folder
        num_parts: Number of parts to split into
    """
    df = pd.read_csv(csv_file_path)
    
    # Create computed column
    df['dqCommand_combined'] = df['dqCommand_imag'] ** 2 + df['dqCommand_real'] ** 2
    
    base_name = csv_file_path.stem
    output_folder.mkdir(parents=True, exist_ok=True)
    total_rows = len(df)
    part_size = (total_rows + num_parts - 1) // num_parts  # ceil division

    id_columns = ['spi_time', 'die_temp_filtered', 'dqCommand_combined', 'outputSpeed_rpm']
    td_columns = ['spi_time', 'coil_temp_filtered']

    for i in range(num_parts):
        start = i * part_size
        end = min(start + part_size, total_rows)
        part_df = df.iloc[start:end]
        part_folder = output_folder / f"part{str(i+1).zfill(2)}_{base_name}"
        part_folder.mkdir(parents=True, exist_ok=True)

        # ID_ file (saved as data.csv)
        try:
            id_df = part_df[id_columns]
            id_file = part_folder / "data.csv"
            id_df.to_csv(id_file, index=False)
            print(f"Created: {id_file}")
        except KeyError as e:
            print(f"Error: Column {e} not found for ID_ in {csv_file_path.name}")

        # TD_ file (saved as label.csv)
        try:
            td_df = part_df[td_columns]
            td_file = part_folder / "label.csv"
            td_df.to_csv(td_file, index=False)
            print(f"Created: {td_file}")
        except KeyError as e:
            print(f"Error: Column {e} not found for TD_ in {csv_file_path.name}")

    print("-" * 50)

def process_and_split_folder(input_folder, output_folder, num_parts=5):
    """
    Process all CSV files in a folder and split them into N parts.
    
    Args:
        input_folder: Path to folder containing CSV files
        output_folder: Path to output folder for split files
        num_parts: Number of parts to split into
    """
    input_path = Path(input_folder)
    
    # Find all CSV files
    csv_files = list(input_path.glob('*.csv'))
    
    if not csv_files:
        print(f"No CSV files found in {input_folder}")
        return
    
    print(f"Found {len(csv_files)} CSV file(s)\n")
    
    # Process each file
    for csv_file in sorted(csv_files):
        print(f"Processing: {csv_file.name}")
        split_csv_into_parts(csv_file, output_folder, num_parts=num_parts)

def process_and_split_to_subfolders(input_folder, output_folder, num_parts=50):
    """
    Process all CSV files in a folder and split them into N parts with subfolders containing data.csv and label.csv files.
    
    Args:
        input_folder: Path to folder containing CSV files
        output_folder: Path to output folder for split files
        num_parts: Number of parts to split into
    """
    input_path = Path(input_folder)
    
    # Find all CSV files
    csv_files = list(input_path.glob('*.csv'))
    
    if not csv_files:
        print(f"No CSV files found in {input_folder}")
        return
    
    print(f"Found {len(csv_files)} CSV file(s)\n")
    
    # Process each file
    for csv_file in sorted(csv_files):
        print(f"Processing: {csv_file.name}")
        split_csv_and_create_subfolders(csv_file, output_folder, num_parts=num_parts)

if __name__ == "__main__":
    # Set paths
    input_folder = Path(__file__).parent.parent.parent / "Data" / "processed" / "2_downsampled_normalized"  # Downsampled CSV files
    processed_folder = Path(__file__).parent.parent.parent / "Data" / "processed"
    
    # Ask user for number of parts
    print("=" * 60)
    print("CSV File Splitter - Multiple Parts with ID/TD Separation")
    print("=" * 60)
    
    while True:
        try:
            user_input = input(f"Enter number of parts to split into (default 25, press Enter for default): ").strip()
            
            if user_input == "":
                num_parts = 25  # Default value
                break
            else:
                num_parts = int(user_input)
                if num_parts < 1:
                    print("Error: Number of parts must be at least 1. Please try again.")
                    continue
                break
        except ValueError:
            print("Error: Please enter a valid number.")
            continue
    
    print(f"\nSplitting CSV files into {num_parts} parts...")
    
    # For splitting into N parts and creating subfolders/files
    training_data_folder = processed_folder / "4_training_data_set"
    process_and_split_to_subfolders(input_folder, training_data_folder, num_parts=num_parts)
    
    print("\n" + "=" * 60)
    print(f"Processing complete! Files split into {num_parts} parts.")
    print(f"Output folder: {training_data_folder}")
    print("\nEach subfolder contains:")
    print("  - data.csv: Input features (spi_time, die_temp_filtered, dqCommand_combined, outputSpeed_rpm)")
    print("  - label.csv: Target values (spi_time, coil_temp_filtered)")
    print("=" * 60)
