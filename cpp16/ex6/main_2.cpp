
#include <iostream>
#include <complex>
#include "rpn_pvec.h"
#include "memfun.h"
#include "connect4_interop/my_playfield.h"
#include "connect4_interop/connect4.h"
#include "connect4_interop/rc_cpu_player_dumb.h"
#include "connect4_interop/rc_human_player.h"
#include "connect4_interop/extern/reto_ai.h"
#include "connect4_interop/extern/rkoch_ai.h"
#include "connect4_interop/rc_cpu_player.h"


int main(int argc, const char* argv[]){

    std::cout << "------------------------------------------------------------\n|		TASK 6.1 \n ------------------------------------------------------------"
              << std::endl;

    std::cout << "------------------------------------------------------------\n|		TASK 6.2 \n ------------------------------------------------------------"
              << std::endl;
    std::vector<Base*> vec;

    vec.push_back(new Derived1);
    vec.push_back(new Derived2);
    vec.push_back(new Derived1);
    vec.push_back(new Derived2);

    for_each(vec.begin(), vec.end(), std::mem_fun(&Base::print));

    std::cout << "------------------------------------------------------------\n|		TASK 6.3 \n ------------------------------------------------------------"
              << std::endl;



    connect4< my_playfield,rc_cpu_player, rc_cpu_player_dumb<my_playfield>> game;
    //game.runGame();
    std::cout << "------------------------------------------------------------\n|		TASK 6.4 \n ------------------------------------------------------------"
    << std::endl;
    rpn_pvec<std::complex<double>> rf_for_each;
    rf_for_each.run();
    system("pause");
    return 0;
}
