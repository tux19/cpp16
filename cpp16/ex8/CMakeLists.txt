cmake_minimum_required(VERSION 3.5)
project(ex8_1 CXX)
project(ex8_2 CXX)

set(EX8_1 constdeconst.cpp
        constdeconst.h
        spellchecker.h
        spellchecker.cpp

        main_1.cpp
        connect4_factory/player.h
        connect4_factory/playfield.h
        connect4_factory/my_playfield.h
        connect4_factory/my_playfield.cpp
        connect4_factory/connect4.h

        connect4_factory/player_factory.h
        connect4_factory/rc_cpu_player.h
        connect4_factory/rc_cpu_player_dumb.h
        connect4_factory/rc_human_player.h
        connect4_factory/extern/reto_ai.h
        connect4_factory/extern/reto_ai.cpp
        connect4_factory/extern/rkoch_ai.h
        connect4_factory/extern/rkoch_ai.cpp
        )

set(EX8_2 constdeconst.cpp
        constdeconst.h
        spellchecker.h
        spellchecker.cpp

        main_2.cpp
        connect4_thread/player.h
        connect4_thread/playfield.h
        connect4_thread/my_playfield.h
        connect4_thread/my_playfield.cpp
        connect4_thread/connect4.h
        connect4_thread/player_factory.h

        connect4_thread/rc_cpu_player.h
        connect4_thread/rc_cpu_player_dumb.h
        connect4_thread/rc_human_player.h
        connect4_thread/extern/reto_ai.h
        connect4_thread/extern/reto_ai.cpp
        connect4_thread/extern/rkoch_ai.h
        connect4_thread/extern/rkoch_ai.cpp
        connect4_thread/cpu_playfield.h)
      #[[  spellchecker.h  spellchecker.cpp)]]

include_directories(${Boost_INCLUDE_DIRS})

add_executable(ex8_2 ${EX8_2})
add_executable(ex8_1 ${EX8_1})


target_include_directories(ex8_1 PUBLIC "${PROJECT_SOURCE_DIR}/ex8")
target_include_directories(ex8_2 PUBLIC "${PROJECT_SOURCE_DIR}/ex8")
target_link_libraries(ex8_2 ${Boost_LIBRARIES})
