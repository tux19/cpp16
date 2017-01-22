cmake_minimum_required(VERSION 3.5)
project(ex5 CXX)

set(EX5 main.cpp dumb_pointer.h smart_pointer.h smart_pointer_store.h Object.h)


add_executable(ex5 ${EX5})
target_include_directories(ex5 PUBLIC "${PROJECT_SOURCE_DIR}/ex5")