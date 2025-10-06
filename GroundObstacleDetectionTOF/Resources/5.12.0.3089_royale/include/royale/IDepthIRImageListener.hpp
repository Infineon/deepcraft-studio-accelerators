/****************************************************************************\
* Copyright (C) 2019 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <royale/DepthIRImage.hpp>
#include <string>

namespace royale {
/*!
 * Provides a combined listener interface for consuming both depth and IR images from Royale.
 * A listener needs to implement this interface and register itself as a listener to the ICameraDevice.
 */
class IDepthIRImageListener {
  public:
    virtual ~IDepthIRImageListener() {}

    /*!
     * Will be called on every frame update by the Royale framework
     *
     * NOTICE: Calling other framework functions within the data callback
     * can lead to undefined behavior and is therefore unsupported.
     * Call these framework functions from another thread to avoid problems.
     */
    virtual void onNewData(const royale::DepthIRImage *data) = 0;
};
} // namespace royale
