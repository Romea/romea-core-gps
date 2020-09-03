catkin_add_gtest(${PROJECT_NAME}-test test.cpp)
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME} ${catkin_LIBRARIES})
