"""
Data Downsampling and Normalization Pipeline

This script combines downsampling and normalization in a single pipeline:
1. Downsamples data from 10 Hz to 0.1 Hz (reducing sampling rate)
2. Normalizes the downsampled data to [0,1] range using Min-Max scaling
3. Saves scaler objects for inverse transformation

Usage:
    python 2_downsample_normalize.py

Input Folder:  ../../Data/processed/1_measurement_data_csv/ (raw CSV files converted from .mat)
Output Folder: ../../Data/processed/2_downsampled_normalized/ (downsampled_normalized_*.csv and scaler_*.pkl files)

Technical Details:
- Downsampling ratio: 1:100 (takes every 100th sample)
- Time interval: exactly 10 seconds between samples
- Normalization: Min-Max scaling to [0, 1]
- Data reduction: ~99%

Project: DEEPCRAFT - Virtual Winding Temperature Sensing v2
"""

import pandas as pd
import numpy as np
from pathlib import Path
from sklearn.preprocessing import MinMaxScaler
import pickle

def downsample_and_normalize_csv(csv_file_path, output_folder,
                                  original_freq_hz=10, target_freq_hz=0.1,
                                  exclude_columns=['spi_time'], save_scaler=True):
    """
    Downsample and normalize CSV data in a single pipeline.
    
    Pipeline Steps:
    1. Downsample: Reduce sampling frequency (10 Hz -> 0.1 Hz)
       - Takes every 100th sample
       - Recalculates spi_time for uniform intervals
    
    2. Normalize: Min-Max scaling to [0, 1]
       - Excludes specified columns (e.g., 'spi_time')
       - Saves scaler for inverse transformation
    
    Args:
        csv_file_path: Path to the CSV file
        output_folder: Path to output folder
        original_freq_hz: Original sampling frequency in Hz (default: 10)
        target_freq_hz: Target sampling frequency in Hz (default: 0.1)
        exclude_columns: List of column names to exclude from normalization
        save_scaler: Whether to save the scaler object (default: True)
    """
    # Read the CSV file
    df = pd.read_csv(csv_file_path)
    
    # Get the base filename without extension
    base_name = csv_file_path.stem
    
    # Create output folder if it doesn't exist
    output_folder.mkdir(parents=True, exist_ok=True)
    
    try:
        # ========== STEP 1: DOWNSAMPLING ==========
        
        # Calculate downsampling ratio
        downsample_ratio = int(original_freq_hz / target_freq_hz)
        
        print(f"Processing: {csv_file_path.name}")
        print(f"  Original shape: {df.shape}")
        print(f"  Original frequency: {original_freq_hz} Hz")
        print(f"  Target frequency: {target_freq_hz} Hz")
        print(f"  Downsampling ratio: 1:{downsample_ratio} (taking every {downsample_ratio}th sample)")
        
        # Downsample: Select every Nth row
        df_downsampled = df.iloc[::downsample_ratio].copy()
        
        # Reset index to ensure proper alignment
        df_downsampled = df_downsampled.reset_index(drop=True)
        
        print(f"  Downsampled shape: {df_downsampled.shape}")
        
        # Recalculate spi_time to have uniform intervals at target frequency
        if 'spi_time' in df_downsampled.columns:
            time_interval = 1.0 / target_freq_hz  # Time between samples (10 seconds for 0.1 Hz)
            start_time = df_downsampled['spi_time'].iloc[0]
            num_samples = len(df_downsampled)
            
            # Display original spi_time statistics before recalculation
            original_time_diffs = df_downsampled['spi_time'].diff().dropna()
            print(f"  Original spi_time intervals - mean: {original_time_diffs.mean():.2f}s, "
                  f"std: {original_time_diffs.std():.4f}s")
            
            # Create uniform time array starting from first sample
            uniform_times = start_time + (pd.Series(range(num_samples)) * time_interval)
            
            # Update spi_time with uniform intervals
            df_downsampled['spi_time'] = uniform_times.values
            
            # Verify uniform spacing
            new_time_diffs = df_downsampled['spi_time'].diff().dropna()
            print(f"  Uniform spi_time intervals: {time_interval:.1f}s (exactly {target_freq_hz} Hz)")
            print(f"  Verification - all intervals exactly: {new_time_diffs.unique()[0]:.1f}s")
        
        # Calculate data reduction percentage
        reduction = (1 - len(df_downsampled) / len(df)) * 100
        print(f"  Data reduction: {reduction:.1f}%")
        
        # ========== STEP 2: NORMALIZATION ==========
        
        # Identify columns to normalize (all except excluded ones)
        columns_to_normalize = [col for col in df_downsampled.columns if col not in exclude_columns]
        
        if not columns_to_normalize:
            print(f"  Warning: No columns to normalize!")
            print("-" * 60)
            return
        
        print(f"  Columns to normalize: {columns_to_normalize}")
        print(f"  Excluded columns: {exclude_columns}")
        
        # Create a copy for normalization
        df_normalized = df_downsampled.copy()
        
        # Initialize MinMaxScaler for normalization to [0, 1] range
        scaler = MinMaxScaler(feature_range=(0, 1))
        
        # Apply normalization
        df_normalized[columns_to_normalize] = scaler.fit_transform(
            df_downsampled[columns_to_normalize]
        )
        
        print(f"  Normalization range: [0, 1]")
        
        # ========== SAVE OUTPUTS ==========
        
        # Save the downsampled and normalized data
        output_file = output_folder / f"downsampled_normalized_{base_name}.csv"
        df_normalized.to_csv(output_file, index=False)
        
        print(f"  Saved: {output_file.name}")
        
        # Save the scaler for inverse transformation
        if save_scaler:
            scaler_file = output_folder / f"scaler_{base_name}.pkl"
            with open(scaler_file, 'wb') as f:
                pickle.dump(scaler, f)
            print(f"  Scaler saved: {scaler_file.name}")
        
        # Display sample statistics for verification
        print(f"  Sample statistics after normalization:")
        for col in columns_to_normalize[:3]:  # Show first 3 normalized columns
            print(f"    {col}: min={df_normalized[col].min():.4f}, "
                  f"max={df_normalized[col].max():.4f}, "
                  f"mean={df_normalized[col].mean():.4f}")
        
        print(f"  Final shape: {df_normalized.shape}")
        print("-" * 60)
        
    except Exception as e:
        print(f"Error processing {csv_file_path.name}: {str(e)}")
        print("-" * 60)

def process_folder_downsample_normalize(input_folder, output_folder,
                                         original_freq_hz=10, target_freq_hz=0.1,
                                         exclude_columns=['spi_time'], save_scaler=True):
    """
    Process all CSV files in a folder: downsample and normalize.
    
    This function processes data files typically containing:
    - ID_ prefixed files: Input data (die_temp_filtered, dqCommand_combined, outputSpeed_rpm)
    - TD_ prefixed files: Target data (coil_temp_filtered)
    
    Args:
        input_folder: Path to folder containing CSV files
        output_folder: Path to output folder
        original_freq_hz: Original sampling frequency (default: 10 Hz)
        target_freq_hz: Target sampling frequency (default: 0.1 Hz)
        exclude_columns: List of column names to exclude from normalization
        save_scaler: Whether to save scaler objects for each file
    """
    input_path = Path(input_folder)
    
    # Find all CSV files
    csv_files = list(input_path.glob('*.csv'))
    
    if not csv_files:
        print(f"No CSV files found in {input_folder}")
        return
    
    print(f"Found {len(csv_files)} CSV file(s) to process\n")
    print(f"Pipeline: Downsample ({original_freq_hz} Hz -> {target_freq_hz} Hz) + Normalize [0, 1]")
    print(f"Excluded from normalization: {exclude_columns}")
    print("=" * 60)
    
    # Process each file
    for csv_file in sorted(csv_files):
        downsample_and_normalize_csv(csv_file, output_folder,
                                      original_freq_hz, target_freq_hz,
                                      exclude_columns, save_scaler)

if __name__ == "__main__":
    # Set paths
    input_folder = Path(__file__).parent.parent.parent / "Data" / "processed" / "1_measurement_data_csv"  # Raw CSV files from .mat conversion
    output_folder = Path(__file__).parent.parent.parent / "Data" / "processed" / "2_downsampled_normalized"
    
    # Process all CSV files in the 1_measurement_data_csv folder
    # 1. Downsample from 10 Hz to 0.1 Hz
    # 2. Normalize to [0, 1] range (excluding 'spi_time')
    process_folder_downsample_normalize(input_folder, output_folder,
                                        original_freq_hz=10,
                                        target_freq_hz=0.1,
                                        exclude_columns=['spi_time'],
                                        save_scaler=True)
    
    print("\n" + "=" * 60)
    print("Downsampling and normalization complete!")
    print(f"Output saved to: {output_folder}")
    print("\nPipeline Summary:")
    print("  1. Downsampled data from 10 Hz to 0.1 Hz (~99% reduction)")
    print("  2. Recalculated spi_time for uniform 10-second intervals")
    print("  3. Normalized all columns (except spi_time) to [0, 1] range")
    print("  4. Saved scaler objects for inverse transformation of predictions")
    print("\nNote: Use saved scalers to inverse transform predictions after training.")
    print("      Example: predictions_original = scaler.inverse_transform(predictions)")
