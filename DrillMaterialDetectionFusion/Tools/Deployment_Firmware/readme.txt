When creating a project under 'C:\ModusProject', the steps are as follows:
1. Move the Deployment_Firmware folder under 'C:\ModusProject'.
2. Launch 'Modus-Shell (Cygwin)' by selecting 'Modustoolbox3.7 -> modus-shell' from the Windows Start menu.
3. In modus-shell, change directory to C:\ModusProject\Deployment_Firmware\Deploy_Fusion (the Deploy_Fusion project located within the Deployment_Firmware workspace).
    $ cd /cygdrive/c/ModusProject/Deployment_Firmware/Deploy_Fusion
4. Run the following command in modus-shell to generate the mtb_shared folder.
    $ make getlibs
5. Run the following command in modus-shell to generate the configuration file for the Modustoolbox IDE.
    $ make eclipse
6. Launch the application by selecting Infineon Technologies -> Eclipse for Modustoolbox IDE from the Windows Start menu.
7. In the Modustoolbox IDE QuickPanel, click ‘Import Existing Application In-Place’, select C:\MtbProj\Deploy_Fusion, then click Finish.
    Note: This may take some time.
8. In the Modustoolbox IDE, select ‘Project -> build all’