#****************************************************************************
# Copyright (C) 2018-2023 pmdtechnologies ag & Infineon Technologies
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#****************************************************************************

option (ROYALE_DEPRECATION_WARNING "Print deprecation warnings for Royale" ON)

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component (coPath "${CMAKE_CURRENT_LIST_FILE}" PATH)

set (instPath "${coPath}/../../..")

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component (instPath "${instPath}" REALPATH)

# Provide the include directories to the caller
#set (royale_INCLUDE_DIRS "${royale_INSTALL_PATH}/include")
get_target_property(royale_INCLUDE_DIRS royale::royale INTERFACE_INCLUDE_DIRECTORIES)

set (royale_LIBS "royale::royale")
set (royale_LIBRARIES "royale::royale")
set (royale_CONFIG_PATH "${coPath}")
set (royale_INSTALL_PATH "${instPath}")
if (WIN32)
    set (royale_LIB_DIR "${instPath}/lib")
else ()
    set (royale_LIB_DIR "${instPath}/bin")
endif ()

# Mark variables as deprecated
if(ROYALE_DEPRECATION_WARNING)
    function(variable_is_deprecated var access)
        if("${access}" STREQUAL "READ_ACCESS")
            message(DEPRECATION
            "variable '${var}' is deprecated!\n"
            " Please use target royale::royale to link against libroyale\n"
            " Silence this warning with ROYALE_DEPRECATION_WARNING=OFF")
        endif()
    endfunction()

    variable_watch(royale_CONFIG_PATH variable_is_deprecated)
    variable_watch(royale_INSTALL_PATH variable_is_deprecated)
    variable_watch(royale_LIB_DIR variable_is_deprecated)
    variable_watch(royale_LIBS variable_is_deprecated)
    variable_watch(royale_LIBRARIES variable_is_deprecated)
endif()

unset(coPath)
unset(instPath)
