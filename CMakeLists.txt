cmake_minimum_required(VERSION 2.8.3)
project(lines_matcher)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

#QT4_WRAP_UI(UISrcs )
#QT4_WRAP_CPP(MOCSrcs MyWidget.h)

add_executable(lines_matcher src/lines_matcher.cpp src/bildinfo.cpp)

target_link_libraries(lines_matcher ${QT_LIBRARIES})
#target_link_libraries(lines_matcher ${OpenCV_LIBRARIES} ${QT_LIBRARIES})
