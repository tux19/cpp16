
#include <iostream>
#include "connect4_thread/my_playfield.h"
#include "connect4_thread/connect4.h"
#include "../ex6/rpn_pvec.h"
#include "constdeconst.h"

int main(int argc, const char* argv[]){

    std::cout << "------------------------------------------------------------\n|		TASK 8.3 \n ------------------------------------------------------------"
              << std::endl;

    connect4< my_playfield> game("cpu_dumb","cpu_minimax");
    //game.runGame();

    std::cout << "------------------------------------------------------------\n|		TASK 8.4 \n ------------------------------------------------------------"
              << std::endl;

    std::cout << "First: inherit just from base" << std::endl;
    deriv1();

    std::cout << std::endl;
    std::cout << "Second: inherit from base, base2 (in this order)" << std::endl;
    deriv2();

    std::cout << std::endl;
    std::cout << "Third: inherit from base2, base1" << std::endl;
    deriv3();
}
