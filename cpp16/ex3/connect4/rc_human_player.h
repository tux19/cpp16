//
// Created by Christian Ott on 02.11.2016.
//

#ifndef CPP16_SC_HUMAN_PLAYER_H
#define CPP16_SC_HUMAN_PLAYER_H

#include <iostream>
#include <string>
#include "player.h"

template<typename F>
class rc_human_player : public player<F>{
public:
    int play(const F &field){
        int selectedCol = -1;
        std::string input;

        while(selectedCol > field.width || selectedCol < 0) {
            std::cout << "Please enter your selected column (or 'q' to quit): ";
            std::cin >> input;
            std::cout << std::endl;

            if(input == "q") {
                return -1;
            }

            selectedCol = atoi(input.c_str());
        }

        return selectedCol;
    }
};

#endif //CPP16_SC_HUMAN_PLAYER_H
