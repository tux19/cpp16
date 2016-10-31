cmake_minimum_required(VERSION 3.5)
project(ex3 CXX)

set(EX3 main.cpp
        playfield.h)

add_executable(ex3 ${EX3})
target_include_directories(ex3 PUBLIC "${PROJECT_SOURCE_DIR}/ex3")