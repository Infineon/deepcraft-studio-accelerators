#****************************************************************************
# Copyright (C) 2018 pmdtechnologies ag & Infineon Technologies
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#****************************************************************************

#
# Find Numpy package
#

set (Numpy_FOUND 0)

if (NOT Python3_EXECUTABLE)
    message (STATUS "Python3_EXECUTABLE executable has to be set before this script.")
endif ()

if (CMAKE_CROSSCOMPILING)
    set (__numpy_include_path "")
    set (Numpy_VERSION "0.0.crosscompile")
else()
# Check for the numpy includes
    execute_process (
        COMMAND
            "${Python3_EXECUTABLE}" -c
            "from __future__ import print_function\ntry: import numpy; print(numpy.get_include(), end='')\nexcept:pass\n"
        OUTPUT_VARIABLE __numpy_include_path)

# And the version
    execute_process (
        COMMAND
            "${Python3_EXECUTABLE}" -c
            "from __future__ import print_function\ntry: import numpy; print(numpy.__version__, end='')\nexcept:pass\n"
        OUTPUT_VARIABLE Numpy_VERSION)
endif()

find_path (Numpy_INCLUDE_DIR numpy/arrayobject.h HINTS "${__numpy_include_path}"
    "${Python3_INCLUDE_DIRS}" NO_DEFAULT_PATH)

if ("${Numpy_VERSION}" STREQUAL "")
    set (Numpy_VERSION "0.0.0")
    set (Numpy_VERSION_MAJOR "0")
    set (Numpy_VERSION_MINOR "0")
    set (Numpy_VERSION_PATCH "0")
else ()
    string (REPLACE "." ";" NUMPY_VERSION_LIST ${Numpy_VERSION})
    list (LENGTH NUMPY_VERSION_LIST _NUM_ELEMENTS)
    if (${_NUM_ELEMENTS} GREATER "2")
        list (GET NUMPY_VERSION_LIST 0 Numpy_VERSION_MAJOR)
        list (GET NUMPY_VERSION_LIST 1 Numpy_VERSION_MINOR)
        list (GET NUMPY_VERSION_LIST 2 Numpy_VERSION_PATCH)
    endif ()
endif ()

if (ROYALE_NUMPY_INCLUDE_DIR)
    set (Numpy_INCLUDE_DIR ${Numpy_INCLUDE_DIR} CACHE STRING "Numpy include folder")
    set (Numpy_VERSION ${Numpy_VERSION} CACHE STRING "Numpy version")
    set (Numpy_VERSION_MAJOR ${Numpy_VERSION_MAJOR} CACHE STRING "Numpy major version")
    set (Numpy_VERSION_MINOR ${Numpy_VERSION_MINOR} CACHE STRING "Numpy minor version")
    set (Numpy_VERSION_PATCH ${Numpy_VERSION_PATCH} CACHE STRING "Numpy patch version")
endif (ROYALE_NUMPY_INCLUDE_DIR)

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (
    Numpy
    FOUND_VAR
    Numpy_FOUND
    REQUIRED_VARS
    Numpy_INCLUDE_DIR
    VERSION_VAR
    Numpy_VERSION)
