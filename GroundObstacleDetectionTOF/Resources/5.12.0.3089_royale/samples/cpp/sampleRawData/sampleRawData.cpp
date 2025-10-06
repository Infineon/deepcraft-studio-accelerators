/****************************************************************************\
* Copyright (C) 2017 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#include <chrono>
#include <iostream>
#include <royale.hpp>
#include <thread>

#include <sample_utils/PlatformResources.hpp>

#ifndef ROYALE_ACCESS_CODE_LEVEL2
#define ROYALE_ACCESS_CODE_LEVEL2 "" // Insert activation code here
#endif

using namespace sample_utils;
using namespace std;

class MyRawListener : public royale::IRawDataListener {
    void onNewData(const royale::RawData *data) override {
        // RawData contains everything needed for the calibration of modules
        auto raw = data;

        auto idx = raw->width * raw->height / 2 + raw->width / 2;
        cout << "Raw value : " << raw->rawData[idx] << endl;

        cout << "Illumination temperature : " << raw->illuminationTemperature << endl;

        cout << "Modulation frequencies : ";
        for (auto curMod : raw->modulationFrequencies) {
            cout << curMod << " ";
        }
        cout << endl;

        cout << "Illumination enabled : ";
        for (auto curIllu : raw->illuminationEnabled) {
            // We need the cast, otherwise the uint8_t is interpreted as char
            cout << static_cast<unsigned int>(curIllu) << " ";
        }
        cout << endl;
    }
};

int main() {
    // Windows requires that the application allocate these, not the DLL.
    PlatformResources resources;

    // This is the data listener which will receive callbacks.  It's declared
    // before the cameraDevice so that, if this function exits with a 'return'
    // statement while the camera is still capturing, it will still be in scope
    // until the cameraDevice's destructor implicitly deregisters the listener.
    MyRawListener listener;

    // Check if we have the appropriate access level
    // (the following operations need Level 2 access)
    if (royale::CameraManager::getAccessLevel(ROYALE_ACCESS_CODE_LEVEL2) < royale::CameraAccessLevel::L2) {
        cerr << "Please insert the activation code for Level 2 into the define at the beginning of this program!" << endl;
        return 1;
    }

    // this represents the main camera device object
    unique_ptr<royale::ICameraDevice> cameraDevice;

    // the camera manager will query for a connected camera
    {
        royale::CameraManager manager(ROYALE_ACCESS_CODE_LEVEL2);

        auto camlist = manager.getConnectedCameraList();
        cout << "Detected " << camlist.size() << " camera(s)." << endl;
        if (!camlist.empty()) {
            cout << "CamID for first device: " << camlist.at(0).c_str() << " with a length of (" << camlist.at(0).length() << ")" << endl;
            cameraDevice = manager.createCamera(camlist[0]);
        }
    }
    // the camera device is now available and CameraManager can be deallocated here

    if (cameraDevice == nullptr) {
        cerr << "Cannot create the camera device" << endl;
        return 1;
    }

    // IMPORTANT: call the initialize method before working with the camera device
    if (cameraDevice->initialize() != royale::CameraStatus::SUCCESS) {
        cerr << "Cannot initialize the camera device" << endl;
        return 1;
    }

    if (cameraDevice->registerRawDataListener(&listener) != royale::CameraStatus::SUCCESS) {
        cerr << "Couldn't register the extended data listener" << endl;
        return 1;
    }

    // Set the callbackData you want to receive
    // (if you call cameraDevice->setCallbackData (CallbackData::Raw)
    // before initializing the camera Royale can also open cameras without
    // calibration data and return raw images)
    if (cameraDevice->setCallbackData(royale::CallbackData::Raw) != royale::CameraStatus::SUCCESS) {
        cerr << "Cannot set the callbackData" << endl;
        return 1;
    }

    // start capture mode
    if (cameraDevice->startCapture() != royale::CameraStatus::SUCCESS) {
        cerr << "Error starting the capturing" << endl;
        return 1;
    }

    // let the camera capture for some time
    this_thread::sleep_for(chrono::seconds(5));

    // stop capture mode
    if (cameraDevice->stopCapture() != royale::CameraStatus::SUCCESS) {
        cerr << "Error stopping the capturing" << endl;
        return 1;
    }

    return 0;
}
