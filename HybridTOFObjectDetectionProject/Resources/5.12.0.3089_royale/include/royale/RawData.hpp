/****************************************************************************\
 * Copyright (C) 2015 Infineon Technologies
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <royale/Definitions.hpp>
#include <royale/ModulationScheme.hpp>
#include <royale/StreamId.hpp>
#include <royale/String.hpp>
#include <royale/Vector.hpp>

namespace royale {
/**
 *  This structure defines the raw data which is delivered through the callback only
 *  exposed for access LEVEL 2.
 *  This data comprises the raw phase images coming directly from the imager.
 */
struct RawData {
    ROYALE_API explicit RawData();
    ROYALE_API explicit RawData(size_t rawVectorSize);

    std::chrono::microseconds timeStamp;                //!< timestamp in microseconds precision (time since epoch 1970)
    StreamId streamId;                                  //!< stream which produced the data
    uint16_t width;                                     //!< width of raw frame
    uint16_t height;                                    //!< height of raw frame
    royale::Vector<uint16_t> rawData;                   //!< array of raw data points
    royale::Vector<royale::String> exposureGroupNames;  //!< name of each exposure group
    royale::Vector<size_t> rawFrameCount;               //!< raw frame count of each exposure group
    royale::Vector<uint32_t> modulationFrequencies;     //!< modulation frequencies for each sequence
    royale::Vector<uint32_t> exposureTimes;             //!< integration times for each sequence
    float illuminationTemperature;                      //!< temperature of illumination
    royale::Vector<uint16_t> phaseAngles;               //!< phase angles for each raw frame
    royale::Vector<uint8_t> illuminationEnabled;        //!< status of the illumination for each raw frame (1-enabled/0-disabled)
    royale::usecase::ModulationScheme modulationScheme; //!< the modulation scheme used for this stream
    uint16_t chipLength;                                //!< The chip length used for coded modulation
    float bitShifts;                                    //!< The number of bitshifts used
    uint16_t codeLength;                                //!< The code length used for coded modulation

    // Retrieve a pointer to certain raw data
    const uint16_t *getRawData(uint32_t idx) const {
        return &rawData[idx * (width * (height + 1)) + width];
    }

    // Retrieve the pseudo data of a certain raw data frame
    const uint16_t *getPseudoData(uint32_t idx) const {
        return &rawData[idx * (width * (height + 1))];
    }

    // Retrieve the number of raw frames
    const size_t getNumberOfRawFrames() const {
        size_t num = 0u;
        for (auto curGroup : rawFrameCount) {
            num += curGroup;
        }
        return num;
    }

    // Retrieve a certain raw frame
    royale::Vector<uint16_t> getRawPhase(uint32_t idx) {
        if (idx < getNumberOfRawFrames()) {
            auto rawPtr = getRawData(idx);
            return royale::Vector<uint16_t>(rawPtr, rawPtr + width * height);
        }
        return royale::Vector<uint16_t>{};
    }

    // Retrieve a certain pseudo data lina
    royale::Vector<uint16_t> getPseudoDataFromPhase(uint32_t idx) {
        if (idx < getNumberOfRawFrames()) {
            auto rawPtr = getPseudoData(idx);
            return royale::Vector<uint16_t>(rawPtr, rawPtr + width);
        }
        return royale::Vector<uint16_t>{};
    }
};

} // namespace royale
