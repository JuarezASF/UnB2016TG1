cmake_minimum_required(VERSION 2.7)
project(FaceTracker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/home/jasf/Programas/opencv2/include)
include_directories(/home/jasf/Documents/Downloads/face-analysis-sdk-master/src)
include_directories(/home/jasf/Documents/Downloads/face-analysis-sdk-master/build/src)


set(FACE_ANALYSIS_LIB /home/jasf/Documents/Downloads/face-analysis-sdk-master/build/lib)
set(OPENCV24_LIB /home/jasf/Programas/opencv2/lib)
set(SOURCE_FILES main.cpp)
add_executable(FaceTracker ${SOURCE_FILES})
target_link_libraries(FaceTracker ${FACE_ANALYSIS_LIB}/libutilities.so ${FACE_ANALYSIS_LIB}/libclmTracker.so ${FACE_ANALYSIS_LIB}/libavatarAnim.so ${OPENCV24_LIB}/libopencv_core.so ${OPENCV24_LIB}/libopencv_highgui.so ${OPENCV24_LIB}/libopencv_imgproc.so ${OPENCV24_LIB}/libopencv_objdetect.so)


