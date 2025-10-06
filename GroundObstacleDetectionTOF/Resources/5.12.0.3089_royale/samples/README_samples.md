Royale sample applications
==========================

Some of these samples are only provided in the relevant platform's SDK, for example the Android
example is omitted from the other platforms' SDKs.

For developers targeting the Windows, Mac OS and Linux platforms, the examples are sorted by
language: [C++](#cpp) and [Python](#python)

For the [Android platform](#android), the example combines native C++ with Java.

For the OpenCV and ROS frameworks, there are samples that act as drivers, to use
Royale-supported cameras as inputs to those frameworks.  These are in the
[Integration and drivers](#drivers) section.

For developers with level 2 access, there are [C++](#level2cpp) examples using the additional
functionality.


C++ examples <a name="cpp"></a>
===============================

For C++, the recommended order to read these examples is to start with sampleCameraInfo, and then
sampleRetrieveData.  These also use code from the [Utility](#utility) section.

sampleCameraInfo
----------------

This C++ example shows how to create a camera and query information about the camera, and about the
use cases that the camera supports.  It doesn't capture any images.

This sample can also be used as a tool in other workflows.  It prints the list of supported modes
(use cases) which can be used with Royaleviewer's `--mode` option and as sampleRetrieveData's
command-line argument.  For UVC and Amundsen devices (e.g. pico maxx and pico monstar), it also
prints the USB firmware version.

sampleRetrieveData
------------------

This C++ example shows how to capture image data from a camera.

It's a command line application that does not depend on any GUI toolkit, therefore it only displays
textual information and low-resolution ascii-art of the captured images.

It normally uses the camera's default use case, but the name of a use case can also be given as a
command-line argument. It can also play recorded .rrf files.

sampleQtViewer
----------------

This C++ example shows how to create a Qt GUI that will display the gray images from a connected camera.


sampleRecordRRF
---------------

This C++ example shows how to record rrf-files.

It's a command line application that does not depend on any GUI toolkit, therefore it only displays
textual information.

It uses the camera's default use case.
The parameters to start recording can be passed as command-line parameter:
sampleRecord.exe C:/path/to/file.rrf [numberOfFrames [framesToSkip [msToSkip]]]
where the file parameter is required!

sampleExportPLY
---------------

This C++ example shows how to replay image data from a recorded .rrf file and to do some processing
on each frame in the .rrf, in this example it exports the data to the PLY format (a format for
storing data from 3D-scanners).  Because this example only handles recordings (not live cameras), it
doesn't have the time constraints and thread-handling which make sampleRetrieveData more complicated.

It's a command line application that takes an rrf filename as a command-line argument, and outputs
PLY files in to the current working directory, one file for every frame of the recording.

sampleIReplay
---------------

This C++ example shows how to replay image data from a
recorded .rrf file and manipulate the timing of the frames.

It's a command line application that takes an rrf filename as a command-line argument.

sampleMultiCamera
---------------------

This C++ example shows how to open and use multiple cameras simultaneously.

It shows how to generate an application which creates, initializes, starts and stops capturing with two
or more cameras devices. This application doesn't capture any images, instead the datalistener is
simplified and displays a basic way of data processing.

sampleEventListener
---------------------

This C++ example shows how to implement an EventListener with Royale.


Integration and drivers <a name="drivers"></a>
==============================================

These samples are tools for using Royale-supported cameras as the data source for image processing
frameworks.  They're implemented in C++, but the data can be accessed using the tools of the
framework.

sampleROS
---------

This C++ example is delivered for Linux and OSX platforms and shows the integration of Royale
into a ROS (Robot Operating System) node. Please refer to the README.md in the sampleROS folder
for further details.

sampleROS2
---------
This sample is now hosted on pmd's Github page: https://github.com/pmdtechnologies/pmd-royale-ros


sampleTcpClient
---------
This C++ sample shows how to use an camera of an other computer with TCP. 


C++ examples (Level 2 access code needed) <a name="level2cpp"></a>
==================================================================

sampleProcessingParameters
--------------------------

This C++ example shows how to open the camera with a different access level
and change parameters of the processing pipeline.

sampleRawData
--------------------------

This C++ example shows how to retrieve raw and intermediate data from a camera
by using a different callbackData.

Build Instructions <a name="buildInstructionscpp"></a>
==================================================================
WINDOWS:
------------------
To build the c++ examples first open CMake and set the source code path to the samples folder inside your royale installation. 
The path should look something like this: C:\Program Files\royale\VERSION\samples, where VERSION
is the version of royale. Also set the build directory in CMake to the directory you want to build the sample to. After that 
configure and generate the sample with CMake (set the platform to x64). Next open the royale_samples.sln file from the build directory in Visual Studio. 
Then you can run the sample of your choice.

If the sample you want to build isn't automatically build with the procedure above, you can try this: 
Open CMake and set the source code path to the sample you want to build inside your royale installation. 
The path should look something like this: C:\Program Files\royale\VERSION\samples\cpp\SAMPLE, where VERSION
is the version of royale and SAMPLE is the directory of the sample you want to build. Also set the build directory 
in CMake to the directory you want to build the sample to. After that configure and generate the sample with CMake (set the platform to x64). 
Next open the SAMPLE.sln file from the build directory of the sample in Visual Studio. Finally, run the SAMPLE.

LINUX:
------------------
Create a build folder. Inside this folder call CMake: "cmake path_to_samples" (/home/USERNAME/LIBROYALE/samples, where USERNAME is your username and LIBROYALE is the sdk directory). 
Then call make. 

If the sample you want to build is not automatically build with the procedure above, try this: 
Create a build folder and inside call CMake, but with the path to the sample: "cmake path_to_sample".
Then call make. 

Python examples <a name="python"></a>
====================================

sample_camera_info
------------------

This Python example shows how to create a camera and query information about the camera.

It displays all the use cases that the camera supports and also shows the lens parameters of the camera
connected. It doesn't capture any images.

sample_record_rrf
-----------------

This Python example shows how to record data to an .rrf file.

This sample uses Royale's feature of stopping after a given number of frames are captured, therefore the --frames argument
is required. Also --output argument should be provided, which is the file to write the data to. It uses the camera's default use case.

sample_retrieve_data
--------------------

This Python example shows how to capture image data from a camera.

It uses Python's numpy and matplotlib to process and display the data.


Android example <a name="android"></a>
======================================

We recommend reading the C++ sampleCameraInfo and sampleRetrieveData examples before reading the
Android example.

sampleNativeAndroid
--------------

This JNI example (both C++ and Java) shows how to use a USB camera on Android phones that support
acting as USB hosts.

The data is received in a C++ callback, and the sample shows how to pass the received data to Java
in the NativeCamera.AmplitudeListener::onAmplitudes method.

We recommend reading the non-Android C++ examples sampleCameraInfo and sampleRetrieveData before
reading this one, as the native code is based on those examples.


Utility <a name="utility"></a>
==============================

inc/sample\_utils
-----------------

This contains the PlatformResources utility required for the C and C++ examples to use some cameras
on some platforms. Currently it's only required for UVC cameras on Windows, as the media framework
requires the application to set up the COM environment before calling the library code.
