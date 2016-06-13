#add_executable(test_hsv_range_tracker test_hsv_tracker.cpp)
#target_link_libraries(test_hsv_range_tracker MultipleViewPointTracker ${OpenCV_LIBS})

add_executable(create_easy_video create_easy_video.cpp )
target_link_libraries(create_easy_video ${OpenCV_LIBS})

add_executable(createEasyTemplateVideo createEasyTemplateVideo.cpp)
target_link_libraries(createEasyTemplateVideo ${OpenCV_LIBS})

add_executable(generateTrackableTemplate generateTrackableTemplate.cpp)
target_link_libraries(generateTrackableTemplate ${OpenCV_LIBS})
