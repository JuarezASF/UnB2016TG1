add_executable(test_hsv_range_tracker test_hsv_tracker.cpp)
target_link_libraries(test_hsv_range_tracker MultipleViewPointTracker ${OpenCV_LIBS})

add_executable(test_camera test_camera.cpp)
target_link_libraries(test_camera Camera ${OpenCV_LIBS})

add_executable(create_easy_video create_easy_video.cpp)
target_link_libraries(create_easy_video ${OpenCV_LIBS})

add_executable(color_transform color_transform.cpp)
target_link_libraries(color_transform ${OpenCV_LIBS})
