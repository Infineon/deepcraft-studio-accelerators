/****************************************************************************\
 * Copyright (C) 2021 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <royale/String.hpp>

namespace royale {
/*!
 *  Royale allows to set different filter presets. Internally these represent
 *  different configurations of the processing pipeline. Which filter presets
 *  are available depends on the currently selected pipeline.
 */
enum class FilterPreset {
    Off = 0,                    ///< Turn off all filtering of the data (validation will still be enabled) (WS pipeline)
    Deprecated1 = 1,            ///< Not available anymore
    Deprecated2 = 2,            ///< Not available anymore
    Deprecated3 = 3,            ///< Not available anymore
    Deprecated4 = 4,            ///< Not available anymore
    IR1 = 5,                    ///< Only available for the IR/FaceID pipeline : IR_IlluOn-FPN
    IR2 = 6,                    ///< Only available for the IR/FaceID pipeline : IR_IlluOn-IlluOff
    AF1 = 7,                    ///< Standard setting for the auto focus pipeline
    CM1 = 8,                    ///< Standard setting for the coded modulation pipeline
    Binning_1_Basic = 9,        ///< NG pipeline : basic kernels with binning size 1
    Binning_2_Basic = 10,       ///< NG pipeline : basic kernels with binning size 2
    Binning_3_Basic = 11,       ///< NG pipeline : basic kernels with binning size 3
    Binning_4_Basic = 12,       ///< NG pipeline : basic kernels with binning size 4
    Binning_8_Basic = 13,       ///< NG pipeline : basic kernels with binning size 8
    Binning_10_Basic = 14,      ///< NG pipeline : basic kernels with binning size 10
    Binning_1_Efficiency = 15,  ///< NG pipeline : efficiency kernels with binning size 1
    Binning_2_Efficiency = 16,  ///< NG pipeline : efficiency kernels with binning size 2
    Binning_3_Efficiency = 17,  ///< NG pipeline : efficiency kernels with binning size 3
    Binning_4_Efficiency = 18,  ///< NG pipeline : efficiency kernels with binning size 4
    Binning_8_Efficiency = 19,  ///< NG pipeline : efficiency kernels with binning size 8
    Binning_10_Efficiency = 20, ///< NG pipeline : efficiency kernels with binning size 10
    Fast1 = 21,                 ///< FAST pipeline
    Spot1 = 22,                 ///< Spot processing
    Legacy = 200,               ///< Standard settings for older cameras (WS pipeline)
    Full = 255,                 ///< Enable all filters that are available for this camera (WS pipeline)
    Custom = 256                ///< Value returned by getFilterPreset if the processing parameters differ from all of the presets
};

ROYALE_API royale::String getFilterPresetName(royale::FilterPreset preset);

ROYALE_API royale::FilterPreset getFilterPresetFromName(royale::String name);
} // namespace royale
