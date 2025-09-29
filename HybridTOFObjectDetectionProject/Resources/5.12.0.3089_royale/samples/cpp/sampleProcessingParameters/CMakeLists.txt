cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleProcessingParameters)

find_package (royale REQUIRED)

add_executable (sampleProcessingParameters sampleProcessingParameters.cpp)

target_include_directories (sampleProcessingParameters PRIVATE ../../inc)

copy_royale_libs (sampleProcessingParameters)

target_link_libraries (sampleProcessingParameters royale::royale)
