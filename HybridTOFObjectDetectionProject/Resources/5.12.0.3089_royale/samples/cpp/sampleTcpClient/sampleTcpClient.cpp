/****************************************************************************\
* Copyright (C) 2020 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#include <iostream>
#include <royale.hpp>
#include <royale/IDepthDataListener.hpp>

using namespace royale;

// make our own data listener to perform useful computation
class DepthDataListener : public IDepthDataListener {
  public:
    DepthDataListener() {}
    virtual ~DepthDataListener() {}

    // implement our own onNewData, this is required to make your own listener.
    void onNewData(const DepthData *data) {
        float avgDepth = 0.0f;
        size_t numValidPoints = 0u;

        for (size_t i = 0u; i < data->getNumPoints(); i++) {
            if (data->getZ(i) > 0.0f) {
                numValidPoints++;
                avgDepth += data->getZ(i);
            }
        }
        if (numValidPoints) {
            avgDepth /= static_cast<float>(numValidPoints); // total depth divided by number of points
            printf("Average Depth %5.2f [cm]\n", avgDepth * 100.0);
        } else {
            printf("No valid depth points\n");
        }
    }
};

int main(int, char *[]) {
    std::cout << "Starting client now ..... " << std::endl;

    // call the manager with the appropriate IP and port
    CameraManager manager;
    auto camera = manager.createCamera("127.0.0.1:5000");
    if (camera == nullptr) {
        std::cout << "Cannot create the camera device" << std::endl;
        return 1;
    }

    // initialize camera
    auto ret = camera->initialize();
    if (ret != CameraStatus::SUCCESS) {
        std::cout << "Cannot initialize the camera : " << static_cast<int>(ret) << std::endl;
        return 1;
    }

    royale::Vector<royale::String> useCases;
    ret = camera->getUseCases(useCases);
    if (ret != CameraStatus::SUCCESS) {
        std::cout << "Cannot retrieve use cases : " << static_cast<int>(ret) << std::endl;
        return 1;
    }

    // register data callback
    std::shared_ptr<DepthDataListener> listener{new DepthDataListener()};
    camera->registerDataListener(listener.get());

    // start capture mode
    ret = camera->startCapture();
    if (ret != CameraStatus::SUCCESS) {
        std::cout << "Cannot start capturing : " << static_cast<int>(ret) << std::endl;
        return 1;
    }

    // do nothing until user input, onNewData will be called by the listener in the meantime
    std::cout << "Press Enter to exit\n"
              << std::endl;
    std::cin.ignore();

    ret = camera->stopCapture();
    if (ret != CameraStatus::SUCCESS) {
        std::cout << "Cannot stop capturing" << std::endl;
        return 1;
    }

    return 0;
}
