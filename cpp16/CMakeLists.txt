cmake_minimum_required(VERSION 3.5)
project(cpp16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(BOOST_ROOT C:/MinGW2/)

FIND_PACKAGE(Boost 1.61.0 REQUIRED thread)
include_directories(${Boost_INCLUDE_DIRS})

#set(SOURCE_FILES main.cpp)
add_subdirectory(ex1)
add_subdirectory(ex2)
add_subdirectory(ex3)
add_subdirectory(ex5)
add_subdirectory(ex6)
add_subdirectory(ex7)
add_subdirectory(ex8)
add_subdirectory(ex9)
add_subdirectory(ex10)