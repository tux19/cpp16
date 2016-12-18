cmake_minimum_required(VERSION 3.5)
project(ex6 CXX)

set(EX6
        memfun.cpp)

add_executable(ex6 ${EX6})
target_include_directories(ex6 PUBLIC "${PROJECT_SOURCE_DIR}/ex6")