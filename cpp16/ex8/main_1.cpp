
#include <iostream>
#include "connect4_factory/my_playfield.h"
#include "connect4_factory/connect4.h"
#include "spellchecker.h"

int main(int argc, const char* argv[]){

    std::cout << "------------------------------------------------------------\n|		TASK 8.1 \n ------------------------------------------------------------"
              << std::endl;

    connect4< my_playfield> game("cpu_dumb","cpu_minimax");
    //game.runGame();

    std::cout << "------------------------------------------------------------\n|		TASK 8.2 \n ------------------------------------------------------------"
              << std::endl;
    spellchecker r;
    r.run();


    std::cin.get();

}
