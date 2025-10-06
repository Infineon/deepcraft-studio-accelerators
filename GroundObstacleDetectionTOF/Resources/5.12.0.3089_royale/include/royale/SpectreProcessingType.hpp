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

#include <royale/String.hpp>

namespace royale {
/*!
 *  This is a list of pipelines that can be set in Spectre.
 *  Which pipelines are available depends on the module and the currently selected
 *  use case.
 */
enum class SpectreProcessingType {
    AUTO = 1,
    CB_BINNED_WS = 2,
    NG = 3,
    AF = 4,
    CB_BINNED_NG = 5,
    GRAY_IMAGE = 6,
    CM_FI = 7,
    FAST = 8,
    SPOT = 9,
    CB_BINNED_FAST = 10,
    WS = 11,
    NUM_TYPES
};

/*!
 * Converts the given processing type into a readable string.
 */
ROYALE_API royale::String getSpectreProcessingTypeName(royale::SpectreProcessingType mode);

/*!
 * Converts the name of a processing type into an enum value.
 */
ROYALE_API bool getSpectreProcessingTypeFromName(const royale::String &modeName, royale::SpectreProcessingType &processingType);
} // namespace royale
