"""
Data Downsampling and Normalization Pipeline

This script combines downsampling and normalization in a single pipeline:
1. Downsamples data from 10 Hz to 0.1 Hz (reducing sampling rate)
2. Fits a SINGLE Min-Max scaler on the union of all downsampled files
3. Normalizes each file with the shared scaler and saves it locally
4. Saves the shared scaler once for inverse transformation

Usage:
    python 2_downsample_normalize.py

Input Folder:  ../../Data/processed/1_measurement_data_csv/ (raw CSV files converted from .mat)
Output Folder: ../../Data/processed/2_downsampled_normalized/ (downsampled_normalized_*.csv files and a single shared scaler.pkl)

Technical Details:
- Downsampling ratio: 1:100 (takes every 100th sample)
- Time interval: exactly 10 seconds between samples
- Normalization: Min-Max scaling to [0, 1]
- Data reduction: ~99%
"""

import pandas as pd
import numpy as np
from pathlib import Path
from sklearn.preprocessing import MinMaxScaler
import pickle

def downsample_csv(csv_file_path, original_freq_hz=10, target_freq_hz=0.1):
    """
    Read a CSV file and downsample it from `original_freq_hz` to `target_freq_hz`.
    
    Pipeline Steps:
    1. Read the CSV file
    2. Decimate by taking every Nth sample (N = original / target)
    3. Recalculate spi_time so the output has exactly uniform target-frequency intervals
    
    Args:
        csv_file_path: Path to the CSV file
        original_freq_hz: Original sampling frequency in Hz (default: 10)
        target_freq_hz: Target sampling frequency in Hz (default: 0.1)
    
    Returns:
        (df_downsampled, base_name) on success, or None on error.
    """
    # Read the CSV file
    df = pd.read_csv(csv_file_path)
    
    # Get the base filename without extension
    base_name = csv_file_path.stem
    
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
        print("-" * 60)
        
        return df_downsampled, base_name
        
    except Exception as e:
        print(f"Error processing {csv_file_path.name}: {str(e)}")
        print("-" * 60)
        return None


def process_folder_downsample_normalize(input_folder, output_folder,
                                         original_freq_hz=10, target_freq_hz=0.1,
                                         exclude_columns=['spi_time'], save_scaler=True):
    """
    Process all CSV files in a folder: downsample each, fit a single shared
    MinMaxScaler on the union of all downsampled data, then normalize and save
    each file with that shared scaler.
    
    Args:
        input_folder: Path to folder containing CSV files
        output_folder: Path to output folder
        original_freq_hz: Original sampling frequency (default: 10 Hz)
        target_freq_hz: Target sampling frequency (default: 0.1 Hz)
        exclude_columns: List of column names to exclude from normalization
        save_scaler: Whether to save the single shared scaler object (default: True)
    """
    input_path = Path(input_folder)
    csv_files = list(input_path.glob('*.csv'))
    
    if not csv_files:
        print(f"No CSV files found in {input_folder}")
        return
    
    output_folder.mkdir(parents=True, exist_ok=True)
    
    print(f"Found {len(csv_files)} CSV file(s) to process\n")
    print(f"Pipeline: Downsample ({original_freq_hz} Hz -> {target_freq_hz} Hz) + Normalize [0, 1]")
    print(f"Excluded from normalization: {exclude_columns}")
    print("=" * 60)
    
    # ---------- Step 1: downsample every file (cache results in memory) ----------
    downsampled_list = []
    for csv_file in sorted(csv_files):
        result = downsample_csv(csv_file, original_freq_hz, target_freq_hz)
        if result is not None:
            downsampled_list.append(result)
    
    if not downsampled_list:
        print("No files were successfully downsampled.")
        return
    
    # ---------- Step 2: fit a single shared scaler on the union of all files ----------
    columns_to_normalize = [col for col in downsampled_list[0][0].columns
                            if col not in exclude_columns]
    if not columns_to_normalize:
        print("Warning: No columns to normalize across the dataset.")
        return
    
    combined = pd.concat([df for df, _ in downsampled_list], ignore_index=True)
    scaler = MinMaxScaler(feature_range=(0, 1))
    scaler.fit(combined[columns_to_normalize])
    
    print(f"\nFitted single MinMaxScaler on combined data ({len(combined)} rows total)")
    print(f"Columns to normalize: {columns_to_normalize}")
    print("=" * 60)
    
    # ---------- Step 3: save the combined normalized dataset ----------
    combined_normalized = combined.copy()
    combined_normalized[columns_to_normalize] = scaler.transform(combined[columns_to_normalize])
    combined_file = output_folder / "combined_data.csv"
    combined_normalized.to_csv(combined_file, index=False)
    print(f"\nCombined normalized dataset saved: {combined_file.name}")
    print(f"  Shape: {combined_normalized.shape}")

    # ---------- Step 4: save the single shared scaler ----------
    if save_scaler:
        scaler_file = output_folder / "scaler.pkl"
        with open(scaler_file, 'wb') as f:
            pickle.dump(scaler, f)
        print(f"\nShared scaler saved: {scaler_file}")

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
                                        exclude_columns=['spi_time', 'T_mot_ode_16bit'],
                                        save_scaler=True)
    
    print("\n" + "=" * 60)
    print("Downsampling and normalization complete!")
    print(f"Output saved to: {output_folder}")
    print("\nPipeline Summary:")
    print("  1. Downsampled data from 10 Hz to 0.1 Hz (~99% reduction)")
    print("  2. Recalculated spi_time for uniform 10-second intervals")
    print("  3. Fitted a single MinMaxScaler on the union of all downsampled files")
    print("  4. Normalized all columns (except spi_time) to [0, 1] using the shared scaler")
    print("  5. Saved combined_data.csv (all files downsampled, combined, and normalized)")
    print("  6. Saved the shared scaler (scaler.pkl) for inverse transformation of predictions")
    print("\nNote: Use the saved shared scaler to inverse transform predictions after training.")
    print("      Example: predictions_original = scaler.inverse_transform(predictions)")
