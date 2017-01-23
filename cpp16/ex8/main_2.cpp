//
// Created by Christian Ott on 21.01.2017.
//

#include <iostream>
#include "connect4_thread/my_playfield.h"
#include "connect4_thread/connect4.h"
#include "../ex6/rpn_pvec.h"

int main(int argc, const char* argv[]){

    std::cout << "------------------------------------------------------------\n|		TASK 6.1 \n ------------------------------------------------------------"
              << std::endl;

    connect4< my_playfield> game("cpu_dumb","cpu_minimax");
    //game.runGame();

    std::cout << "------------------------------------------------------------\n|		TASK 6.2 \n ------------------------------------------------------------"
              << std::endl;


    std::cout << "------------------------------------------------------------\n|		TASK 6.4 \n ------------------------------------------------------------"
              << std::endl;

    std::cin.get();
    rpn_pvec<std::complex<double>> rf_for_each;
    rf_for_each.run();
}
