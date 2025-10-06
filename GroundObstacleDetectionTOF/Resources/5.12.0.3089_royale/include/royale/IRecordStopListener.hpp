/****************************************************************************\
 * Copyright (C) 2015 pmdtechnologies ag
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

namespace royale {
/**
 *  This interface needs to be implemented if the client wants to get notified when recording stopped after
 *  the specified number of frames.
 */
class IRecordStopListener {
  public:
    ROYALE_API virtual ~IRecordStopListener();

    /**
     * Will be called if the recording is stopped.
     * @param numFrames Number of frames that have been recorded
     */
    ROYALE_API virtual void onRecordingStopped(const uint32_t numFrames) = 0;
};
} // namespace royale
