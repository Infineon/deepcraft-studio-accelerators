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
Create a Python virtual environment by using the following command (from workspace root):
``` 
python -m venv Tools\venvVTS
```
Activate the environment by running
``` 
Tools\venvVTS\Scripts\Activate
```
Set up the virtual environment by installing the required packages
``` 
pip install -r Tools\requirements.txt
```

---

## 🚀 Quick Start

### Run Processing Pipeline
```powershell
# Make sure virtual environment is activated
Tools\venvVTS\Scripts\Activate

# Run scripts in order (from workspace root)
python Tools\scripts\1_convert_mat_csv.py
python Tools\scripts\2_downsample_combine_normalize.py
python Tools\scripts\3_split_data_label.py
python Tools\scripts\4_generate_training_set.py
```

---

## Pipeline & Scripts

**Purpose:** Transform raw MATLAB sensor data into neural network-ready training datasets.

| # | Script | Processing Step | Details |
|---|--------|----------------|----------|
| **1** | `1_convert_mat_csv.py` | **Convert** .mat → CSV | Flattens MATLAB arrays, preserves variable names |
| | `1a_print_mat_headers.py` | Inspect .mat structure | Shows variables, shapes, data types (debugging) |
| **2** | `2_downsample_combine_normalize.py` | **Downsample + Combine + Normalize** | 10 Hz → 0.1 Hz (99% reduction), Min-Max [0,1] |
| **3** | `3_split_data_label.py` | **Split data/label** | Creates subfolders with data.csv & label.csv |
| **4** | `4_generate_training_set.py` | **Training set** | Splits into 100 folders for training |

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
│ Script: 2_downsample_combine_normalize.py               │
│ - Downsample: 10 Hz → 0.1 Hz (99% reduction)            │
| - Combine data samples to find a common scalaer         |
│ - Normalize: Min-Max [0, 1]                             │
│ - Save scalers for inverse transformation               │
│ Output: Data/processed/2_downsampled_normalized/*.csv   │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│ 3. Split into Data/Label Files                          │
│ Script: 3_split_data_label.py                           │
│ - data.csv: Input features (die_temp, dqCommand, speed) │
│ - label.csv: Target values (coil_temp)                  │
│ Output: Data/processed/3_split_data_label/<filename>/   │
│         ├── data.csv                                    │
│         └── label.csv                                   │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│ 4. Split into Training Parts                            │
│ Script: 4_generate_training_set.py                      │
| - Split the combined file into training folders         |
| - Generate 100 training sets folder                     |
│ - Each part gets data.csv and label.csv                 │
│ Output: Data/processed/4_training_set/dataset001/       │
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
| `dqCommand_combined` | Combined direct and quadrature current (imag² + real²) | - |
| `outputSpeed_rpm` | Motor output speed | RPM |

### Label Data (label.csv files)
| Column | Description | Unit |
|--------|-------------|------|
| `spi_time` | Timestamp | seconds |
| `coil_temp_filtered` | Filtered coil temperature (target variable) | °C |

---
