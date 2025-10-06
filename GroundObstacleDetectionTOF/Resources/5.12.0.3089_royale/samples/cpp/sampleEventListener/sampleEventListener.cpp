/****************************************************************************\
 * Copyright (C) 2022 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#include <royale.hpp>
#include <royale/IEvent.hpp>
#include <sample_utils/PlatformResources.hpp>

#include <thread>

using namespace royale;
using namespace sample_utils;

/**
 * This class reports on events from Royale.
 */
class MyListener : public IEventListener {
  public:
    MyListener(){};
    void onEvent(std::unique_ptr<royale::IEvent> &&event) override {
        royale::EventSeverity severity = event->severity();

        switch (severity) {
        case royale::EventSeverity::ROYALE_INFO:
        case royale::EventSeverity::ROYALE_WARNING:
            std::cout << event->describe() << std::endl;
            break;
        case royale::EventSeverity::ROYALE_ERROR:
        case royale::EventSeverity::ROYALE_FATAL:
            std::cerr << "Stopping capture because of event: " << event->describe() << std::endl;
            cameraDevice->stopCapture();
            break;
        }
    }

    std::unique_ptr<royale::ICameraDevice> cameraDevice;
};

int main(int argc, char **argv) {
    // Windows requires that the application allocate these, not the DLL.
    PlatformResources resources;

    // Event listener which will recieve callback when an event occurs.
    MyListener listener;
    {
        royale::CameraManager manager;

        auto camlist = manager.getConnectedCameraList();

        std::cout << "Detected " << camlist.size() << " camera(s)." << std::endl;
        if (!camlist.empty()) {
            std::cout << "CamID for first device: " << camlist.at(0).c_str() << " with a length of (" << camlist.at(0).length() << ")" << std::endl;
            listener.cameraDevice = manager.createCamera(camlist[0]);
        }

        if (listener.cameraDevice == nullptr) {
            std::cerr << "Cannot create the camera device" << std::endl;
            return 1;
        }
    }
    listener.cameraDevice->registerEventListener(&listener);

    auto status = listener.cameraDevice->initialize();
    if (status != royale::CameraStatus::SUCCESS) {
        std::cerr << "Cannot initialize the camera device, error string : " << getErrorString(status) << std::endl;
        return 1;
    }

    // start capturing from the device
    if (listener.cameraDevice->startCapture() != CameraStatus::SUCCESS) {
        std::cerr << "Error starting the capturing" << std::endl;
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    bool capturing = true;
    listener.cameraDevice->isCapturing(capturing);

    if (capturing) {
        listener.cameraDevice->stopCapture();
    }
    return 0;
}