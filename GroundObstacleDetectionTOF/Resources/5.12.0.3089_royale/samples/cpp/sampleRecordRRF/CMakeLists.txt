cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleRecordRRF)

find_package (royale REQUIRED)

add_executable (sampleRecordRRF sampleRecordRRF.cpp)

target_include_directories (sampleRecordRRF PRIVATE ../../inc)

copy_royale_libs (sampleRecordRRF)

target_link_libraries (sampleRecordRRF royale::royale)
