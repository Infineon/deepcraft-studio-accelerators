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

#include <common/exceptions/ResourceError.hpp>
#include <royale/IEvent.hpp>
#include <royale/IRecord.hpp>
#include <royale/String.hpp>

namespace royale {
class RecordDummy : public royale::IRecord {
  public:
    /**
     * Constructor for the RecordDummy class.
     */
    ROYALE_API RecordDummy();

    /**
     * Destructor for the CameraRecord class.
     */
    ROYALE_API virtual ~RecordDummy();

    ROYALE_API void captureCallback(std::vector<royale::common::ICapturedRawFrame *> &,
                                    const royale::usecase::UseCaseDefinition &,
                                    royale::StreamId,
                                    std::unique_ptr<const royale::collector::CapturedUseCase>) override;
    ROYALE_API void releaseAllFrames() override;

    // IRecord interface
    ROYALE_API bool isRecording() override;
    ROYALE_API void setProcessingParameters(const royale::ProcessingParameterVector &, const royale::StreamId) override;
    ROYALE_API void startRecord(const royale::String &, const std::vector<uint8_t> &,
                                const royale::String &, const royale::String &,
                                const uint32_t = 0, const uint32_t = 0, const uint32_t = 0) override;
    ROYALE_API void resetParameters() override;
    ROYALE_API void stopRecord() override;
    ROYALE_API bool setFrameCaptureListener(royale::collector::IFrameCaptureListener *) override;

    ROYALE_API void registerEventListener(royale::IEventListener *) override;
    ROYALE_API void unregisterEventListener() override;

    ROYALE_API operator bool() const override;
};
} // namespace royale
