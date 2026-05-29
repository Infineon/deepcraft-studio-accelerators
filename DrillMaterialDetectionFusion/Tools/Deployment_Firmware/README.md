# Deployment Firmware
The Deployment Firmware is a ModusToolbox project for PSOC Edge E84 AI Evaluation Kit. It is a slightly modified version of the PSOC Edge E84 DEEPCRAFT Deploy Audio Code Example to allow for multi-sensor initialization and preprocessing.

## Use-case description
This project is intended to be used to deploy sensor-fusion models, particularly the Drill Material Sensor Fusion Studio Accelerator. It can also be modified to deploy other sensor-fusion models.

## Project Creation
When creating a project under 'C:\<path_accelerator_project>', the steps are as follows:
1. Move the Deployment_Firmware folder under 'C:\<path_accelerator_project>'.
2. Launch 'Modus-Shell (Cygwin)' by selecting 'Modustoolbox3.7 -> modus-shell' from the Windows Start menu.
3. In modus-shell, change directory to C:\<path_accelerator_project>\Deployment_Firmware\Deploy_Fusion (the Deploy_Fusion project located within the Deployment_Firmware workspace).
    $ cd /cygdrive/c/ModusProject/Deployment_Firmware/Deploy_Fusion
4. Run the following command in modus-shell to generate the mtb_shared folder.
    $ make getlibs
5. Run the following command in modus-shell to generate the configuration file for the Modustoolbox IDE.
    $ make eclipse
6. Launch the application by selecting Infineon Technologies -> Eclipse for Modustoolbox IDE from the Windows Start menu.
7. In the Modustoolbox IDE QuickPanel, click ‘Import Existing Application In-Place’, select C:\<path_accelerator_project>\Deployment_Firmware, then click Finish.
    Note: This may take some time.
8. In the Modustoolbox IDE, select ‘Project -> build all’

After the project is built successfully, program the board and visualize the output in a serial terminal like TeraTerm.