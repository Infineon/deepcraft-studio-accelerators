"""
MATLAB to CSV Converter

This script converts MATLAB .mat files to CSV format for further processing.
It flattens all MATLAB array data to 1D and preserves variable names as column headers.

Usage:
    python 1_convert_mat_csv.py

Input Folder:  ../../Data/measurement_data/ (MATLAB .mat files)
Output Folder: ../../Data/processed/1_measurement_data_csv/ (.csv files with same base name)
"""

import os
import scipy.io
import pandas as pd
from pathlib import Path
import numpy as np

def mat_to_csv(mat_file_path, output_folder=None):
    """
    Convert a .mat file to CSV format, flattening all data.
    
    Args:
        mat_file_path: Path to the .mat file
        output_folder: Optional output folder path. If None, saves in same directory as .mat file
    """
    # Load the .mat file
    mat_data = scipy.io.loadmat(mat_file_path)
    
    # Get the base filename without extension
    base_name = Path(mat_file_path).stem
    
    # Set output directory
    if output_folder is None:
        output_folder = Path(mat_file_path).parent
    else:
        output_folder = Path(output_folder)
        output_folder.mkdir(parents=True, exist_ok=True)
    
    # Get non-metadata keys
    keys = [key for key in mat_data.keys() if not key.startswith('__')]
    
    # Create dictionary for DataFrame - flatten all data
    data_dict = {}
    
    for key in keys:
        value = mat_data[key]
        
        if isinstance(value, np.ndarray):
            # Flatten all arrays to 1D
            data_dict[key] = value.flatten()
        else:
            data_dict[key] = value
    
    try:
        # Create DataFrame
        df = pd.DataFrame(data_dict)
        
        # Create output filename
        output_file = output_folder / f"{base_name}.csv"
        
        # Save to CSV
        df.to_csv(output_file, index=False)
        print(f"\nSaved: {output_file}")
        print(f"Shape: {df.shape}")
        print(f"CSV Headers: {list(df.columns)}")
        print("-" * 50)
        
    except Exception as e:
        print(f"Could not convert {mat_file_path.name}: {str(e)}")

def process_folder(input_folder, output_folder=None):
    """
    Process all .mat files in a folder.
    
    Args:
        input_folder: Path to folder containing .mat files
        output_folder: Optional output folder path
    """
    input_path = Path(input_folder)
    
    # Find all .mat files
    mat_files = list(input_path.glob('*.mat'))
    
    if not mat_files:
        print(f"No .mat files found in {input_folder}")
        return
    
    print(f"Found {len(mat_files)} .mat file(s)")
    
    # Process each file
    for mat_file in sorted(mat_files):
        print(f"\nProcessing: {mat_file.name}")
        mat_to_csv(mat_file, output_folder)

if __name__ == "__main__":
    # Set paths
    input_folder = Path(__file__).parent.parent.parent / "Data" / "measurement_data"
    output_folder = Path(__file__).parent.parent.parent / "Data" / "processed" / "1_measurement_data_csv"  # Folder for raw CSV data
    
    process_folder(input_folder, output_folder)