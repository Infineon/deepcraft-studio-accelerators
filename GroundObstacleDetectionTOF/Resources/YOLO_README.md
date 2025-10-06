# Yolo Data Labeling and Training in Deepcraft

## Project Overview

This document shows the whole pipeline from project creation, data labeling, model training to model evaluation

For more details please check this link out : [https://developer.imagimob.com/](https://developer.imagimob.com/)

<!-- ## Data Collection -->

<!-- * Scrapes data from a single webpage
* Saves data to a CSV file -->

## Project Creation

* Click "New project"
* Click "Vision", "Empty Object Detection Project", set up the project name and select location

![Project Screenshot](0709_screenshot/create_project.png)

* Open the project file

![Project Screenshot](0709_screenshot/click_project.png)

## Add Data

* In "Data" click "Add Data" in the bottom left

![Project Screenshot](0709_screenshot/add_data.png)

* Add Data. Drag or drop your data folder

![Project Screenshot](0709_screenshot/add_data_1.png)

* In the Select Label Format window, in this example we are importing an image dataset without labels, so select "No Labels" checkbox

![Project Screenshot](0709_screenshot/label_format.png)

* Data Import. Click "Next"

![Project Screenshot](0709_screenshot/data_import.png)

* Now we get unlabeled data

![Project Screenshot](0709_screenshot/unlabeled_data.png)

## Data Labeling

* In the Predefined Labels Setion (Top Right), click the "+" Add New label icon to add labels. Labels are created under "Label Name" column

![Project Screenshot](0709_screenshot/unlabeled_data.png)

* Double-click the session file under "Name" from the session table in which you want to add the labels. The session file window opens in a new tab. The predefined labels are displayed in the panel.

![Project Screenshot](0709_screenshot/unlabeled_picture.png)

* Select a label and use Pen Tool to draw bounding box

![Project Screenshot](0709_screenshot/bbox_picture.png)

* Do it for every picture

![Project Screenshot](0709_screenshot/bbox_picture_1.png)

* After all data are labeled, go back to project and click "Rescan Data". Under "Status" there should be all green checks

![Project Screenshot](0709_screenshot/rescan_data.png)

* And click "Redistribute Sets" to split the data into Training, Test and Validation Sets

![Project Screenshot](0709_screenshot/redistribute.png)

* Now data is distributed into three sets as shown under section "Set", we are ready for training

![Project Screenshot](0709_screenshot/redistributed_data.png)

## Model Training

* Go to Training section, and set all the hyperparameters and augmentation setup. There is a default setting already

* Click "Start New Training Job" and click "OK"

![Project Screenshot](0709_screenshot/training.png)

* Type the name and description and click "OK"

![Project Screenshot](0709_screenshot/training_1.png)

* Click "OK" to begin the training. A popup window appears indicating that the job has been started. Once again click "OK" to view the progress of the job in a new tab

![Project Screenshot](0709_screenshot/training_window.png)

![Project Screenshot](0709_screenshot/training_2.png)

* The result will pop out after training is completed. Model can also be downloaded under the "Download" section. There you get .pt file, onnx and tflite file with various accuracy as well as performance reports

![Project Screenshot](0709_screenshot/result_0929.png)

* On the top right, click the "Imagimob Cloud", "Browse Cloud Jobs", to see the current and finished jobs and their results

![Project Screenshot](0709_screenshot/browse_cloud_job.png)

<!-- ## Model Evaluation and Download

* Scrapes data from a single webpage
* Saves data to a CSV file

## Create Project

* Scrapes data from a single webpage
* Saves data to a CSV file

## Create Project

* Scrapes data from a single webpage
* Saves data to a CSV file

<!-- ## Usage

To use this project, simply run the `scrape.py` script and follow the prompts. -->

<!-- ## Requirements

* Python 3.8+
* BeautifulSoup 4.9+

## Installation

To install this project, clone the repository and run `pip install -r requirements.txt`.

## Troubleshooting

If you encounter any issues, try checking the console output for error messages.

## Contributing

Contributions are welcome! Please submit a pull request with your changes.

## License

This project is released under the MIT License.
