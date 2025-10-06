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
#include <cstring>
#include <memory>
#include <royale/Definitions.hpp>
#include <royale/StreamId.hpp>
#include <royale/Vector.hpp>

namespace royale {
/**
 *  Deprecated. For newer Royale versions please use the coordinates or amplitudes array pointers!
 *
 *  Encapsulates a 3D point in object space, with coordinates in meters.
 *  In addition to the X/Y/Z coordinate each point also includes a gray value, a noise standard deviation, and a
 *  depth confidence value.
 */
struct DepthPoint {
    float x;                 //!< X coordinate [meters]
    float y;                 //!< Y coordinate [meters]
    float z;                 //!< Z coordinate [meters]
    float noise;             //!< noise value [meters]
    uint16_t grayValue;      //!< 16-bit gray value
    uint8_t depthConfidence; //!< value from 0 (invalid) to 255 (full confidence)
};

/**
 *  This structure defines the depth data which is delivered through the callback.
 *  The data comprises a dense 3D point cloud with the size of the depth image (width, height).
 *  The coordinates pointer gives you an array (row-based) with the size of (width x height x 4).
 *  For each pixel it will give you x, y and z (in meters) plus the confidence (in the range 0 (bad) to 1 (good)).
 *  Based on this confidence the user can decide to use the 3D point or not.
 *  The point cloud uses a right handed coordinate system (x -> right, y -> down, z -> in viewing direction)
 *  and the points are already undistorted. The amplitudes will give you the amplitude for each
 *  pixel and the resulting image will still have lens distortion.
 *  To remove the distortion one can use the lens parameters from the camera.
 */
struct DepthData {
    std::chrono::microseconds timeStamp;    //!< timestamp in microseconds precision (time since epoch 1970)
    StreamId streamId;                      //!< stream which produced the data
    uint16_t width;                         //!< width of depth image
    uint16_t height;                        //!< height of depth image
    royale::Vector<uint32_t> exposureTimes; //!< exposureTimes retrieved from CapturedUseCase
    bool hasDepth;                          //!< to check presence of depth information
    float illuminationTemperature;          //!< temperature of illumination

    float *coordinates;   //!< coordinates array with x, y, z and confidence for every pixel
    bool hasAmplitudes;   //!< to check presence of amplitude information
    uint16_t *amplitudes; //!< amplitude value for each pixel

    friend void copyDepthData(DepthData &dst, const DepthData &src) {
        dst.timeStamp = src.timeStamp;
        dst.streamId = src.streamId;
        dst.width = src.width;
        dst.height = src.height;
        dst.hasDepth = src.hasDepth;
        dst.illuminationTemperature = src.illuminationTemperature;
        dst.hasAmplitudes = src.hasAmplitudes;

        dst.exposureTimes.resize(src.exposureTimes.size());
        memcpy(&dst.exposureTimes[0], &src.exposureTimes[0], src.exposureTimes.size() * sizeof(uint32_t));

        const auto numPixels = dst.width * dst.height;

        if (src.hasDepth && numPixels) {
            dst.coordinatesCopy.resize(4 * numPixels);
            memcpy(&dst.coordinatesCopy[0], &src.coordinates[0], 4 * numPixels * sizeof(float));
            dst.coordinates = &dst.coordinatesCopy[0];
        }

        if (src.hasAmplitudes && numPixels) {
            dst.amplitudesCopy.resize(numPixels);
            memcpy(&dst.amplitudesCopy[0], &src.amplitudes[0], numPixels * sizeof(uint16_t));
            dst.amplitudes = &dst.amplitudesCopy[0];
        }

        dst.isCopy = true;
    }

    DepthData() : timeStamp(0),
                  streamId(0u),
                  width(0u),
                  height(0u),
                  hasDepth(false),
                  illuminationTemperature(0.0f),
                  coordinates(nullptr),
                  hasAmplitudes(false),
                  amplitudes(nullptr),
                  isCopy(false) {
    }

    DepthData(const DepthData &dd) {
        copyDepthData(*this, dd);
    }

    DepthData &operator=(const DepthData &dd) {
        if (&dd != this) {
            copyDepthData(*this, dd);
        }

        return *this;
    }

    /**
     *  Returns the maximal height supported by the camera device.
     */
    royale::DepthPoint getLegacyPoint(size_t idx) const {
        royale::DepthPoint point;

        if (hasDepth) {
            point.x = this->coordinates[idx * 4 + 0];
            point.y = this->coordinates[idx * 4 + 1];
            point.z = this->coordinates[idx * 4 + 2];
            point.depthConfidence = this->coordinates[idx * 4 + 3] < 1.0f ? static_cast<uint8_t>(this->coordinates[idx * 4 + 3] * 255.0f) : 255;
        } else {
            point.x = 0.0f;
            point.y = 0.0f;
            point.z = 0.0f;
            point.depthConfidence = 0;
        }

        if (hasAmplitudes) {
            point.grayValue = this->amplitudes[idx];
        } else {
            point.grayValue = 0u;
        }
        point.noise = 0.0f; // not supported anymore

        return point;
    }

    royale::Vector<royale::DepthPoint> getLegacyPoints() const {
        royale::Vector<royale::DepthPoint> points;

        uint32_t numPixels = this->height * this->width;
        points.resize(numPixels);

        DepthPoint *targetPoint = &points[0];
        for (auto i = 0u; i < numPixels; ++i, ++targetPoint) {
            *targetPoint = getLegacyPoint(i);
        }
        return points;
    }

    float getX(size_t idx) const {
        return this->coordinates[idx * 4 + 0];
    }

    float getY(size_t idx) const {
        return this->coordinates[idx * 4 + 1];
    }

    float getZ(size_t idx) const {
        return this->coordinates[idx * 4 + 2];
    }

    uint16_t getGrayValue(size_t idx) const {
        return this->amplitudes[idx];
    }

    float getDepthConfidence(size_t idx) const {
        return this->coordinates[idx * 4 + 3];
    }

    size_t getNumPoints() const {
        return this->width * this->height;
    }

    bool getIsCopy() const {
        return isCopy;
    }

  private:
    royale::Vector<float> coordinatesCopy;
    royale::Vector<uint16_t> amplitudesCopy;

    bool isCopy;
};
} // namespace royale
