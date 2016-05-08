cmake_minimum_required(VERSION 2.7)
project(TG1_marker_detection)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Camera.cpp Camera.h Markers.cpp Markers.h)
add_executable(TG1_marker_detection ${SOURCE_FILES})
target_link_libraries( TG1_marker_detection ${OpenCV_LIBS} )