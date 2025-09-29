/****************************************************************************\
 * Copyright (C) 2020 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#include <sampleQtViewer.hpp>

SampleQtViewer::SampleQtViewer() {
    // required by Qt
    setupUi(this);

    if (!setUpCamera()) {
        QMessageBox::critical(this, "Sample Qt viewer", "Couldn't open a camera!");
    }
}

SampleQtViewer::~SampleQtViewer() {
    // destroying the camera device will also stop the capturing
}

bool SampleQtViewer::setUpCamera() {
    // the camera manager will query for a connected camera
    royale::CameraManager manager;

    // checks if there are cameras connected
    if (manager.getConnectedCameraList().empty()) {
        std::cout << "Could not find at least one connected Camera." << std::endl;
        return false;
    }

    // gets the first camera found
    m_cameraDevice = manager.createCamera(manager.getConnectedCameraList().first());

    // IMPORTANT: call the initialize method before working with the camera device
    auto ret = m_cameraDevice->initialize();
    if (ret != royale::CameraStatus::SUCCESS) {
        std::cout << "Camera device did not initialize: " << static_cast<int>(ret) << std::endl;
        return false;
    }

    // register data listener - will call onNewData
    ret = m_cameraDevice->registerDataListener(static_cast<IDepthDataListener *>(this));
    if (ret != royale::CameraStatus::SUCCESS) {
        std::cout << "Could not register data listener: " << static_cast<int>(ret) << std::endl;
        return false;
    }

    // start capturing
    ret = m_cameraDevice->startCapture();
    if (ret != royale::CameraStatus::SUCCESS) {
        std::cout << "Cannot start capturing: " << static_cast<int>(ret) << std::endl;
        return false;
    }

    return true;
}

// helper function that transforms depthData into a qImage
void SampleQtViewer::depthDataToQImage(const royale::DepthData *depthData, QImage &resultImg) {
    // assuming 900 is the maximum amplitude the values reach
    static const auto MAX_AMPLITUDE = 900.0f;

    // dimensions of our data
    const auto &maxWidth = depthData->width;
    const auto &maxHeight = depthData->height;

    // write data to an image
    if (depthData->width != resultImg.width() ||
        depthData->height != resultImg.height() ||
        resultImg.isNull()) {
        resultImg = QImage(depthData->width, depthData->height, QImage::Format_ARGB32);
    }

    // iterates over all the pixels
    for (int curWidth = 0; curWidth < maxWidth; curWidth++) {
        for (int curHeight = 0; curHeight < maxHeight; curHeight++) {
            // get the right point from our depth dataset
            auto dataPos = curHeight * maxWidth + curWidth;
            float curAmpl = depthData->getGrayValue(dataPos);

            // convert amplitude values to a float between 0 and 1
            auto j = 70.f;
            auto modAmplFloat = (log10f(1.0f + (j - 1.f) * curAmpl / MAX_AMPLITUDE) / log10f(j));
            if (modAmplFloat > 1.0f) {
                modAmplFloat = 1.0f;
            }

            // convert float between 0 and 1 to a value between 0 and 255 to make it RGB compliant
            modAmplFloat = modAmplFloat * 255.0f;
            auto modAmplInt = static_cast<int>(modAmplFloat);

            // sets the rgb values on the QImage pixel
            QColor qC(modAmplInt, modAmplInt, modAmplInt);
            resultImg.setPixel(curWidth, curHeight, qC.rgba());
        }
    }
}

// this function is called by the listener every time we have new data
void SampleQtViewer::onNewData(const royale::DepthData *data) {
    {
        QMutexLocker locker(&m_dataMutex);

        depthDataToQImage(data, m_image);
    }

    // we have to update the label in the GUI thread
    update();
}

void SampleQtViewer::paintEvent(QPaintEvent *) {
    QMutexLocker locker(&m_dataMutex);

    if (!m_image.isNull()) {
        // display the image on our Qt label and scale it accordingly
        imageLabel->setPixmap(QPixmap::fromImage(m_image).scaled(imageLabel->size(), Qt::KeepAspectRatio));
    }
}
