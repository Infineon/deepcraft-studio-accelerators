cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleEventListener)

find_package (royale REQUIRED)

add_executable (sampleEventListener sampleEventListener.cpp)

target_include_directories (sampleEventListener PRIVATE ../../inc)

copy_royale_libs (sampleEventListener)

target_link_libraries (sampleEventListener royale::royale)
