################################################################################
# \file Makefile
# \version 1.0
#
# \brief
# Makefile for configuring the Cortex-M55 core project
#
################################################################################
# \copyright
# (c) 2025, Infineon Technologies AG, or an affiliate of Infineon
# Technologies AG.  SPDX-License-Identifier: Apache-2.0
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

include ../common.mk

################################################################################
# Basic Configuration
################################################################################

# Name of application (used to derive name of final linked file).
#
# If APPNAME is edited, ensure to update or regenerate launch
# configurations for your IDE.
APPNAME=proj_cm55

# If set to "true" or "1", display full command-lines when building.
VERBOSE=

# Neural Network Configuration. Options include
#
# float    -- floating point for the input data and weights
# int8x8   -- 8-bit fixed-point for the input data and weights (this is supported by default)
NN_TYPE=int8x8

# Choose the inference engine
# tflm      -- TensorFlow Lite for Microcontrollers inference engine with interpreter
# Note tflm_less option is not supported currently
NN_INFERENCE_ENGINE=tflm

################################################################################
# Advanced Configuration
################################################################################

# Enable optional code that is ordinarily disabled by default.
#
# Available components depend on the specific targeted hardware and firmware
# in use. In general, if you have
#
#    COMPONENTS=foo bar
#
# ... then code in directories named COMPONENT_foo and COMPONENT_bar will be
# added to the build
#
COMPONENTS+=

# Like COMPONENTS, but disable optional code that was enabled by default.
DISABLE_COMPONENTS=

# Set this application to run at the CM55
CORE=CM55
CORE_NAME=CM55_0
NPU=U55

# By default the build system automatically looks in the Makefile's directory
# tree for source code and builds it. The SOURCES variable can be used to
# manually add source code to the build process from a location not searched
# by default, or otherwise not found by the build system.
SOURCES+=

# Like SOURCES, but for include directories. Value should be paths to
# directories (without a leading -I).
INCLUDES+=

# Add additional defines to the build process (without a leading -D).
DEFINES+=CY_RETARGET_IO_CONVERT_LF_TO_CRLF

# Add additional defines related to ARM Helium and DSP extensions
DEFINES+=ARM_MATH_HELIUM ARM_MATH_DSP ARM_MATH_AUTOVECTORIZE


ifeq (ACCELEROMETER_GYROSCOPE, $(IMU_ENABLE_SENSOR))
DEFINES+=IMU_ACC
DEFINES+=IMU_GYR
endif

ifeq (ACCELEROMETER, $(IMU_ENABLE_SENSOR))
DEFINES+=IMU_ACC
endif

ifeq (GYROSCOPE, $(IMU_ENABLE_SENSOR))
DEFINES+=IMU_GYR
endif


# Add additional components related to MTB ML
COMPONENTS+=U55

# Add additional define/components to select the inference engine
ifeq (tflm, $(NN_INFERENCE_ENGINE))
COMPONENTS+=ML_TFLM
DEFINES+=TF_LITE_STATIC_MEMORY
endif

# Add define to build code for CM55 and include additional files
ifeq (cm55, $(ML_DEEPCRAFT_CPU))
DEFINES+=ML_DEEPCRAFT_CM55
DEFINES+=CY_ML_MODEL_MEM=.cy_socmem_data
DEFINES+=CY_ML_ARENA_MEM=.cy_socmem_data
COMPONENTS+=CMSIS_DSP
endif

# Depending which Neural Network Type, add a specific DEFINE and COMPONENT
ifeq (float, $(NN_TYPE))
COMPONENTS+=ML_FLOAT32
endif
ifeq (int8x8, $(NN_TYPE))
COMPONENTS+=ML_INT8x8
endif

# Select softfp or hardfp floating point. Default is softfp.
VFP_SELECT+=hardfp

# Additional / custom C compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CFLAGS+=

# Additional / custom C++ compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CXXFLAGS+=

# Additional / custom assembler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
ASFLAGS+=

# Additional / custom linker flags.
LDFLAGS+=

# Additional / custom libraries to link in to the application.
LDLIBS+=

# Path to the linker script to use (if empty, use the default linker script).
LINKER_SCRIPT=

# Custom pre-build commands to run.
PREBUILD=

# Custom post-build commands to run.
POSTBUILD=

# Ignore the cm55 source files when CPU is cm33
ifeq ($(ML_DEEPCRAFT_CPU),cm33)
CY_IGNORE+=./model/model.c
CY_IGNORE+=./model/MICPrep.c
CY_IGNORE+=./model/IMUPrep.c
CY_IGNORE+=./audio.c
CY_IGNORE+=./imu.c
endif

################################################################################
# Paths
################################################################################

# Relative path to the project directory (default is the Makefile's directory).
#
# This controls where automatic source code discovery looks for code.
CY_APP_PATH=

# Relative path to the shared repo location.
#
# All .mtb files have the format, <URI>#<COMMIT>#<LOCATION>. If the <LOCATION> field 
# begins with $$ASSET_REPO$$, then the repo is deposited in the path specified by 
# the CY_GETLIBS_SHARED_PATH variable. The default location is one directory level 
# above the current app directory.
# This is used with CY_GETLIBS_SHARED_NAME variable, which specifies the directory name.
CY_GETLIBS_SHARED_PATH=../..

# Directory name of the shared repo location.
#
CY_GETLIBS_SHARED_NAME=mtb_shared

include $(CY_TOOLS_DIR)/make/start.mk
