cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleMultiCamera)

find_package (royale REQUIRED)

add_executable (sampleMultiCamera sampleMultiCamera.cpp)

target_include_directories (sampleMultiCamera PRIVATE ../../inc)

copy_royale_libs (sampleMultiCamera)

target_link_libraries (sampleMultiCamera royale::royale)
