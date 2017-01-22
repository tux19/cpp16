/*
 * computer.h
 *
 *  Created on: 13.11.2013
 *      Author: rko
 */

#ifndef CPP16_EX8_CON4_RKOCH
#define CPP16_EX8_CON4_RKOCH

#include <iostream>
#include "../player.h"

class rkoch_ai: public player {

public:
    int play(const playfield &field);

private:
    int find_player_number(const playfield &field);

};

#endif /* CPP16_EX8_CON4_RKOCH */