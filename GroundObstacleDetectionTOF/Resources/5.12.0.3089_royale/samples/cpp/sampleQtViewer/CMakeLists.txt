cmake_minimum_required (VERSION 3.16)

# On systems that need it, find QT based on the QTDIR environment variable
if (DEFINED ENV{QTDIR})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{QTDIR}")
else()
    message (
        "Make sure the QTDIR environment variable is set."
    )
endif ()

project (sampleQtViewer)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cmake")
# Widgets finds its own dependencies.
find_package (Qt5 COMPONENTS Widgets QUIET)

if (NOT Qt5Widgets_FOUND)
    message (
        "Qt example will not be build as no Qt was found! Please set the CMAKE_PREFIX_PATH to the lib/cmake folder inside your Qt installation"
    )
    return ()
endif ()

find_package (royale REQUIRED)

# As moc files are generated in the binary dir, tell CMake to always look for includes there:
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (MOC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/inc/sampleQtViewer.hpp")

set (UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui")

qt5_wrap_ui (UI_HEADERS ${UI_FILES})
qt5_wrap_cpp (MOCED_HEADERS ${MOC_HEADERS})

add_executable (sampleQtViewer
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sampleQtViewer.cpp"
    ${MOC_HEADERS}
    ${UI_HEADERS}
    ${MOCED_HEADERS}
)

target_include_directories (sampleQtViewer PRIVATE
    ../../inc
    inc
)

set_target_properties (sampleQtViewer PROPERTIES WIN32_EXECUTABLE ON)

target_link_libraries (sampleQtViewer royale::royale Qt5::Widgets)

copy_royale_libs (sampleQtViewer)
