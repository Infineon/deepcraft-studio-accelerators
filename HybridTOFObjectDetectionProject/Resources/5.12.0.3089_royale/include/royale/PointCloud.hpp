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
 *  The point cloud gives XYZ and confidence for every valid
 *  point.
 *  It is given as an array of packed coordinate quadruplets (x,y,z,c)
 *  as floating point values. The x, y and z coordinates are in meters.
 *  The confidence (c) has a floating point value in [0.0, 1.0], where 1
 *  corresponds to full confidence.
 */
struct PointCloud {
    int64_t timestamp; //!< timestamp for the frame
    StreamId streamId; //!< stream which produced the data
    uint16_t width;    //!< width of depth image
    uint16_t height;   //!< height of depth image
    float *xyzcPoints; //!< XYZ and confidence for every valid point

    friend void copyPointCloud(PointCloud &dst, const PointCloud &src) {
        dst.timestamp = src.timestamp;
        dst.streamId = src.streamId;
        dst.width = src.width;
        dst.height = src.height;

        const auto numPixels = dst.width * dst.height;

        if (numPixels && src.xyzcPoints) {
            dst.pcCopy.resize(numPixels);
            memcpy(&dst.pcCopy[0], &src.xyzcPoints[0], numPixels * sizeof(uint16_t));
            dst.xyzcPoints = &dst.pcCopy[0];
        }

        dst.isCopy = true;
    }

    PointCloud() : timestamp(0),
                   streamId(0u),
                   width(0u),
                   height(0u),
                   xyzcPoints(nullptr),
                   isCopy(false) {
    }

    PointCloud(const PointCloud &dd) {
        copyPointCloud(*this, dd);
    }

    PointCloud &operator=(const PointCloud &dd) {
        if (this != &dd) {
            copyPointCloud(*this, dd);
        }

        return *this;
    }

    size_t getNumPoints() const {
        return this->width * this->height;
    }

    bool getIsCopy() const {
        return isCopy;
    }

  private:
    royale::Vector<float> pcCopy;
    bool isCopy;
};
} // namespace royale
