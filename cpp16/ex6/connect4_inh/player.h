#ifndef CPP16_EX6_PLAYER_H
#define CPP16_EX6_PLAYER_H

#include <iostream>

#include "playfield.h"
#include "my_playfield.h"

class player {
public:
    virtual int play(const playfield &field) = 0;
    virtual ~player(){};
};


#endif //CPP16_EX6_PLAYER_H
