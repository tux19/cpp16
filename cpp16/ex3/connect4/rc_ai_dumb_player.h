
#ifndef CPP16_RC_AI_DUMB_PLAYER_H
#define CPP16_RC_AI_DUMB_PLAYER_H

#include <iostream>

#include <vector>

#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include <random>

template<typename F>
class rc_cpu_player_dumb{
private:
    std::unique_ptr<F> myPlayfield;
    int myPlayer_No;

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



    int playerTurn(const std::unique_ptr<F> &state){
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

    std::unique_ptr<std::vector<int>> actions(const std::unique_ptr<F> &state){
        std::unique_ptr<std::vector<int>> v( new std::vector<int>());

        for(int i = 0; i < F::width; ++i) {
            if(state->stoneat(i,0) == F::none)
                v->push_back(i);
        }
        return v;

    }


    void makeMove(const std::unique_ptr<F> &state, int action){
        int result = -1;
        for(int r = F::height - 1; r >= 0 && result != 0; --r) {
            if(state->stoneat(action, r) == F::none) {
                state->setstoneat(action,r, playerTurn(state));
                result = 0;
            }
        }
    }

    void undoMove(const std::unique_ptr<F> &state, int action){
        int result = -1;
        for(int r = 0; r < F::height && result != 0; ++r) {
            if(state->stoneat(action, r) == playerTurn(state)) {
                state->setstoneat(action,r, F::none);
                result = 0;
            }
        }
    }



public:
    rc_cpu_player_dumb(){
        myPlayer_No = -1;
        std::unique_ptr<F> f(new F());
        myPlayfield = move(f);
    }

    int play(const F &field){
        // copys field
        std::unique_ptr<F> f(new F(field));
        myPlayfield = move(f);

        // am I player 1 or player 2?
        if(myPlayer_No == -1){
            myPlayer_No = playerTurn(myPlayfield);
        }

        std::cout << "Renato & Christian's AI is thinking ... " << std::endl;

        int selectedCol = -1;

        // all columns where a move is possible (not full yet)
        auto possibleCol = actions(myPlayfield);

        // test for every possible move if its possible to win for both players
        for(int c : *possibleCol){
            // check if I can win
            if(tryMove(myPlayer_No, c)){
                selectedCol = c;
                break;
            }

            // check if other player can win
            if(tryMove((myPlayer_No == 1) ? 2 : 1, c)){
                selectedCol = c;
            }
        }

        // if neither of the players can win, evaluate next move with minimax method
        if(selectedCol == -1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, (int) possibleCol->size());
            selectedCol = possibleCol->at((dis(gen) - 1));
        }

        std::cout << "Renato & Christian's dumb AI chose column: " << selectedCol << std::endl;

        return selectedCol;
    }
};
#endif //CPP16_RC_AI_DUMB_PLAYER_H
