cmake_minimum_required(VERSION 3.9)
project(learning_opencv)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(learning_opencv src/Chapter6/perspectiveTransform.cpp)
target_link_libraries( learning_opencv ${OpenCV_LIBS} )