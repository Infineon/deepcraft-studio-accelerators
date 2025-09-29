#****************************************************************************
# Copyright (C) 2019 pmdtechnologies ag & Infineon Technologies
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#****************************************************************************

cmake_minimum_required (VERSION 3.16)

set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE STRING "build architectures for macOS")
project(RoyPy)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/cmake")

if(POLICY CMP0086)
    # UseSWIG honors SWIG_MODULE_NAME via -module flag
    cmake_policy(SET CMP0086 NEW)
endif()

find_package(royale REQUIRED)

find_package(SWIG REQUIRED)
if(DEFINED Python3_ROOT_DIR)
    set(Python3_FIND_STRATEGY LOCATION)
endif()
find_package(Python3 ${PYTHON_VERSION_STRING} REQUIRED
    COMPONENTS Interpreter Development
    OPTIONAL_COMPONENTS NumPy)

if (NOT SWIG_FOUND OR
    NOT Python3_Development_FOUND)
    message("SWIG not found. Python wrapper will not be built!")
    return()
endif()

include(${SWIG_USE_FILE})

set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin" CACHE STRING "" FORCE )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin" CACHE STRING "" FORCE )

#this option can be set to have faster retrieval of depth points and
#for this case, numpy.i should be included in the current directory
option(royale_USE_NUMPY_IN_ROYPY "Use numpy.i for the Python wrapper" OFF)

set_source_files_properties(roypy.i PROPERTIES
    CPLUSPLUS ON)

swig_add_library(roypy LANGUAGE python
        SOURCES roypy.i roypy.h PythonEventListener.hpp)

target_include_directories( roypy PRIVATE
    ./
    ../../include
)
# If we don't have the debug library link against the release
if(NOT PYTHON_DEBUG_LIBRARIES AND MSVC)
    target_compile_definitions(roypy
        PRIVATE
        $<$<CONFIG:Debug>:SWIG_PYTHON_INTERPRETER_NO_DEBUG>)
endif()

target_link_libraries(roypy PRIVATE royale::royale Python3::Python)

set_target_properties(roypy
    PROPERTIES
    FOLDER python
    DEBUG_POSTFIX ""
    SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set_property(TARGET roypy PROPERTY SWIG_GENERATED_COMPILE_OPTIONS -Wno-deprecated-declarations)
endif()

if (royale_USE_NUMPY_IN_ROYPY)
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/numpy.i")
        message(FATAL_ERROR "numpy.i not found! Please download numpy.i from https://github.com/numpy/numpy/tree/master/tools/swig and place it in ${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
    if (NOT Python3_NumPy_FOUND)
            MESSAGE(FATAL_ERROR "Numpy activated but Python package was not found!")
    endif()
    message(STATUS "Numpy version : ${Python3_NumPy_VERSION}")
    set_target_properties (roypy PROPERTIES SWIG_COMPILE_DEFINITIONS ROYALE_ACTIVATE_NUMPY)
    set_property( TARGET roypy
        APPEND PROPERTY SWIG_GENERATED_COMPILE_DEFINITIONS ROYALE_ACTIVATE_NUMPY)
    target_compile_definitions(roypy INTERFACE ROYALE_ACTIVATE_NUMPY)
    target_link_libraries(roypy PRIVATE Python3::NumPy)
endif ()

if (APPLE) 
   set_target_properties(roypy PROPERTIES MACOSX_RPATH TRUE)
   set_target_properties(roypy PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
   set_target_properties(roypy PROPERTIES INSTALL_RPATH "@loader_path")
elseif(UNIX)
   set_target_properties(roypy PROPERTIES INSTALL_RPATH "\$ORIGIN/")
endif()

COPY_ROYALE_LIBS(roypy)
