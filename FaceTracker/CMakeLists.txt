# I just guess 2.7 will be enough. I'm using the basic of the basic of cmake
cmake_minimum_required(VERSION 2.7)
project(FaceTracker)

# c++ 11 for 'auto' keyword
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/home/jasf/Programas/opencv2/include)
include_directories(/home/jasf/Documents/Downloads/face-analysis-sdk-master/src)
include_directories(/home/jasf/Documents/Downloads/face-analysis-sdk-master/build/src)


# path to your build/lib dir instalation of CSIRU face analysis sdk here:
set(FACE_ANALYSIS_LIB /home/jasf/Documents/Downloads/face-analysis-sdk-master/build/lib)
# path to your opencv 2.4.13 intalation lib dir here
set(OPENCV24_LIB /home/jasf/Programas/opencv2/lib)

set(SOURCE_FILES main.cpp)
add_executable(FaceTracker ${SOURCE_FILES})
# link everything we need from CSIRO libs and opencv 2.4.13 libs
target_link_libraries(FaceTracker ${FACE_ANALYSIS_LIB}/libutilities.so ${FACE_ANALYSIS_LIB}/libclmTracker.so ${FACE_ANALYSIS_LIB}/libavatarAnim.so ${OPENCV24_LIB}/libopencv_core.so ${OPENCV24_LIB}/libopencv_highgui.so ${OPENCV24_LIB}/libopencv_imgproc.so ${OPENCV24_LIB}/libopencv_objdetect.so)


