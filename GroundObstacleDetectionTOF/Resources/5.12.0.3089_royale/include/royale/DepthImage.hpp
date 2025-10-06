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
#include <memory>
#include <royale/Definitions.hpp>
#include <royale/StreamId.hpp>
#include <royale/Vector.hpp>

namespace royale {
/**
 *  The DepthImage represents the depth and confidence for every pixel.
 *  The least significant 13 bits are the depth (z value along the optical axis) in
 *  millimeters. 0 stands for invalid measurement / no data.
 *
 *  The most significant 3 bits correspond to a confidence value. 0 is the highest confidence, 7
 *  the second highest, and 1 the lowest.
 *
 *  Exception Note: For use-cases with UR larger than 8.191 m all 16 bits are used and no
 *  confidence information is available.
 *
 *  As the DepthImage only contains z but no x and y information the resulting
 *  image will have lens distortion.
 *  To remove the distortion one can use the lens parameters from the camera.
 */
struct DepthImage {
    int64_t timestamp;  //!< timestamp for the frame
    StreamId streamId;  //!< stream which produced the data
    uint16_t width;     //!< width of depth image
    uint16_t height;    //!< height of depth image
    uint16_t *data;     //!< depth and confidence for the pixel
    bool hasConfidence; //!< to check presence of confidence information

    friend void copyDepthImage(DepthImage &dst, const DepthImage &src) {
        dst.timestamp = src.timestamp;
        dst.streamId = src.streamId;
        dst.width = src.width;
        dst.height = src.height;
        dst.hasConfidence = src.hasConfidence;
        const auto numPixels = dst.width * dst.height;

        if (numPixels && src.data) {
            dst.depthCopy.resize(numPixels);
            memcpy(&dst.depthCopy[0], &src.data[0], numPixels * sizeof(uint16_t));
            dst.data = &dst.depthCopy[0];
        }

        dst.isCopy = true;
    }

    DepthImage() : timestamp(0),
                   streamId(0u),
                   width(0u),
                   height(0u),
                   data(nullptr),
                   hasConfidence(false),
                   isCopy(false) {
    }

    DepthImage(const DepthImage &dd) {
        copyDepthImage(*this, dd);
    }

    DepthImage &operator=(const DepthImage &dd) {
        if (this != &dd) {

            copyDepthImage(*this, dd);
        }

        return *this;
    }

    uint16_t getDepth(size_t idx) const {
        if (this->data) {
            return this->data[idx];
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
    royale::Vector<uint16_t> depthCopy;
    bool isCopy;
};
} // namespace royale
