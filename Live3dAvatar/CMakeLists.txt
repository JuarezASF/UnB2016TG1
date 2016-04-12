cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(step00)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(PCL 1.2 REQUIRED)

find_package(OpenCV REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


set(SOURCE_FILES HSVRangeMultipleViewTrackableObject.cpp HSVRangeMultipleViewTrackableObject.h Camera.cpp Camera.h CommandLineParser.cpp CommandLineParser.h Logger.h Logger.cpp PointTracker.cpp PointTracker.h ColorPointTracker.cpp ColorPointTracker.h OutputWindow.cpp OutputWindow.h)
add_executable(Live3dAvatar main.cpp State.cpp State.h Demo.cpp Demo.h ${SOURCE_FILES})
target_link_libraries(Live3dAvatar ${PCL_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS})
