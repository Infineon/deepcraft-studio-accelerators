#****************************************************************************
# Copyright (C) 2023 pmdtechnologies ag & Infineon Technologies
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#****************************************************************************

# ===================================================================================
# The Royale CMake configuration file
#
# Usage from an external project: In your CMakeLists.txt, add these lines:
#
# find_package(royale REQUIRED)
# target_link_libraries(my_target_name PRIVATE royale::royale)
# copy_royale_libs(my_target_name)
# ===================================================================================

include(CMakeFindDependencyMacro)
include("${CMAKE_CURRENT_LIST_DIR}/royaleTargets.cmake")

set (royale_VERSION_SHORT "${royale_VERSION_MAJOR}.${royale_VERSION_MINOR}.${royale_VERSION_PATCH}")

macro (copy_royale_libs copytarget)
    if (WIN32 OR APPLE)
        # Compute the installation prefix
        get_target_property(ROYALE_LOCATION_DIR royale::royale LOCATION)
        get_filename_component(ROYALE_LOCATION_DIR "${ROYALE_LOCATION_DIR}" PATH)
        get_filename_component(ROYALE_LOCATION_DIR "${ROYALE_LOCATION_DIR}" PATH)
        if(ROYALE_LOCATION_DIR STREQUAL "/")
            set(ROYALE_LOCATION_DIR "")
        endif()
    endif()

    if (WIN32)
        add_custom_command (
            TARGET ${copytarget} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${ROYALE_LOCATION_DIR}/bin/royale.dll"
                    $<TARGET_FILE_DIR:${copytarget}>)

        add_custom_command (
            TARGET ${copytarget} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${ROYALE_LOCATION_DIR}/bin/spectre.dll"
                    $<TARGET_FILE_DIR:${copytarget}>)
    endif (WIN32)

    if (APPLE)
        add_custom_command (
            TARGET ${copytarget} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${ROYALE_LOCATION_DIR}/bin/libroyale.dylib"
                    $<TARGET_FILE_DIR:${copytarget}>)

        add_custom_command (
            TARGET ${copytarget}
            POST_BUILD
            COMMAND
                ${CMAKE_COMMAND} -E copy
                "${ROYALE_LOCATION_DIR}/bin/libroyale.${royale_VERSION_SHORT}.dylib"
                $<TARGET_FILE_DIR:${copytarget}>)

        add_custom_command (
            TARGET ${copytarget} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${ROYALE_LOCATION_DIR}/bin/libspectre.dylib"
                    $<TARGET_FILE_DIR:${copytarget}>)
    endif (APPLE)
    # Cleanup variables
    set(ROYALE_LOCATION_DIR)
endmacro ()
include("${CMAKE_CURRENT_LIST_DIR}/royaleCompat.cmake")
