cmake_minimum_required(VERSION 3.5)
project(ex1)

set(EX1 main.cpp
        fraction.h
        fraction.cpp
        test_fraction.h
        test_fraction.cpp )
add_executable(ex1 ${EX1})
target_include_directories(ex1 PUBLIC "${PROJECT_SOURCE_DIR}/ex1")
