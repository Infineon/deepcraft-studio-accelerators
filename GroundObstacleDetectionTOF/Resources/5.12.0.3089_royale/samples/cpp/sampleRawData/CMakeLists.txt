cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleRawData)

find_package (royale REQUIRED)

add_executable (sampleRawData sampleRawData.cpp)

target_include_directories (sampleRawData PRIVATE ../../inc)

copy_royale_libs (sampleRawData)

target_link_libraries (sampleRawData royale::royale)
