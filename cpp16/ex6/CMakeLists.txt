cmake_minimum_required(VERSION 3.5)
project(ex6 CXX)

set(EX6_1
        main_1.cpp
        pvector.h
        rpn_pvec.h
        persister.h
        memfun.h

        connect4_inh/player.h
        connect4_inh/playfield.h
        connect4_inh/connect4.h
        connect4_inh/my_playfield.h
        connect4_inh/my_playfield.cpp
        connect4_inh/rc_cpu_player_dumb.h
        connect4_inh/rc_cpu_player.h
        connect4_inh/rc_human_player.h
        connect4_inh/extern/reto_ai.h
        connect4_inh/extern/reto_ai.cpp
        connect4_inh/extern/rkoch_ai.cpp
        connect4_inh/extern/rkoch_ai.h
        connect4_inh/rc_cpu_player_inh.h

        )
set(EX6_2
        main_2.cpp
        pvector.h
        rpn_pvec.h
        persister.h
        memfun.h


        connect4_interop/player.h
        connect4_interop/playfield.h
        connect4_interop/connect4.h
        connect4_interop/my_playfield.h
        connect4_interop/my_playfield.cpp
        connect4_interop/rc_cpu_player_dumb.h
        connect4_interop/rc_cpu_player.h
        connect4_interop/rc_human_player.h
        connect4_interop/extern/reto_ai.h
        connect4_interop/extern/reto_ai.cpp
        connect4_interop/extern/rkoch_ai.cpp
        connect4_interop/extern/rkoch_ai.h
        )
add_executable(ex6_1 ${EX6_1})
add_executable(ex6_2 ${EX6_2})

target_include_directories(ex6_1 PUBLIC "${PROJECT_SOURCE_DIR}/ex6")
target_include_directories(ex6_2 PUBLIC "${PROJECT_SOURCE_DIR}/ex6")