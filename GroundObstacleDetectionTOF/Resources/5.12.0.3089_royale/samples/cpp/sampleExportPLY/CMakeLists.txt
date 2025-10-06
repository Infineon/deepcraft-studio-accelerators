cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleExportPLY)

find_package (royale REQUIRED)

add_executable (sampleExportPLY sampleExportPLY.cpp)

target_include_directories (sampleExportPLY PRIVATE ../../inc)

copy_royale_libs (sampleExportPLY)

target_link_libraries (sampleExportPLY royale::royale)
