#ifndef CPP16_EX6_CON4_INTEROP_HUMAN
#define CPP16_EX6_CON4_INTEROP_HUMAN

#include <iostream>
#include <string>
#include "player.h"


class rc_human_player : public player{
public:
    virtual int play(const playfield &field){
        int selected_col = -1;
        std::string input;

        while(selected_col > field.width || selected_col < 0) {
            std::cout << "Please enter your selected column (or 'q' to quit): ";
            std::cin >> input;
            std::cout << std::endl;

            if(input == "q") {
                return -1;
            }

            selected_col = atoi(input.c_str());
        }

        const int res = selected_col;
        return res;
    }
};

#endif //CPP16_EX6_CON4_INTEROP_HUMAN
