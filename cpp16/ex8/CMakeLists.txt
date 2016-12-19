cmake_minimum_required(VERSION 3.5)
project(ex8 CXX)

set(EX8 constdeconst.cpp
        constdeconst.h)
      #[[  spellchecker.h
        spellchecker.cpp)]]


add_executable(ex8 ${EX8})
target_include_directories(ex8 PUBLIC "${PROJECT_SOURCE_DIR}/ex8")