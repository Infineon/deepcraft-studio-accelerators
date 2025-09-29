/****************************************************************************\
 * Copyright (C) 2020 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#include <QApplication>
#include <sampleQtViewer.hpp>

// barebones Qt main that just starts the GUI
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName("pmdtechnologies ag & Infineon Technologies AG");
    app.setApplicationName("sampleQtViewer");

    SampleQtViewer sampleQtViewer;
    sampleQtViewer.show();
    return app.exec();
}
