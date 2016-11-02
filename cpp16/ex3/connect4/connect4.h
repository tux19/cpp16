//
// Created by Christian Ott on 02.11.2016.
//

#ifndef CPP16_CONNECT4_H
#define CPP16_CONNECT4_H

#include <iostream>


#include "rc_playfield.h"
#include "player.h"

template<typename F, typename P1=player<F>, typename P2=player<F>>
class connect4 {
private:
    F *myPlayfield;
    P1 *player1;
    P2 *player2;

    bool play = true;
    int round = 1;


public:
    connect4(){
        this->myPlayfield = new F();
        this->player1 = new P1();
        this->player2 = new P2();
    }

    void printField(){
        // Rows
        for(int r = 0; r < myPlayfield->height; ++r) {

            // Columns
            for(int c = 0; c < myPlayfield->width; ++c) {
                if(myPlayfield->stoneat(c, r) == F::player1) {
                    std::cout << "X";
                } else if(myPlayfield->stoneat(c,r) == F::player2) {
                    std::cout << "O";
                } else {
                    std::cout << " ";
                }
            }

            std::cout << "|" << std::endl;
        }

        for(int i = 0; i < myPlayfield->width; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;

        for(int i = 0; i < myPlayfield->width; i++) {
            std::cout << i;
        }
        std::cout << std::endl << std::endl;
    }

    int makeMove(int playerNo, int col){
        int result = -1;

        for(int r = F::height - 1; r >= 0 && result != 0; --r) {
            if(myPlayfield->stoneat(col, r) == F::none) {

                myPlayfield->setstoneat(col,r, playerNo);

                result = 0;
            }
        }

        if(result == 0) {
            result = static_cast<int>(myPlayfield->checkWin(playerNo));
        }

        return result;
    }
    void runGame(){
        bool roundRunning = true;

        int move = -1;
        int moveResult = -1;

        while(connect4::play) {
            printField();
            roundRunning = true;

            while(roundRunning) {

                if(myPlayfield->checkFull()) {
                    std::cout << "Game ended in a draw!" << std::endl;
                    play = false;
                    break;
                }

                if(round%2 == 1) {
                    std::cout << "PLAYER 1: " << std::endl;

                    const F *cField = const_cast<const F*>(myPlayfield);
                    move = player1->play(*cField);

                    if(move == -1) {
                        play = false;
                        break;
                    }

                    moveResult = makeMove(1, move);

                    if(moveResult == 0) {
                        roundRunning = false;
                        ++round;
                    } else if (moveResult == 1) {
                        printField();
                        std::cout << "PLAYER 1 HAS WON!!" << std::endl;
                        roundRunning = false;
                        play = false;
                    }
                } else if(round%2 == 0) {
                    std::cout << "PLAYER 2: " << std::endl;

                    const F *cField = const_cast<const F*>(myPlayfield);
                    move = player2->play(*cField);

                    if(move == -1) {
                        play = false;
                        break;
                    }

                    moveResult = makeMove(2, move);

                    if(moveResult == 0) {
                        roundRunning = false;
                        ++round;
                    } else if (moveResult == 1) {
                        printField();
                        std::cout << "PLAYER 2 HAS WON!!" << std::endl;
                        roundRunning = false;
                        play = false;
                    }
                }
            }
        }
    }
};
#endif //CPP16_CONNECT4_H
