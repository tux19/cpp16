#ifndef CPP16_CONNECT4_FACT
#define CPP16_CONNECT4_FACT

#include <iostream>


#include "playfield.h"
#include "player.h"
#include "player_factory.h"

template<typename F>
class connect4 {
private:
    F *field;
    player *player1;
    player *player2;

    bool play = true;
    int round = 1;


public:
    connect4(std::string p1, std::string p2) {
        field = new F();
        player_factory pf;

        player1 = pf.get_player(p1);
        player2 = pf.get_player(p2);
        if(player1 == nullptr || player2 == nullptr){
            throw "ERROR: wrong player selection!";
        }
    }


    void print_field(){
        // Rows
        for(int r = 0; r < field->height; ++r) {

            // Columns
            for(int c = 0; c < field->width; ++c) {
                if(field->stoneat(c, r) == F::player1) {
                    std::cout << "X";
                } else if(field->stoneat(c,r) == F::player2) {
                    std::cout << "O";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << "|" << std::endl;
        }

        for(int i = 0; i < field->width; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;

        for(int i = 0; i < field->width; i++) {
            std::cout << i;
        }
        std::cout << std::endl << std::endl;
    }

    int make_move(int player_no, int col){
        int result = -1;


        for(int r = F::height - 1; r >= 0 && result != 0; --r) {
            if(field->stoneat(col, r) == F::none) {

                field->setstoneat(col,r, player_no);
                result = 0;
            }
        }

        if(result == 0) {
            result = static_cast<int>(field->check_win(player_no));
        }

        return result;
    }
    void runGame(){
        bool roundRunning = true;

        int move = -1;
        int moveResult = -1;

        while(connect4::play) {
            print_field();
            roundRunning = true;

            while(roundRunning) {

                if(field->check_full()) {
                    std::cout << "Game ended in a draw!" << std::endl;
                    play = false;
                    break;
                }

                if(round%2 == 1) {
                    std::cout << "PLAYER 1: " << std::endl;

                    move = player1->play(*const_cast<const F*>(field));

                    if(move == -1) {
                        play = false;
                        break;
                    }

                    moveResult = make_move(1, move);

                    if(moveResult == 0) {
                        roundRunning = false;
                        ++round;
                    } else if (moveResult == 1) {
                        print_field();
                        std::cout << "PLAYER 1 HAS WON!!" << std::endl;
                        roundRunning = false;
                        play = false;
                    }
                } else if(round%2 == 0) {
                    std::cout << "PLAYER 2: " << std::endl;

                    move = player2->play(*const_cast<const F*>(field));

                    if(move == -1) {
                        play = false;
                        break;
                    }

                    moveResult = make_move(2, move);

                    if(moveResult == 0) {
                        roundRunning = false;
                        ++round;
                    } else if (moveResult == 1) {
                        print_field();
                        std::cout << "PLAYER 2 HAS WON!!" << std::endl;
                        roundRunning = false;
                        play = false;
                    }
                }
            }
        }
    }
};
#endif //CPP16_CONNECT4_FACT
