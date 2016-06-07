add_executable(Live3dAvatar main.cpp State.cpp Demo.cpp RangeMultipleViewTracker.cpp Camera.cpp CommandLineParser.cpp Logger.cpp MultipleViewPointTracker.cpp ColorPointTracker.cpp OutputWindow.cpp util.cpp MVMOTracker.cpp MVMOTemplateTracker.cpp Markers.cpp TrackableObjInfo.cpp MOTemplateTracker.cpp MultipleViewMerger.cpp MultipleViewMerger.h)
target_link_libraries(Live3dAvatar ${OpenCV_LIBS} ${PCL_LIBRARIES} )

add_library(Camera Camera.h Camera.cpp)
