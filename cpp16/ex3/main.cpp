//
// Created by Christian Ott on 30.10.2016.
//

#include <iostream>
#include "connect4/connect4.h"

#include "connect4/rc_playfield.h"
#include "connect4/rc_human_player.h"
#include "connect4/rc_ai_player.h"

int main(int argc, const char* argv[]) {
    connect4< sc_playfield, rc_ai_player<sc_playfield>, rc_human_player<sc_playfield> > game;
    game.runGame();

}