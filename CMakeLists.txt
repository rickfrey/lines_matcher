cmake_minimum_required(VERSION 2.8.3)
project(lines_matcher)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(lines_matcher src/lines_matcher.cpp)

target_link_libraries(lines_matcher ${OpenCV_LIBRARIES})
