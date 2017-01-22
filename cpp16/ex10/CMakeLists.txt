cmake_minimum_required(VERSION 3.5)
project(ex10 CXX)

set(EX10 main.cpp)
#[[  spellchecker.h
  spellchecker.cpp)]]


add_executable(ex10 ${EX10})
target_include_directories(ex10 PUBLIC "${PROJECT_SOURCE_DIR}/ex10")