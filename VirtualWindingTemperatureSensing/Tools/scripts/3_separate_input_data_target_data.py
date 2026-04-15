"""
CSV File Separator - Input Data/Target Data Separation (Alternative)

Alternative simpler script for separating CSV files into Input Data and Target Data files.
Creates a subfolder for each source file containing data.csv and label.csv.

Usage:
    python 3_separate_input_data_target_data.py

Input Folder:  ../../Data/processed/2_downsampled_normalized/ (downsampled and normalized CSV files)
Output Folder: ../../Data/processed/3_split_data_label/<filename>/ (data.csv and label.csv files)

Project: DEEPCRAFT - Virtual Winding Temperature Sensing v2
"""

import pandas as pd
from pathlib import Path

def split_csv_file(csv_file_path, output_folder):
    """
    Split a CSV file into two files: data.csv (input features) and label.csv (target values).
    Creates a subfolder named after the source file.
    
    Args:
        csv_file_path: Path to the CSV file
        output_folder: Path to output folder
    """
    # Read the CSV file
    df = pd.read_csv(csv_file_path)
    
    # Get the base filename without extension
    base_name = csv_file_path.stem
    
    # Create subfolder for this file
    file_output_folder = output_folder / base_name
    file_output_folder.mkdir(parents=True, exist_ok=True)
    
    try:
        # Create computed column
        df['dqCommand_combined'] = df['dqCommand_imag'] ** 2 + df['dqCommand_real'] ** 2
        
        # Create data.csv file with input features
        id_columns = ['spi_time', 'die_temp_filtered', 'dqCommand_combined', 'outputSpeed_rpm']
        id_df = df[id_columns]
        id_output_file = file_output_folder / "data.csv"
        id_df.to_csv(id_output_file, index=False)
        print(f"Created: {id_output_file}")
        print(f"  Columns: {list(id_df.columns)}")
        print(f"  Shape: {id_df.shape}")
        
        # Create label.csv file with target values
        td_columns = ['spi_time', 'coil_temp_filtered']
        td_df = df[td_columns]
        td_output_file = file_output_folder / "label.csv"
        td_df.to_csv(td_output_file, index=False)
        print(f"Created: {td_output_file}")
        print(f"  Columns: {list(td_df.columns)}")
        print(f"  Shape: {td_df.shape}")
        print("-" * 50)
        
    except KeyError as e:
        print(f"Error: Column {e} not found in {csv_file_path.name}")
        print(f"Available columns: {list(df.columns)}")
        print("-" * 50)
    except Exception as e:
        print(f"Error processing {csv_file_path.name}: {str(e)}")
        print("-" * 50)

def process_csv_folder(input_folder, output_folder):
    """
    Process all CSV files in a folder and split them into data.csv and label.csv files.
    Each source file gets its own subfolder.
    
    Args:
        input_folder: Path to folder containing CSV files
        output_folder: Path to output folder for split files
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
        split_csv_file(csv_file, output_folder)

if __name__ == "__main__":
    # Set paths
    input_folder = Path(__file__).parent.parent.parent / "Data" / "processed" / "2_downsampled_normalized"  # Downsampled CSV files
    output_folder = Path(__file__).parent.parent.parent / "Data" / "processed" / "3_split_data_label"
    
    process_csv_folder(input_folder, output_folder)
