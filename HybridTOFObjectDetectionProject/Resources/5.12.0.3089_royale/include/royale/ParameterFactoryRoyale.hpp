/****************************************************************************\
* Copyright (C) 2023 pmdtechnologies ag & Infineon Technologies
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <factory/IProcessingParameterMapFactory.hpp>

#include <memory>

namespace royale {
namespace config {
/**
 * Returns a factory which can provide the processing parameters for every camera that is
 * included in getUsbProbeDataRoyale and which links external processing parameters by ID.
 */
ROYALE_API std::shared_ptr<royale::factory::IProcessingParameterMapFactory> getProcessingParameterMapFactoryRoyale();
} // namespace config
} // namespace royale
