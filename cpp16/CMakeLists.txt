cmake_minimum_required(VERSION 3.5)
project(cpp16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp)
add_subdirectory(ex1)
add_subdirectory(ex2)
add_subdirectory(ex3)

