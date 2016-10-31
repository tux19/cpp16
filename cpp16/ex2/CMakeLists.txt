cmake_minimum_required(VERSION 3.5)
project(ex2)

set(EX2 main.cpp
        fraction.h
        fraction.cpp
        pvector.h
        rpn.h
        rpn.cpp
        rpn_pvec.h
        rpn_pvec.cpp
        rpn_templ.h
        rpn_templ.cpp)
set(noinline inline_ex.cpp)
add_executable(ex2 ${EX2})
add_executable(noinline ${noinline})
set_target_properties(noinline PROPERTIES COMPILE_FLAGS -save-temps)

target_include_directories(ex2 PUBLIC "${PROJECT_SOURCE_DIR}/ex2")

