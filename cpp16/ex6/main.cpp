
#include <iostream>
#include <complex>
#include "rpn_pvec.h"
#include "memfun.h"
//#include "connect4_interop/my_playfield.h"
//#include "connect4_interop/connect4.h"
//#include "connect4_interop/rc_cpu_player_dumb.h"
//#include "connect4_interop/rc_human_player.h"
//#include "connect4_interop/extern/reto_ai.h"
//#include "connect4_interop/extern/rkoch_ai.h"
//#include "connect4_interop/rc_cpu_player.h"
#include "connect4_inh/my_playfield.h"
#include "connect4_inh/connect4.h"
#include "connect4_inh/rc_cpu_player_dumb.h"
#include "connect4_inh/extern/reto_ai.h"
#include "connect4_inh/extern/rkoch_ai.h"
#include "connect4_inh/rc_cpu_player_inh.h"

int main(int argc, const char* argv[]){

    std::cout << "------------------------------------------------------------\n|		TASK 6.1 \n ------------------------------------------------------------"
              << std::endl;
    rc_cpu_player_inh p1;
    rc_cpu_player_dumb_inh p2;
    rkoch_ai p3;
    retos_computerplayer p4(2);
    connect4< my_playfield> game(&p1,&p2);
    game.runGame();

    std::cout << "------------------------------------------------------------\n|		TASK 6.2 \n ------------------------------------------------------------"
              << std::endl;
    std::vector<Base*> vec;

    vec.push_back(new Derived1);
    vec.push_back(new Derived2);
    vec.push_back(new Derived1);
    vec.push_back(new Derived2);

    for_each(vec.begin(), vec.end(), std::mem_fun(&Base::print));

    return 0;

    std::cout << "------------------------------------------------------------\n|		TASK 6.4 \n ------------------------------------------------------------"
    << std::endl;

    //rpn_pvec<std::complex<double>> rf_for_each;
    //rf_for_each.run();
}
