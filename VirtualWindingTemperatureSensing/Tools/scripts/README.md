# Data Processing Scripts

This folder contains Python scripts for processing winding temperature sensing data. All scripts are located in `Tools/scripts/` and are numbered in the recommended execution order for a complete data processing pipeline.

---

## 📋 Table of Contents

1. [Requirements](#requirements)
2. [Quick Start](#quick-start)
3. [Pipeline & Scripts](#pipeline--scripts)
4. [Processing Workflow](#processing-workflow)
5. [Data Column Definitions](#data-column-definitions)

---

## Requirements

### Python Version
- Python 3.7 or higher (Python 3.10+ recommended)

### Python Dependencies
Create Python virtual environment by using the following command:
``` 
python -m venv Tools\venvVTS
```
Set up the virtual environment by running the following command:
``` 
pip install -r requirements.txt
```


### System Requirements
- **RAM:** 8GB minimum (16GB recommended for large datasets)
- **Disk Space:** ~5GB for complete processing pipeline
- **OS:** Windows 10/11, Linux, or macOS

---

## 🚀 Quick Start

### Run Processing Pipeline
```powershell
# Make sure virtual environment is activated
Tools\venvVTS\Scripts\Activate.ps1

# Run scripts in order (from workspace root)
python Tools\scripts\1_convert_mat_csv.py
python Tools\scripts\2_downsample_normalize.py
python Tools\scripts\3_separate_input_data_target_data.py
python Tools\scripts\4_split_csv_multiple_parts.py
```

---

## Pipeline & Scripts

**Purpose:** Transform raw MATLAB sensor data into neural network-ready training datasets.

| # | Script | Processing Step | Details |
|---|--------|----------------|----------|
| **1** | `1_convert_mat_csv.py` | **Convert** .mat → CSV | Flattens MATLAB arrays, preserves variable names |
| | `1_print_mat_headers.py` | Inspect .mat structure | Shows variables, shapes, data types (debugging) |
| **2** | `2_downsample_normalize.py` | **Downsample + Normalize** | 10 Hz → 0.1 Hz (99% reduction), Min-Max [0,1] |
| **3** | `3_separate_input_data_target_data.py` | **Split data/label** | Creates subfolders with data.csv & label.csv |
| **4** | `4_split_csv_multiple_parts.py` | **Partition** (optional) | Splits into N parts (default: 10, user-configurable) |

**Output:** Organized subfolders with `data.csv` (input features) and `label.csv` (target values) ready for DEEPCRAFT Studio.

---

## Processing Workflow

### Standard Workflow

```
┌─────────────────────────────────────────────────────────┐
│ Raw .mat files                                          │
│ Input:  Data/measurement_data/*.mat                     │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│ 1. MAT to CSV Conversion                                │
│ Script: 1_convert_mat_csv.py                            │
│ Output: Data/processed/1_measurement_data_csv/*.csv     │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│ 2. Downsample + Normalize                               │
│ Script: 2_downsample_normalize.py                       │
│ - Downsample: 10 Hz → 0.1 Hz (99% reduction)            │
│ - Normalize: Min-Max [0, 1]                             │
│ - Save scalers for inverse transformation               │
│ Output: Data/processed/2_downsampled_normalized/*.csv   │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│ 3. Split into Data/Label Files                          │
│ Script: 3_separate_input_data_target_data.py            │
│ - Creates subfolder per source file                     │
│ - data.csv: Input features (die_temp, dqCommand, speed) │
│ - label.csv: Target values (coil_temp)                  │
│ Output: Data/processed/3_split_data_label/<filename>/   │
│         ├── data.csv                                    │
│         └── label.csv                                   │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│ 4. Split into Training Parts (Optional)                 │
│ Script: 4_split_csv_multiple_parts.py                   │
│ - User configurable number of parts (default: 10)       │
│ - Each part gets data.csv and label.csv                 │
│ Output: Data/processed/4_training_data_set/partNN_*/    │
│         ├── data.csv                                    │
│         └── label.csv                                   │
└─────────────────────────────────────────────────────────┘
                       │
                       ▼
              Ready for DEEPCRAFT Studio
```

---

## Data Column Definitions

### Input Features (data.csv files)
| Column | Description | Unit |
|--------|-------------|------|
| `spi_time` | Timestamp | seconds |
| `die_temp_filtered` | Filtered die temperature | °C |
| `dqCommand_combined` | Combined direct and quadrarture current (imag² + real²) | - |
| `outputSpeed_rpm` | Motor output speed | RPM |

### Label Data (label.csv files)
| Column | Description | Unit |
|--------|-------------|------|
| `spi_time` | Timestamp | seconds |
| `coil_temp_filtered` | Filtered coil temperature (target variable) | °C |

---
