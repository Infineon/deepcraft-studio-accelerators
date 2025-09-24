import argparse
from pathlib import Path
import pandas as pd

def parse_args():
    parser = argparse.ArgumentParser(
        "Script to downsample the dataset to one-third of its original size")

    parser.add_argument(
        "--input-dir", "-i",
        type=str,
        required=True,
        help="Directory where the collected data files are placed.")

    return parser.parse_args()

def search_for_data_files(search_dir: Path, data_file_wildcard: str):
    """
    Searches recursively for files named according to data_file_wildcard
    """
    data_files = list(search_dir.rglob(data_file_wildcard))
    if not data_files:
        print(f"Warning: Could not find any data files named: {data_file_wildcard}")
    
    return data_files


def main():
    args = parse_args()
    input_dir = Path(args.input_dir)

    # Recursively search for .data files
    data_files = search_for_data_files(input_dir, '*.data')

    for datafile in data_files:
        print("------------------------")
        print("Data File:", datafile)
        print("------------------------")
        
        # loading data to csv
        data_df = pd.read_csv(datafile)
		
        data_df = data_df.iloc[::3, :]  # Selects every 3rd raw starting from 0
		
		#save to file
        data_df.to_csv(datafile, index = False)

        
if __name__ == "__main__":
    main()