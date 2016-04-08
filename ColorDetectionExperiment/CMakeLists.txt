cmake_minimum_required(VERSION 2.6)
project(TG1_arm_detection_color)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

find_package(OpenCV REQUIRED)

FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cpp HSVRangeTrackableObject.cpp HSVRangeTrackableObject.h Camera.cpp Camera.h CommandLineParser.cpp CommandLineParser.h Logger.h Logger.cpp PointTracker.cpp PointTracker.h ColorPointTracker.cpp ColorPointTracker.h OutputWindow.cpp OutputWindow.h Demo.cpp Demo.h)
add_executable(TG1_arm_detection_color ${SOURCE_FILES})
target_link_libraries(TG1_arm_detection_color ${OpenCV_LIBS})
