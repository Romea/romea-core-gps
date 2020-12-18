find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}_test test.cpp )
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test PRIVATE -std=c++17)
add_test(test ${PROJECT_NAME}_test)
