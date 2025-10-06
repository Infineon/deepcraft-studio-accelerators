cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleRetrieveData)

find_package (royale REQUIRED)

add_executable (sampleRetrieveData sampleRetrieveData.cpp)

target_include_directories (sampleRetrieveData PRIVATE ../../inc)

copy_royale_libs (sampleRetrieveData)

target_link_libraries (sampleRetrieveData royale::royale)
