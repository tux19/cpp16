cmake_minimum_required(VERSION 3.5)
project(ex6 CXX)

set(EX6
        main.cpp
        pvector.h
        rpn_pvec.h
        persister.h

        connect4_inh/player.h
        connect4_inh/playfield.h
        connect4_inh/connect4.h
        connect4_inh/my_playfield.h
        connect4_inh/my_playfield.cpp
        connect4_inh/rc_ai_dumb_player.h
        connect4_inh/rc_human_player.h
        connect4_inh/extern/reto_ai.h connect4_inh/extern/reto_ai.cpp connect4_inh/extern/rkoch_ai.cpp connect4_inh/extern/rkoch_ai.h)

add_executable(ex6 ${EX6})
target_include_directories(ex6 PUBLIC "${PROJECT_SOURCE_DIR}/ex6")