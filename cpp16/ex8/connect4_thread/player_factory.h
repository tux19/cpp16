//
// Created by Christian Ott on 21.01.2017.
//

#ifndef CPP16_PLAYER_FACTORY_H
#define CPP16_PLAYER_FACTORY_H

#include <string>
#include "player.h"
//#include "connect4_factory/rc_cpu_player.h"
#include "rc_cpu_player_dumb.h"
#include "rc_human_player.h"
#include "extern/reto_ai.h"
#include "extern/rkoch_ai.h"

class player_factory {
public:
    player_factory(){};
    player *get_player(const std::string type) {
        if (type=="human") return new rc_human_player();
        else if (type=="cpu_dumb") return new rc_cpu_player_dumb();
//      else if (type=="cpu_minimax") return new rc_cpu_player_dumb();
        else if (type=="cpu_reto") return new retos_computerplayer();
        else if (type=="cpu_rkoch") return new rkoch_ai();
        else return nullptr;
    }
};


#endif //CPP16_PLAYER_FACTORY_H
