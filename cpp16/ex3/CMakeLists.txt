cmake_minimum_required(VERSION 3.5)
project(ex3 CXX)

set(EX3 main.cpp
        pvector.h
        pset.h
        connect4/rc_playfield.cpp
        connect4/playfield.h
        connect4/player.h
        connect4/connect4.h
        connect4/rc_playfield.h
        connect4/rc_ai_player.h
        connect4/rc_human_player.h
        persister.h
        pset.h
        rpn_pvec.h)

add_executable(ex3 ${EX3})
target_include_directories(ex3 PUBLIC "${PROJECT_SOURCE_DIR}/ex3")