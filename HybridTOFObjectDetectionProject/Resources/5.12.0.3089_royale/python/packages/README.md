roypypack - the Royale Python wrapper package
=============================================

The **Royale** Python wrapper package provides a source distribution (sdist, *.tar.gz) and, depending
on the platform, also a binary distribution (wheel, *.whl) of the Royale Python wrapper.

The Royale software package provides a light-weight camera framework for time-of-flight (ToF) cameras.
While being tailored to PMD cameras, the framework enables partners and customers to evaluate and/or
integrate 3D TOF technology on/in their target platform. This reduces time to first demo and time to
market.

Royale contains all the logic which is required to operate a ToF based camera. The user doesn't need to
care about setting registers, but can conveniently control the camera via a high-level interface.
The Royale framework is completely designed in C++ using the C++11 standard.

To use Royale Python wrapper "roypy" and the Python samples you have to install numpy and matplotlib,
because they are used for the visualization of the data.
This version of the Royale Python wrapper was built against Python 3.10.9.
To use it you will need a Python version with the same major and minor version.
If you want to use the Python wrapper with a different Python version please refer to
the steps in "SDist Installation".


Operating Systems
=================

Royale for Python (Roypy) supports the following operating systems:

- Windows 10
- Linux (tested on Ubuntu 20.04)
- Linux ARM (32Bit version tested on Raspbian GNU/Linux 10 (Buster) Raspberry Pi reference 2020-08-20
             64Bit version tested on a Raspberry 4 with Ubuntu 20.04 ARM 64)


Hardware Requirements
=====================

On x86 platforms the processing part will require AVX2 support.


Python Dependencies
===================

The Python wrapper is designed to work with numpy 1.24.2 and specific versions of Python:

 Windows 10            - Python 3.10
 Ubuntu 20.04 64bit    - Python 3.8
 Linux ARM 32bit       - Python 3.7
 Linux ARM 64bit       - Python 3.8
 MacOs Arm 64bit       - Python 3.11

If you want to use a different Python version please have a look at the following section under
"SDist Installation".


Installation
============

The following Python packages are required to run roypy or to build the wheel using the sdist:
- numpy>=1.24.2
- matplotlib

For a Windows installation of Python, you will need the following additional packages:
- pywin32 (contains the pythoncom packages needed by roypy)

Under Linux, depending on the configuration of your (virtual) Python environment,
you might encounter library not found errors.
Depending on which library is not found, you either need to modify the LD_LIBRARY_PATH to include 
the "lib" folder of your Python installation or the roypypack wheel installation folder 
(e.g. <your_python_path>/site-packages/roypypack).


Wheel (*.whl) Installation
--------------------------

Windows:
To install the wheel from the Royale Python packages folder 
(e.g. C:\Program Files\royale\5.12.0.3089\python\packages) using the Windows PowerShell, 
the command for Royale version 5.12.0.3089 under Windows for example is:
    pip install .\roypypack-5.12.0.3089-cp310-cp310-win_amd64.whl

Linux:
To install the wheel from the Royale Python packages folder (e.g. /home/royale_user/apps/libroyale-5.12.0.3089-LINUX-x86-64Bit/python/packages),
type for Royale version 5.12.0.3089 under Linux for example:
    python3 -m pip install roypypack-5.12.0.3089-cp38-cp38-manylinux_2_31_x86_64.whl
You also need to set the LD_LIBRARY_PATH to where the wheel is installed so that the Royale libraries are found. For example:
    export LD_LIBRARY_PATH=/home/royale_user/.local/lib/python3.8/site-packages/roypypack

If for any reason the wheel cannot be installed or errors occur while using the installed wheel package it is 
advised to install the sdist package since it will be compiled specifically for your machine during installation.


SDist (*.tar.gz) Installation
-----------------------------

Your Python environment needs to have the "build" package installed. Install it via
    pip install build
Additionally, you need to have a working C++ build environment installed and configured - i.a. CMake,
Microsoft Visual Studio 2022 under Windows and build-essential (among others) under Ubuntu 20.04. 

Windows:
To build and install your own wheel via the sdist package from the Royale Python packages folder (e.g. C:\Program Files\royale\5.12.0.3089\python\packages) using the Windows PowerShell, type
    pip install .\roypypack-5.12.0.3089.tar.gz --config-settings=cmake.define.ROYALE_DIR="<Royale installation folder>"
whereas the default "<Royale installation folder>" for Royale version 5.12.0.3089 is "C:/Program Files/royale/5.12.0.3089".

Installing the sdist should look similar to the following in MS Windows PowerShell:

PS C:\Program Files\royale\5.12.0.3089\python\packages> pip install .\roypypack-5.12.0.3089.tar.gz --config-settings=cmake.define.ROYALE_DIR="C:\Program Files\royale\5.12.0.3089"
Processing c:\program files\royale\5.12.0.3089\python\packages\roypypack-5.12.0.3089.tar.gz
  Installing build dependencies ... done
  Getting requirements to build wheel ... done
  Installing backend dependencies ... done
  Preparing metadata (pyproject.toml) ... done
Collecting numpy==1.24.2 (from roypypack==5.12.0.3089)
  Using cached numpy-1.24.2-cp311-cp311-win_amd64.whl (14.8 MB)
Building wheels for collected packages: roypypack
  Building wheel for roypypack (pyproject.toml) ... done
  Created wheel for roypypack: filename=roypypack-5.12.0.3089-cp311-cp311-win_amd64.whl size=4021954 sha256=d156bd115124a532e9702cc4c85fb214806b7482b5e4c0a8ac7cce84db552caa
  Stored in directory: c:\users\royale_user\appdata\local\pip\cache\wheels\9b\ef\7d\e31ba166883ebf80be1032eb9985e53263ae6d08ad66a8d710
Successfully built roypypack
Installing collected packages: numpy, roypypack
Successfully installed numpy-1.24.2 roypypack-5.12.0.3089

Linux:
To build and install your own wheel via the sdist package from the Royale Python packages folder (e.g. /home/royale_user/apps/libroyale-5.12.0.3089-LINUX-x86-64Bit/python/packages) using the shell, type
    python3 -m pip install roypypack-5.12.0.3089.tar.gz --config-settings=cmake.define.ROYALE_DIR="<Royale installation folder>"
whereas the "<Royale installation folder>" for Royale version 5.12.0.3089 could be "/home/royale_user/apps/libroyale-5.12.0.3089-LINUX-x86-64Bit" under Linux.
