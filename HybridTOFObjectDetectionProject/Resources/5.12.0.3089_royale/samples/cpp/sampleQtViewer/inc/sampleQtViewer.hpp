/****************************************************************************\
 * Copyright (C) 2020 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <QtWidgets>

#include <ui_mainwindow.h>

#include <royale.hpp>

class SampleQtViewer : public QMainWindow,
                       public Ui::SampleQtViewerWindow,
                       public royale::IDepthDataListener {
    Q_OBJECT

  public:
    SampleQtViewer();
    ~SampleQtViewer();

    void onNewData(const royale::DepthData *data) override;

  protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

  private:
    bool setUpCamera();
    void depthDataToQImage(const royale::DepthData *depthData, QImage &resultImg);

    std::unique_ptr<royale::ICameraDevice> m_cameraDevice;
    QImage m_image;
    QMutex m_dataMutex;
};
