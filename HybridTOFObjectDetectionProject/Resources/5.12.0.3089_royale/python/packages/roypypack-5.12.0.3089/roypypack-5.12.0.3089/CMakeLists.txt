#******************************************************************************
# Copyright(C) 2023 pmdtechnologies ag & Infineon Technologies
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#******************************************************************************
cmake_minimum_required(VERSION 3.24)

if(APPLE)
    message("Apple platform currently not supported.")
    return()
endif()

project(${SKBUILD_PROJECT_NAME})

if("${ROYALE_BUILD_DIR}" STREQUAL "")  # Should only be set when building royale.
    set(ROYPY_SDIST_BUILD TRUE)
else()
    set(ROYPY_SDIST_BUILD FALSE)
endif()

if(ROYPY_SDIST_BUILD)
    list(APPEND CMAKE_PREFIX_PATH "${ROYALE_DIR}/lib/cmake") # Build using release install directory
    list(APPEND CMAKE_MODULE_PATH "${ROYALE_DIR}/lib/cmake") #                ''
else()
    list(APPEND CMAKE_PREFIX_PATH "${ROYALE_DIR}/cmake") # Build using development repository directory
    list(APPEND CMAKE_MODULE_PATH "${ROYALE_DIR}/cmake/Modules") #         ''
endif()

set(PACKAGE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/${SKBUILD_PROJECT_NAME}")

message("Building ${SKBUILD_PROJECT_NAME}...")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ROYPY_SDIST_BUILD)
    find_package(royale REQUIRED)
endif()

find_package(Python3 COMPONENTS Interpreter Development.Module Development.Embed NumPy
             REQUIRED)

find_package(SWIG COMPONENTS python REQUIRED)
include(${SWIG_USE_FILE})

file(DOWNLOAD https://github.com/numpy/numpy/raw/main/tools/swig/numpy.i "${PACKAGE_SRC_DIR}/numpy.i"
     STATUS DWN_RES_LIST)
list(GET DWN_RES_LIST 0 DWN_RES_CODE)
if(NOT DWN_RES_CODE EQUAL 0)
    message("Could not download numpy.i: ${DWN_RES_LIST}")
endif()

if(NOT EXISTS "${PACKAGE_SRC_DIR}/numpy.i")
    message(FATAL_ERROR "numpy.i not found! Please download numpy.i from https://github.com/numpy/numpy/tree/master/tools/swig and place it in ${PACKAGE_SRC_DIR}")
endif()
if(NOT Python3_NumPy_FOUND)
    message(FATAL_ERROR "Numpy Python package was not found!")
endif()
message(STATUS "Numpy version: ${Python3_NumPy_VERSION}")

set_source_files_properties("${PACKAGE_SRC_DIR}/roypy.i" PROPERTIES CPLUSPLUS ON)
#set_source_files_properties("${PACKAGE_SRC_DIR}/numpy.i" PROPERTIES CPLUSPLUS ON)

swig_add_library(${SKBUILD_PROJECT_NAME} LANGUAGE python
                 SOURCES "${PACKAGE_SRC_DIR}/roypy.i"
                         "${PACKAGE_SRC_DIR}/roypy.h"
                         "${PACKAGE_SRC_DIR}/PythonEventListener.hpp")

set_target_properties(${SKBUILD_PROJECT_NAME} PROPERTIES SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)
target_include_directories(${SKBUILD_PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PACKAGE_SRC_DIR}"
    "${ROYALE_DIR}/include"            # install directory
    "${ROYALE_DIR}/source/royale/inc"  # repository directory
    "${ROYALE_DIR}/source/core/inc")   #     ''

if(ROYPY_SDIST_BUILD)
    set(ROYALE_BUILD_DIR "${ROYALE_DIR}/python")
    set(ROYALE_LIB_DIR ${ROYALE_BUILD_DIR})
else()
    if(WIN32)
        set(ROYALE_LIB_DIR "${ROYALE_BUILD_DIR}/lib/Release")
        set(ROYALE_BUILD_DIR "${ROYALE_BUILD_DIR}/Release")
    else()
        set(ROYALE_LIB_DIR "${ROYALE_BUILD_DIR}/bin")
    endif(WIN32)
endif(ROYPY_SDIST_BUILD)

target_link_directories(${SKBUILD_PROJECT_NAME} PRIVATE
    "${ROYALE_DIR}/lib"
    "${ROYALE_BUILD_DIR}"  # CMake binary directory
    "${ROYALE_LIB_DIR}")   #         ''

# If we don't have the debug library link against the release
if(NOT PYTHON_DEBUG_LIBRARIES AND MSVC)
    target_compile_definitions(${SKBUILD_PROJECT_NAME} PRIVATE
                               )
endif()

set_target_properties(${SKBUILD_PROJECT_NAME}
    PROPERTIES
    FOLDER ${PACKAGE_SRC_DIR}
    DEBUG_POSTFIX ""
    SWIG_COMPILE_DEFINITIONS ROYALE_ACTIVATE_NUMPY
)

set_property(TARGET ${SKBUILD_PROJECT_NAME}
             APPEND PROPERTY SWIG_GENERATED_COMPILE_DEFINITIONS ROYALE_ACTIVATE_NUMPY)

target_compile_definitions(${SKBUILD_PROJECT_NAME} INTERFACE ROYALE_ACTIVATE_NUMPY)

if (WIN32)
    target_link_libraries(${SKBUILD_PROJECT_NAME} PRIVATE "royale" Python3::Python Python3::NumPy)
else()
    target_link_libraries (${SKBUILD_PROJECT_NAME} PRIVATE royale Python3::Python Python3::NumPy)
endif()

add_custom_command(TARGET ${SKBUILD_PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E rm "${PACKAGE_SRC_DIR}/numpy.i")

install(TARGETS ${SKBUILD_PROJECT_NAME} DESTINATION ./${SKBUILD_PROJECT_NAME})

if(WIN32)
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/roypy.py"
            "${ROYALE_BUILD_DIR}/royale.dll"
            "${ROYALE_BUILD_DIR}/spectre.dll"
            DESTINATION ./${SKBUILD_PROJECT_NAME})
else()  # Expected to be Linux only
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/roypy.py"
            "${ROYALE_LIB_DIR}/libroyale.so"
            "${ROYALE_LIB_DIR}/libroyale.so.5.12.0"
            "${ROYALE_LIB_DIR}/libspectre.so"
            DESTINATION ./${SKBUILD_PROJECT_NAME})
endif()
