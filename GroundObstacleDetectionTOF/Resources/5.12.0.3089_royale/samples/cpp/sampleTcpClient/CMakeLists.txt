cmake_minimum_required (VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")

project (sampleTcpClient)

find_package (royale REQUIRED)

add_executable (sampleTcpClient sampleTcpClient.cpp)

target_include_directories (sampleTcpClient PRIVATE ../../inc)

copy_royale_libs (sampleTcpClient)

target_link_libraries (sampleTcpClient royale::royale)
