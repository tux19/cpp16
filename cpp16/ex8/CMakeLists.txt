cmake_minimum_required(VERSION 3.5)
project(ex8 CXX)

set(EX8
        spellchecker.h
        spellchecker.cpp)
 #[[rangecheckingiterator.h
      rangecheckingiteratordriver.cpp
        limitedstack.cpp
        limitedstack.h]]

add_executable(ex8 ${EX8})
target_include_directories(ex8 PUBLIC "${PROJECT_SOURCE_DIR}/ex8")