cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleIReplay)

find_package (royale REQUIRED)

add_executable (sampleIReplay sampleIReplay.cpp)

target_include_directories (sampleIReplay PRIVATE ../../inc)

copy_royale_libs (sampleIReplay)

target_link_libraries (sampleIReplay royale::royale)
