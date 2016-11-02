//
// Created by Christian Ott on 30.10.2016.
//

#include <iostream>
#include "fraction.h"
#include "rpn_pvec.h"
#include "connect4/connect4.h"
#include "connect4/rc_playfield.h"
#include "connect4/rc_human_player.h"
#include "connect4/rc_ai_player.h"

int main(int argc, const char* argv[]) {
    std::cout
            << "------------------------------------------------------------\n|		TASK 3.1 \n ------------------------------------------------------------"
            << std::endl;

    std::cout
            << "------------------------------------------------------------\n|		TASK 3.2 \n ------------------------------------------------------------"
            << std::endl;

    std::cout
            << "------------------------------------------------------------\n|		TASK 3.3 \n ------------------------------------------------------------"
            << std::endl;

    rpn_pvec<fraction> rf_for_each;
    rf_for_each.run();

    std::cout
            << "------------------------------------------------------------\n|		TASK 3.4 & 3.5 \n ------------------------------------------------------------"
            << std::endl;
    connect4< sc_playfield, rc_ai_player<sc_playfield>, rc_human_player<sc_playfield> > game;
    game.runGame();


    std::cin.get();

}