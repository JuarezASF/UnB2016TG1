cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(TG1_marker_detection)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(OpenCV REQUIRED)

add_executable(TG1_marker_detection main.cpp Camera.cpp Camera.h Markers.cpp Markers.h)
target_link_libraries(TG1_marker_detection ${OpenCV_LIBS})