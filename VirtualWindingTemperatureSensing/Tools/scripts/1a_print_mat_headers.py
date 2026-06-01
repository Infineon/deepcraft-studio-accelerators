"""
MATLAB File Inspector

This script inspects MATLAB .mat files and prints their structure without conversion.
Displays all variable names, shapes, and data types for debugging and understanding data structure.

Usage:
    python 1_print_mat_headers.py

Input Folder:  ../../Data/measurement_data/ (MATLAB .mat files)
Output:        Console output showing file structure
"""

import scipy.io
from pathlib import Path

def print_mat_headers(mat_file_path):
    """
    Print the keys (headers) from a .mat file.
    
    Args:
        mat_file_path: Path to the .mat file
    """
    # Load the .mat file
    mat_data = scipy.io.loadmat(mat_file_path)
    
    print(f"\nFile: {mat_file_path.name}")
    print("=" * 50)
    
    # Get non-metadata keys
    keys = [key for key in mat_data.keys() if not key.startswith('__')]
    
    print(f"Keys: {keys}")
    print(f"Total variables: {len(keys)}")
    
    # Print shape information for each key
    for key in keys:
        value = mat_data[key]
        if hasattr(value, 'shape'):
            print(f"  {key}: shape {value.shape}, dtype {value.dtype}")
        else:
            print(f"  {key}: {type(value)}")

def process_folder(input_folder):
    """
    Process all .mat files in a folder and print their headers.
    
    Args:
        input_folder: Path to folder containing .mat files
    """
    input_path = Path(input_folder)
    
    # Find all .mat files
    mat_files = list(input_path.glob('*.mat'))
    
    if not mat_files:
        print(f"No .mat files found in {input_folder}")
        return
    
    print(f"Found {len(mat_files)} .mat file(s)\n")
    
    # Process each file
    for mat_file in sorted(mat_files):
        print_mat_headers(mat_file)

if __name__ == "__main__":
    # Set path to raw folder
    input_folder = Path(__file__).parent.parent.parent / "Data" / "measurement_data"
    
    process_folder(input_folder)