cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(step00)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(OpenCV REQUIRED)

find_package(PCL 1.2 REQUIRED COMPONENTS common visualization)


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(srx)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(util)
