cmake_minimum_required(VERSION 3.5)
project(ex7 CXX)

set(EX7 main.cpp
        rangecheckingiterator.h
        merger.h
        limitedstack.h
        unlimitedstack.h
        )
 #[[rangecheckingiterator.h
      rangecheckingiteratordriver.cpp
        limitedstack.cpp
        limitedstack.h]]

add_executable(ex7 ${EX7})
target_include_directories(ex7 PUBLIC "${PROJECT_SOURCE_DIR}/ex7")