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

#include <royale/SpectreProcessingType.hpp>
#include <royale/String.hpp>
#include <royale/Variant.hpp>
#include <royale/Vector.hpp>

namespace royale {
/*!
 *  These are some of the flags which can be set/altered in access LEVEL 2 in order
 *  to control the processing pipeline. For a complete list please refer to the documentation
 *  you will receive after getting LEVEL 2 access.
 *
 *  Make sure to retrieve and update all the flags when SpectreProcessingType_Int is altered.
 *
 *  consistencyTolerance                      < Consistency limit for asymmetry validation
 *  flyingPixelF0                             < Scaling factor for lower depth value normalization
 *  flyingPixelF1                             < Scaling factor for upper depth value normalization
 *  flyingPixelFarDist                        < Upper normalized threshold value for flying pixel detection
 *  flyingPixelNearDist                       < Lower normalized threshold value for flying pixel detection
 *  saturationThresholdLower                  < Lower limit for valid raw data values
 *  saturationThresholdUpper                  < Upper limit for valid raw data values
 *  mpiAmplitudeThreshold                     < Threshold for MPI flags triggered by amplitude discrepancy
 *  mpiDistanceThreshold                      < Threshold for MPI flags triggered by distance discrepancy
 *  mpiNoiseDistance                          < Threshold for MPI flags triggered by noise
 *  noiseThreshold                            < Upper threshold for final distance noise
 *  adaptiveNoiseFilterType                   < Kernel type of the adaptive noise filter
 *  useAdaptiveNoiseFilter                    < Activate spatial filter reducing the distance noise
 *  useRemoveFlyingPixel                      < Activate FlyingPixel flag
 *  useMPIFlagAverage                         < Activate spatial averaging MPI value before thresholding
 *  useMPIFlagAmplitude                       < Activates MPI-amplitude flag
 *  useMPIFlagDistance                        < Activates MPI-distance flag
 *  useValidateImage                          < Activates output image validation
 *  useRemoveStrayLight                       < Activates the removal of stray light
 *  useFilter2Freq                            < Activates 2 frequency filtering
 *  globalBinning                             < Sets the size of the global binning kernel
 *  autoExposureSetValue                      < The reference value for the new exposure estimate
 *  useSmoothingFilter                        < Enable/Disable the smoothing filter
 *  smoothingAlpha                            < The alpha value used for the smoothing filter
 *  smoothingFilterType                       < Determines the type of smoothing that is used
 *  useFlagSBI                                < Enable/Disable the flagging of pixels where the SBI was active
 *  useFillHoles                              < Enable/Disable the hole filling algorithm
 *  exposureLimitLower                        < Lowest exposure value which will be proposed by the auto exposure algorithm
 *  exposureNormLimitUpper                    < Highest exposure value in a normal case which will be proposed by the auto exposure algorithm
 *  exposureHighLimitUpper                    < Highest exposure value for high exposed frames which will be proposed for HDR
 *  spectreProcessingType                     < The type of processing used by Spectre
 *  useGrayImageFallBackAsAmplitude           < Uses the fallback image in the gray image pipeline as amplitude image
 *  grayImageMeanMap                          < Value where the mean of the gray image is mapped to
 *  noiseFilterSigmaD                         < SigmaD
 *  noiseFilterIterations                     < Iterations of the noise filter
 *  flyPixAngleLimit                          < Angle limit of the flying pixel algorithm
 *  flyPixAmpThreshold                        < Amplitude threshold of the flying pixel algorithm
 *  flyPixNeighborsMin                        < Minimum neighbors for the flying pixel algorithm
 *  flyPixNeighborsMax                        < Maximum neighbors for the flying pixel algorithm
 *  flyPixNoiseRatioThresh                    < Noiseratio threshold
 *  smoothingResetThreshold                   < Reset value for the smoothing
 *  ccThresh                                  < Connected components threshold
 *  phaseNoiseThreshold                       < PhaseNoise threshold
 *  strayLightThreshold                       < Straylight threshold
 *  noiseFilterSigmaA                         < SigmaA
 *  twoFreqCombinationType                    < Determines which algorithm will be used for combining the two frequencies
 *  useCorrectMPI                             < Turn on/off the MPI correction of the spot processing algorithm
 *  amplitudeThreshold                        < Threshold to mark invalid pixels based on the amplitude
 *  useDotReProject                           < Reproject the dots from the spot processing
 *  useMinimalPipeline                        < Turn on/off the minimal variant of the fast pipeline
 *  spotSearchMinSNR                          < Minimum SNR to detect a Spot during the search stage
 *  wrappingThreshold                         < Controls how sensitive the detection of unambiguity range wrap around is
 */

/*!
 * For debugging, printable strings corresponding to the ProcessingFlag enumeration. The
 * returned value is copy of the processing flag name. If the processing flag is not found
 * an empty string will be returned.
 *
 * These strings will not be localized.
 */
ROYALE_API royale::String getProcessingFlagName(uint32_t procFlag);

/*!
 * Convert a string received from getProcessingFlagName back into its ProcessingFlag.
 * If the processing flag name is not found the method returns false,
 * else the method will return true.
 */
ROYALE_API bool parseProcessingFlagName(const royale::String &modeName, uint32_t &processingFlag);

/*!
 * Returns the type of a given parameter
 * If the processing flag name is not found the method returns false,
 * else the method will return true.
 */

ROYALE_API bool getProcessingFlagType(const royale::String &name, royale::VariantType &flagType);

/*!
 *  This is a map combining a set of flags which can be set/altered in access LEVEL 2 and the set value as Variant type.
 *  The proposed minimum and maximum limits are recommendations for reasonable results. Values beyond these boundaries are
 *  permitted, but are currently neither evaluated nor verified.
 */
typedef royale::Vector<royale::Pair<royale::String, royale::Variant>> ProcessingParameterVector;
typedef std::map<royale::String, royale::Variant> ProcessingParameterMap;
typedef std::pair<royale::String, royale::Variant> ProcessingParameterPair;

/*!
 * Converts a parameter map with legacy ProcessingFlag names to their Spectre counterparts.
 */
ROYALE_API royale::ProcessingParameterMap convertLegacyRoyaleParameters(const royale::ProcessingParameterMap &map);

#ifndef SWIG

/**
 * Takes ProcessingParameterMaps a and b and returns a combination of both.
 * Keys that exist in both maps will take the value of map b.
 */
ROYALE_API ProcessingParameterMap combineProcessingMaps(const ProcessingParameterMap &a,
                                                        const ProcessingParameterMap &b);

namespace parameter {
static const int spectreProcessingTypeMax = static_cast<int>(royale::SpectreProcessingType::NUM_TYPES) - 1;
} // namespace parameter
#endif
} // namespace royale
