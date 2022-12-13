cmake_minimum_required(VERSION 3.5)

project(
  "romea_core_gps"
  VERSION 0.1.0
  #  DESCRIPTION
  #  HOMEPAGE_URL
  LANGUAGES CXX)

find_package(romea_core_common REQUIRED)

add_library(${PROJECT_NAME} SHARED
      src/GPSReceiver.cpp
      src/nmea/GGAFrame.cpp
      src/nmea/RMCFrame.cpp
      src/nmea/GSVFrame.cpp
      src/nmea/GSVFrameAggregator.cpp
      src/nmea/NMEAParsing.cpp
      src/nmea/NMEAFixTime.cpp
      src/nmea/NMEAAngle.cpp
      src/nmea/NMEALatitude.cpp
      src/nmea/NMEALongitude.cpp
      src/nmea/NMEAFixDate.cpp
      src/nmea/NMEAFixQuality.cpp
      src/nmea/NMEATalker.cpp
      src/reliability/SatellitesInView.cpp
      src/reliability/HalfNormalDistribution.cpp
      src/reliability/GPSReliability.cpp
      src/reliability/SNRDistribution.cpp
  )

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  ${romea_core_common_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -O3 -std=c++17)

target_link_libraries(${PROJECT_NAME} PUBLIC
  romea_core_common::romea_core_common)

include(GNUInstallDirs)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES package.xml DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

option(BUILD_TESTING "BUILD WITH TESTS" ON)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif(BUILD_TESTING)
