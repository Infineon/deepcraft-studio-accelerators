/****************************************************************************\
* Copyright (C) 2023 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <cstdint>
#include <royale/Definitions.hpp>
#include <royale/StreamId.hpp>
#include <royale/Vector.hpp>

namespace royale {
/*!
 * Provides the listener interface for handling auto-exposure updates in royale.
 *
 * To be notified of changes to the exposure, for example to update a UI slider, an application
 * may implement this interface and register itself as a listener to the ICameraDevice.  If the
 * application merely wishes to use auto-exposure but does not need to know that the exposure
 * has changed, it is not necessary to implement this listener.
 *
 * The exposure will be changed for future captures, but there may be another capture before the
 * new values take effect.  An application that needs the values for a specific set of captured
 * frames should use the metadata provided as part of the capture callback, for example in
 * DepthData::exposureTimes.
 */
class IExposureGroupListener {
  public:
    ROYALE_API virtual ~IExposureGroupListener();

    /*!
     * Will be called after every exposure time update with the current exposure group values.
     *
     * @param exposureTimes Current exposure group values
     */
    ROYALE_API virtual void onNewExposures(const royale::Vector<uint32_t> &exposureTimes) = 0;
};
} // namespace royale
