cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleCameraInfo)

find_package (royale REQUIRED)

add_executable (sampleCameraInfo sampleCameraInfo.cpp)

target_include_directories (sampleCameraInfo PRIVATE ../../inc)

copy_royale_libs (sampleCameraInfo)

target_link_libraries (sampleCameraInfo royale::royale)
