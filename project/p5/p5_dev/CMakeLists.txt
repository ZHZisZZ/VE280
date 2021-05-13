cmake_minimum_required(VERSION 3.15)
project(p5)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_CXX_STANDARD 14)

add_executable(rpn rpn.cpp)
add_executable(cache cache.cpp)