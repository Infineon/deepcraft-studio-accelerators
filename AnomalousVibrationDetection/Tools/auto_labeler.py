import os

labelname = "anomaly"

# Function to get the duration of a .data file in seconds
def get_data_duration(filepath):
    with open(filepath, 'r') as data_file:
        lines = data_file.readlines()
        # Skip the header line
        time_values = [float(line.split(',')[0]) for line in lines[1:]]
        duration = max(time_values)
        return duration

# Main function to edit .label files
def edit_label_files(folder_path):
    for root, dirs, files in os.walk(folder_path):
        for filename in files:
            if filename.endswith('.data'):
                path_to_data = os.path.join(root, filename)
                path_to_label = os.path.join(root, "label.label")
                
                for l_filename in files:
                    if l_filename.endswith('.label'):
                        path_to_label = os.path.join(root, l_filename)   
                    
                # Get the duration of the .data file
                duration = get_data_duration(path_to_data)
                
                # Check if a .label file already exists
                if os.path.exists(path_to_label):
                    # Open the existing .label file and overwrite its content
                    with open(path_to_label, 'w') as label_file:
                        label_file.write("Time(Seconds),Length(Seconds),Label(string),Confidence(double),Comment(string)\n")
                        label_file.write("0," + str(duration) + "," + labelname + ",1,\n")
                    print(f"Updated existing .label file: {path_to_label}")
                else:
                    # Create a new .label file
                    with open(path_to_label, 'w') as label_file:
                        label_file.write("Time(Seconds),Length(Seconds),Label(string),Confidence(double),Comment(string)\n")
                        label_file.write("0," + str(duration) + "," + labelname + ",1,\n")
                    print(f"Created new .label file: {path_to_label}")

current_directory = os.getcwd()

edit_label_files(current_directory)
