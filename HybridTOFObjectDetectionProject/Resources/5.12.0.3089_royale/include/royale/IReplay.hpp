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
#include <royale/IPlaybackStopListener.hpp>
#include <royale/Status.hpp>

namespace royale {
/**
 * Class that can be used to get more control over the playback
 * of a recording. To access the interface the ICameraDevice has
 * to be casted to an IReplay object.
 *\example sampleIReplay.cpp
 */

class IReplay {
  public:
    virtual ~IReplay();

    /**
     * Seek to a different frame inside the recording.
     * @param frameNumber frame which will be read next
     */
    virtual royale::CameraStatus seek(const uint32_t frameNumber) = 0;

    /**
     * Enable/Disable looping of the playback.
     * @param restart Enable/Disable looping
     */
    virtual void loop(const bool restart) = 0;

    /**
     * If enabled, the playback will respect the timestamps and will pause accordingly.
     * @param timestampsUsed Use timestamps
     */
    virtual void useTimestamps(const bool timestampsUsed) = 0;

    /**
     * Retrieves the number of frames in the recording.
     */
    virtual uint32_t frameCount() = 0;

    /**
     * Retrieves the current frame in the recording.
     */
    virtual uint32_t currentFrame() = 0;

    /**
     * Pauses the current playback.
     */
    virtual void pause() = 0;

    /**
     * Resumes the current playback.
     */
    virtual void resume() = 0;

    /**
     *  Once registering the playback stop listener it will be called when the playback is stopped.
     *
     *  \param listener interface which needs to implement the callback method
     */
    virtual void registerStopListener(royale::IPlaybackStopListener *listener) = 0;

    /**
     *  Unregisters the playback stop listener
     */
    virtual void unregisterStopListener() = 0;

    /**
     *  Retrieves the version of the file that was opened
     */
    virtual uint16_t getFileVersion() = 0;

    /**
     *  Retrieves the build of royale that created this file
     */
    virtual uint32_t getMajorVersion() = 0;

    /**
     *  Retrieves the build of royale that created this file
     */
    virtual uint32_t getMinorVersion() = 0;

    /**
     *  Retrieves the build of royale that created this file
     */
    virtual uint32_t getPatchVersion() = 0;

    /**
     *  Retrieves the build of royale that created this file
     */
    virtual uint32_t getBuildVersion() = 0;

    /**
     *  Sets the playback range
     */
    virtual royale::CameraStatus setPlaybackRange(uint32_t first, uint32_t last) = 0;

    /**
     *  Retrieves the playback range
     */
    virtual void getPlaybackRange(uint32_t &first, uint32_t &last) = 0;
};
} // namespace royale
