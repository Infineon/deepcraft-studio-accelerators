To use the script provide the path to the original dataset directory and then another path to the location of where you want the transformed dataset to be located.

Input parameters:
-i  the directory of the input dataset. Note: this dataset should follow the same conventions as the source dataset.
-o  the output directory. This is where the script will create the transformed dataset.
-m  an optional parameter. If included the script will generate a csv file mapping the old data file names to the new in the provided directory. 


Example use: 
python clean_data.py -i "input_dataset_dir" -o "output_dir" -m "mapping_csv_dir"
