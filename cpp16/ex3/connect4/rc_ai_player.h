
#ifndef CPP16_SC_AI_PLAYER_H
#define CPP16_SC_AI_PLAYER_H
#include <iostream>

#include <vector>

#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include "rc_playfield.h"
#include "player.h"

template<typename F>
class rc_ai_player : public player<F>{
private:
    std::unique_ptr<sc_playfield> myPlayfield;
    int myPlayerNo;
    int depthLimit = 8;
    int maxAction;


    /*
     * Simple one move ahead checking
     */
    bool tryMove(int playerNo, int col) {

        bool canWin = false;
        int stoneRow = -1;

        // drop stone into column and return row at which it is
        for(int r = F::height - 1; r >= 0; --r) {
            if(myPlayfield->stoneat(col,r) == F::none) {
                myPlayfield->setstoneat(col,r, playerNo);
                stoneRow = r;
                break;
            }
        }

        if(stoneRow != -1) {
            canWin = myPlayfield->check_win(playerNo);
            myPlayfield->setstoneat(col,stoneRow, F::none);
        }

        return canWin;
    }


    /*
     *  H-MiniMax methods
     */

    int playerTurn(const std::unique_ptr<sc_playfield> &state){
        int p1 = 0, p2 = 0;

        // count stones
        for(int i = 0; i < F::width; ++i) {
            for(int j = 0; j < F::height; ++j){
                if(state->stoneat(i,j) == F::player1)
                    ++p1;
                else if(state->stoneat(i,j) == F::player2)
                    ++p2;
            }
        }
        return (p1 <= p2 ? F::player1 : F::player2);
    }

    std::unique_ptr<std::vector<int>> actions(const std::unique_ptr<sc_playfield> &state){
        std::unique_ptr<std::vector<int>> v( new std::vector<int>());

        for(int i = 0; i < F::width; ++i) {
            if(state->stoneat(i,0) == F::none)
                v->push_back(i);
        }
        return v;

    }

    int try_line(const std::unique_ptr<sc_playfield> &state, int player, int col, int row, int colOffset, int rowOffset){
        for(int count = 0; count < 3; ++count){
            col += colOffset;
            row += rowOffset;
            if(state->stoneat(col, row) != player)
                return 0;
        }
        return 1;
    }

    int count_threats(const std::unique_ptr<sc_playfield> &state, int player, int col, int row){
        if(state->stoneat(col,row) == F::none)
            return 0;

        return 	try_line(state, player, col, row, 1, 1) +
                  try_line(state, player, col, row, 1, -1) +
                  try_line(state, player, col, row, -1, -1) +
                  try_line(state, player, col, row, -1, 1);

    }

    double eval(const std::unique_ptr<sc_playfield> &state){
        int win = 0, lose = 0;
        int player = playerTurn(state);
        int otherPlayer = (player == F::player1 ? F::player2 : F::player1);

        if(state->check_win(player)){
            win = 1;
            lose = 0;
        } else if(state->check_win(otherPlayer)){
            win = 0;
            lose = 1;
        } else {
            win = 0;
            lose = 0;
        }

        int myOddThreats = 0, theirOddThreats = 0;
        for(int row = 0; row < F::height; row +=2){
            for(int col = 0; col < F::width; ++col){
                myOddThreats += count_threats(state, player, col, row);
                theirOddThreats += count_threats(state, otherPlayer, col, row);
            }
        }

        int myEvenThreats = 0, theirEvenThreats = 0;
        for(int row = 1; row < F::height; row +=2){
            for(int col = 0; col < F::width; ++col){
                myEvenThreats += count_threats(state, player, col, row);
                theirEvenThreats += count_threats(state, otherPlayer, col, row);
            }
        }

        // coefficients found via genetic algorithms (https://github.com/TJSomething/cs773c-connect4-minimax)
        std::vector<double> c{	0.2502943943301069,
                             -0.4952316649483701,
                             0.3932539700819625,
                             -0.2742452616759889,
                             0.4746881137884282,
                             0.2091091127191147};

        return 	(c.at(0) * win) +
                  (c.at(1) * lose) +
                  (c.at(2) * myOddThreats) +
                  (c.at(3) * theirOddThreats) +
                  (c.at(4) * myEvenThreats) +
                  (c.at(5) * theirEvenThreats);
    }

    bool cutoff_test(const std::unique_ptr<sc_playfield> &state, int d){
        int player = playerTurn(state);

        if(player == F::player1){
            return state->check_win(F::player1) ||
                      d >= depthLimit ||
                      actions(state)->size() == 0;
        } else {
            return state->check_win(F::player2) ||
                      d >= depthLimit ||
                      actions(state)->size() == 0;
        }
    }

    void makeMove(const std::unique_ptr<sc_playfield> &state, int action){
        int result = -1;
        for(int r = F::height - 1; r >= 0 && result != 0; --r) {
            if(state->stoneat(action, r) == F::none) {
                state->setstoneat(action,r, playerTurn(state));
                result = 0;
            }
        }
    }

    void undoMove(const std::unique_ptr<sc_playfield> &state, int action){
        int result = -1;
        for(int r = 0; r < F::height && result != 0; ++r) {
            if(state->stoneat(action, r) == playerTurn(state)) {
                state->setstoneat(action,r, F::none);
                result = 0;
            }
        }
    }

    double h_minimax(const std::unique_ptr<sc_playfield> &state, int depth){
        if(cutoff_test(state,depth)){
            return eval(state);
        }

        std::unique_ptr<std::vector<int>> possibleActions = actions(state);

        if(playerTurn(state) == myPlayerNo){
            // max
            int maxAction;
            double maxValue = -1 * std::numeric_limits<double>::max();

            for(int a : *possibleActions){
                makeMove(state, a);
                double value = h_minimax(state, depth + 1);

                undoMove(state, a);

                if(value > maxValue){
                    maxValue = value;
                    maxAction = a;
                }
            }
            this->maxAction = maxAction;

            return maxValue;

        } else {
            // min

            int minAction;
            double minValue = std::numeric_limits<double>::max();

            for(int a : *possibleActions){
                makeMove(state, a);
                double value = h_minimax(state, depth + 1);

                undoMove(state, a);
                if(value < minValue){
                    minValue = value;
                    minAction = a;
                }
            }
            return minValue;
        }
    }

public:
    rc_ai_player(){
        myPlayerNo = -1;
        maxAction = 0;
        std::unique_ptr<sc_playfield> f(new sc_playfield());
        myPlayfield = move(f);
    }

    int play(const F &field){
        std::unique_ptr<sc_playfield> f(new sc_playfield(field));
        myPlayfield = move(f);

        // am I player 1 or player 2?
        if(myPlayerNo == -1){
            myPlayerNo = playerTurn(myPlayfield);
        }

        std::cout << "Renato & Christian's AI is thinking ... " << std::endl;

        int selectedCol = -1;

        auto possibleCol = actions(myPlayfield);
        for(int c : *possibleCol){
            // check if I can win
            if(tryMove(myPlayerNo, c)){
                selectedCol = c;
                break;
            }

            // check if other player can win
            if(tryMove((myPlayerNo == 1) ? 2 : 1, c)){
                selectedCol = c;
            }
        }

        // if neither of the players can win, evaluate next move with minimax method
        if(selectedCol == -1) {
            h_minimax(myPlayfield,0);
            selectedCol = maxAction;
        }

        std::cout << "Renato & Christian's AI chose column: " << selectedCol << std::endl;

        return selectedCol;
    }
};
#endif //CPP16_SC_AI_PLAYER_H
