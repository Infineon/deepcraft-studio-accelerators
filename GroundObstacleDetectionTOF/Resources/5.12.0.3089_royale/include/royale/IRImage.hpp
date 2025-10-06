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
 *  Infrared image with 8Bit mono information for every pixel.
 *  The resulting image will be lens distorted. To remove the distortion
 *  one can use the lens parameters from the camera.
 */
struct IRImage {
    int64_t timestamp; //!< timestamp for the frame
    StreamId streamId; //!< stream which produced the data
    uint16_t width;    //!< width of depth image
    uint16_t height;   //!< height of depth image
    uint8_t *data;     //!< 8Bit mono IR image

    friend void copyIRImage(IRImage &dst, const IRImage &src) {
        dst.timestamp = src.timestamp;
        dst.streamId = src.streamId;
        dst.width = src.width;
        dst.height = src.height;

        const auto numPixels = dst.width * dst.height;

        if (numPixels && src.data) {
            dst.irCopy.resize(numPixels);
            memcpy(&dst.irCopy[0], &src.data[0], numPixels * sizeof(uint8_t));
            dst.data = &dst.irCopy[0];
        }

        dst.isCopy = true;
    }

    IRImage() : timestamp(0),
                streamId(0u),
                width(0u),
                height(0u),
                data(nullptr),
                isCopy(false) {
    }

    IRImage(const IRImage &dd) {
        copyIRImage(*this, dd);
    }

    IRImage &operator=(const IRImage &dd) {
        if (this != &dd) {

            copyIRImage(*this, dd);
        }

        return *this;
    }

    uint8_t getIR(size_t idx) const {
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
    royale::Vector<uint8_t> irCopy;
    bool isCopy;
};

} // namespace royale
