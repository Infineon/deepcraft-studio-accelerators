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

#include <royale/DepthImage.hpp>
#include <royale/IRImage.hpp>

namespace royale {
/**
 *  This represents combination of both depth and IR image.
 *  Provides depth, confidence and IR 8Bit mono information for every pixel.
 *
 *  Exception Note: For use-cases with UR larger than 8.191 m no confidence
 *  information is available.
 *
 *  As the DepthImage only contains z but no x and y information the resulting
 *  image as well as the IR image will have lens distortion.
 */
struct DepthIRImage {
    int64_t timestamp;  //!< timestamp for the frame
    StreamId streamId;  //!< stream which produced the data
    uint16_t width;     //!< width of depth image
    uint16_t height;    //!< height of depth image
    uint16_t *dpData;   //!< depth and confidence for the pixel
    uint8_t *irData;    //!< 8Bit mono IR image
    bool hasConfidence; //!< to check presence of confidence information

    friend void copyDepthIRImage(DepthIRImage &dst, const DepthIRImage &src) {
        dst.timestamp = src.timestamp;
        dst.streamId = src.streamId;
        dst.width = src.width;
        dst.height = src.height;
        dst.hasConfidence = src.hasConfidence;
        const auto numPixels = dst.width * dst.height;

        if (numPixels && src.dpData && src.irData) {
            dst.irCopy.resize(numPixels);
            memcpy(&dst.irCopy[0], &src.irData[0], numPixels * sizeof(uint8_t));
            dst.irData = &dst.irCopy[0];

            dst.depthCopy.resize(numPixels);
            memcpy(&dst.depthCopy[0], &src.dpData[0], numPixels * sizeof(uint16_t));
            dst.dpData = &dst.depthCopy[0];
        }

        dst.isCopy = true;
    }

    DepthIRImage() : timestamp(0),
                     streamId(0u),
                     width(0u),
                     height(0u),
                     dpData(nullptr),
                     irData(nullptr),
                     hasConfidence(false),
                     isCopy(false) {
    }

    DepthIRImage(const DepthIRImage &dd) {
        copyDepthIRImage(*this, dd);
    }

    DepthIRImage &operator=(const DepthIRImage &dd) {
        if (this != &dd) {
            copyDepthIRImage(*this, dd);
        }

        return *this;
    }

    uint8_t getIR(size_t idx) const {
        if (this->irData) {
            return this->irData[idx];
        } else {
            return 0u;
        }
    }

    uint16_t getDepth(size_t idx) const {
        if (this->dpData) {
            return this->dpData[idx];
        } else {
            return 0u;
        }
    }

    size_t getNumPoints() const {
        return this->width * this->height;
    }

    bool getIsCopy() const {
        return isCopy;
    }

  private:
    royale::Vector<uint8_t> irCopy;
    royale::Vector<uint16_t> depthCopy;
    bool isCopy;
};
} // namespace royale
