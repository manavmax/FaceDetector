cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_ARCHITECTURES arm64)
project(FaceDetector)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt auto-generation features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# OpenCV
set(OpenCV_DIR /opt/homebrew/opt/opencv/share/opencv4)
find_package(OpenCV REQUIRED)

# GStreamer
set(CMAKE_PREFIX_PATH "/opt/homebrew/")
include_directories(/opt/homebrew/include/gstreamer-1.0)
include_directories(/opt/homebrew/include/glib-2.0)
include_directories(/opt/homebrew/lib/glib-2.0/include)
link_directories(/opt/homebrew/lib)

# Sources and headers
set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(UIS
    mainwindow.ui
)

# App
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Widgets
    ${OpenCV_LIBS}
    gstapp-1.0 gstbase-1.0 gstreamer-1.0 gobject-2.0 glib-2.0
)
