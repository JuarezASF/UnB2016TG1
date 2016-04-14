cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(step00)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#FIND_PACKAGE(Boost REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(PCL 1.2 REQUIRED COMPONENTS common visualization)

find_package(OpenCV REQUIRED COMPONENTS opencv_core opencv_imgproc opencv_video opencv_videoio opencv_highgui)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


set(SOURCE_FILES HSVRangeMultipleViewTrackableObject.cpp HSVRangeMultipleViewTrackableObject.h Camera.cpp Camera.h CommandLineParser.cpp CommandLineParser.h Logger.h Logger.cpp PointTracker.cpp PointTracker.h ColorPointTracker.cpp ColorPointTracker.h OutputWindow.cpp OutputWindow.h)
add_executable(Live3dAvatar main.cpp State.cpp State.h Demo.cpp Demo.h ${SOURCE_FILES})
#target_link_libraries(Live3dAvatar ${PCL_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(Live3dAvatar ${PCL_LIBRARIES} ${OpenCV_LIBS})
