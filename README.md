# DEEPCRAFT™ Studio Accelerators
This repository contains DEEPCRAFT™ Studio Accelerators - deep learning based projects for various use-cases designed as starting points for building custom applications. These projects have data and a project file that is ready to be used with DEEPCRAFT™ Studio.

This repository is automatically pulled and content is generated in DEEPCRAFT™ Studio. For the best experience, access these models through DEEPCRAFT™ Studio.

For commercial use, our standard terms and conditions applies, https://developer.imagimob.com/legal/studio-terms-and-conditions.

## Usage
These projects are designed to be used through DEEPCRAFT™ Studio (https://www.imagimob.com/studio) and should be accessed through that platform.

## Contribution
All users are welcome to submit new models/projects, subject to the Infineon DEEPCRAFT™ Studio Accelerators review process.

## Submission Process
To submit a project, create a pull request with your data and DEEPCRAFT™ Studio project file (.improj) using the automation tool provided below.

Use the available `PROJECT_TEMPLATE` to structure your project:
* Rename your accelerator project folder. For instance, the name can contain the use case and the sensor used in the project. Check the project names of the already available projects. Make sure to pick up a name which is not been already used
* Add content to the relevant folders and delete the ones which do not apply to your project. Data folder is mandatory. Add your custom folder(s) if needed
* Set up the provided project file example or replace it with your own project file
* Add content to the project `README.md` file making sure to include the following information:
    - Use-case description
    - Sensor settings specifications and data description
    - Guidelines for collecting and expanding the dataset
    - Recommended path to production, including steps to make the model production-ready
* Before the submission
    - Make sure to remove all the `README.md` files contained in all subfolders of the `PROJECT_TEMPLATE` if you use it
    - Fill in the fields in the `metadata.json` file as follows:
        - `title` (max 40 characters): give a title to your project making sure it does not exist already. For instance, use words describing the use case and sensor. Get inspired by the existing ones in DEEPCRAFT™ Studio.
        - `description` (max 100 characters): briefly describe your project. Get inspired by the existing ones in DEEPCRAFT™ Studio.
        - `algorithm`: choose between **Classification** or **Regression**
        - `sensors`: specify the sensor used in you project. Choose from the existing ones in DEEPCRAFT™ Studio: **IMU & Vibration**, **Microphone**, **Capacitive & Inductive Sensing**, **Camera**, etc.
        - `domain`: Specify the domain(s) of your project: **Audio**, **Voice**, **Vision**, etc.
	    - `application`: Specify the application(s) of your project: **Smart Home**, **Smart TV**, **Appliances**, **Wearables**, **Games**, etc.
        - `use_case`: Specify the use case(s) of your project: **Object Detection**, **Voice Control**, **Speech Recognition**, etc.
        - `kit`: Specify the Infineon's kit(s) your project is compatible with: **PSoC-6 Pioneer Kit**, **PSoC-6 AI Kit**, **PSoC-Edge AI Kit**, etc.
        - `device`: Specify the device(s) your project is compatible with: **PSoC-4**, **PSoC-6**, **PSoC-Edge**, **AURIX**, etc.
        - `workflow`: Choose between **ML Development** and/or **ML Deployment**.

Once the project is ready, you can download [pr_tool.zip](https://api.imagimob.com/v1/Data/Object/pr_tool.zip) and run:

```bash
tar -xf <download-path>\pr_tool.zip
cd pr_tool
python .\pr_tool.py --path <project-path>
```

where `<project-path>` is the root path of the studio accelerator project. For more information review the tools' `README.md` file.

Please be aware that you will need a GitHub Account. When you run the tool using the command shown above it will authenticate using your GitHub account, fork this repository and prepare the pull request. Once ready, it will open the pull request in a window in your browser. Please add the relevant detail requested to complete your pull request which will aid in the review process and then submit.

***NOTE:*** The pipeline will automatically generate the pre-processing, model predictions and train some models based on the default best model selection from DEEPCRAFT™ Studio. If you would not like to have this, then please specify in the pull request if that should not be what should be published.

