#ifndef CPP16_RC_INH_AI_PLAYER_H
#define CPP16_RC_INH_AI_PLAYER_H

#include "rc_cpu_player.h"
#include "rc_cpu_player_dumb.h"
#include "playfield.h"
#include "player.h"

class rc_cpu_player_inh : public player{
    rc_cpu_player<my_playfield> p;
public:
    virtual
    int play(const playfield &field){
        return p.play(field);
    }
};

class rc_cpu_player_dumb_inh : public player{
    rc_cpu_player_dumb<my_playfield> p;
public:
    virtual
    int play(const playfield &field){
        return p.play(field);
    }
};

#endif //CPP16_RC_INH_AI_PLAYER_H
