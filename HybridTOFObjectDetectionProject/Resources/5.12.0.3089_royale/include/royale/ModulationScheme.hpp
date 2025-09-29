/****************************************************************************\
* Copyright (C) 2023 pmdtechnologies ag
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
namespace usecase {

enum class ModulationScheme {
    MODULATION_SCHEME_CW = 0,
    MODULATION_SCHEME_CW_HC = 1,
    MODULATION_SCHEME_CM_MLS2 = 2,
    MODULATION_SCHEME_CM_MLSB = 3,
    MODULATION_SCHEME_CM_MLSK = 4,
    MODULATION_SCHEME_CM_MLSG = 5,
    MODULATION_SCHEME_NONE = 6,
    MODULATION_SCHEME_CW_DOT = 7,
    /// No modulation
    MODULATION_SCHEME_NONE_LEGACY = 99,

    /// first stream spot illumination, second stream flood illumination
    MODULATION_SCHEME_SPOT_HYBRID1 = 253,
    /// first stream flood illumination, second stream spot illumination
    MODULATION_SCHEME_SPOT_HYBRID2 = 254,
};

ROYALE_API royale::String getModulationSchemeString(const ModulationScheme scheme);

} // namespace usecase
} // namespace royale
