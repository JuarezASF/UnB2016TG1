


add_executable(Live3dAvatar main.cpp State.cpp State.h Demo.cpp Demo.h RangeMultipleViewTracker.cpp RangeMultipleViewTracker.h Camera.cpp Camera.h CommandLineParser.cpp CommandLineParser.h Logger.h Logger.cpp MultipleViewPointTracker.cpp MultipleViewPointTracker.h ColorPointTracker.cpp ColorPointTracker.h OutputWindow.cpp OutputWindow.h)
target_link_libraries(Live3dAvatar ${PCL_LIBRARIES} ${OpenCV_LIBS})

add_library(MultipleViewPointTracker MultipleViewPointTracker.cpp MultipleViewPointTracker.h RangeMultipleViewTracker.h RangeMultipleViewTracker.cpp)
add_library(Camera Camera.h Camera.cpp)

