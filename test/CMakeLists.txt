find_package(GTest REQUIRED)
include(romea_add_gtest)

romea_add_gtest(test_gps test.cpp LIBRARIES ${PROJECT_NAME})
