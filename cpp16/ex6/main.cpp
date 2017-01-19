
#include <iostream>
#include <complex>
#include "rpn_pvec.h"
#include "connect4_inh/my_playfield.h"
#include "connect4_inh/connect4.h"
#include "connect4_inh/rc_ai_dumb_player.h"
#include "connect4_inh/rc_human_player.h"
#include "connect4_inh/extern/reto_ai.h"
#include "connect4_inh/extern/rkoch_ai.h"

int main(int argc, const char* argv[]){

    std::cout << "------------------------------------------------------------\n|		TASK 6.1 \n ------------------------------------------------------------"
              << std::endl;

    connect4< my_playfield, rc_ai_dumb_player_inh, rkoch_ai > game;
    game.runGame();

    std::cout << "------------------------------------------------------------\n|		TASK 6.2 \n ------------------------------------------------------------"
              << std::endl;


    std::cout << "------------------------------------------------------------\n|		TASK 6.4 \n ------------------------------------------------------------"
    << std::endl;

    //rpn_pvec<std::complex<double>> rf_for_each;
    //rf_for_each.run();
}
