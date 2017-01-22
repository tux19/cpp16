cmake_minimum_required(VERSION 3.5)
project(ex8 CXX)

set(EX8 constdeconst.cpp
        constdeconst.h
#        connect4/my_playfield.cpp
#        connect4/playfield.h
#        connect4/connect4.h
#        connect4/my_playfield.h
#        connect4/player.h
#        connect4/rc_cpu_player.h
#        connect4/rc_cpu_player_dumb.h
#        connect4/rc_human_player.h
        main.cpp
        connect4_factory/player.h
        connect4_factory/playfield.h
        connect4_factory/my_playfield.h
        connect4_factory/my_playfield.cpp
        connect4_factory/connect4.h

        connect4_factory/player_factory.cpp
        connect4_factory/player_factory.h
        connect4_factory/rc_cpu_player.h
        connect4_factory/rc_cpu_player_dumb.h
        connect4_factory/rc_human_player.h
        connect4_factory/extern/reto_ai.h
        connect4_factory/extern/reto_ai.cpp
        connect4_factory/extern/rkoch_ai.h
        connect4_factory/extern/rkoch_ai.cpp
        )
      #[[  spellchecker.h  spellchecker.cpp)]]


add_executable(ex8 ${EX8})
target_include_directories(ex8 PUBLIC "${PROJECT_SOURCE_DIR}/ex8")