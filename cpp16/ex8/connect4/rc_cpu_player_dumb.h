
#ifndef CPP16_EX8_CON4_CPU_DUMB
#define CPP16_EX8_CON4_CPU_DUMB

#include <iostream>

#include <vector>

#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include <random>
#include "playfield.h"

template<typename F>
class rc_cpu_player_dumb{
private:
    int _field[ playfield::width][ playfield::height];
    int my_player_no;


    int stoneat(int width, int height){ return _field[width][height];};
    
    // check if player has won with 4 horizontal stones
//    bool check_horizontal(int player_no) {
//
//        bool has_won= false;
//        int counter = 0;
//
//        // for each row
//        for(int r = 0; r < playfield::height && !has_won; ++r) {
//            for(int c = 0; c < playfield::width && !has_won; ++c) {
//                counter = stoneat(c,r) == player_no ? counter + 1 : 0;
//                // if 4 stones in a row
//                if(counter == 4) {
//                    has_won = true;
//                }
//            }
//            counter = 0;
//        }
//        return has_won;
//    }
//
//// check if player has won with 4 vertical stones
//    bool check_vertical(int player_no) {
//
//        bool has_won = false;
//        int counter = 0;
//
//        // for each column
//        for(int c = 0; c < playfield::width && !has_won; ++c) {
//            for(int r = 0; r < playfield::height && !has_won; ++r) {
//                counter = stoneat(c,r) == player_no ? counter + 1 : 0;
//                if(counter == 4) {
//                    has_won = true;
//                }
//            }
//            counter = 0;
//        }
//        return has_won;
//    }

// check if player has won with 4 diagonal stones
    bool check_win(int player_no) {


        // spans a parallelogram where the diagonal sides have length 4
        // and the vertical sides height - 3
        // the parallelogram is moved to the left until it reaches the last column

        // |      *
        // |    * *
        // |  * * *
        // |* * *
        // |* *
        // |*
        // ---------------
        //  0 1 2 3 4 5 6

        // same principle for other diagonal, but from the other side
        int start_col = 0;
        // for every possible start col
        for(start_col = 0; start_col < playfield::width; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                if (stoneat(start_col, start_row) == player_no &&
                    stoneat(start_col, start_row - 1) == player_no &&
                    stoneat(start_col, start_row - 2) == player_no &&
                    stoneat(start_col, start_row - 3) == player_no) {
                    return true;
                }
            }
        }

        for(start_col = 0; start_col < playfield::width-3; start_col++){
            for(int start_row = 0; start_row < playfield::height; start_row++){
                if (stoneat(start_col, start_row) == player_no &&
                    stoneat(start_col + 1, start_row) == player_no &&
                    stoneat(start_col + 2, start_row) == player_no &&
                    stoneat(start_col + 3, start_row) == player_no) {
                    return true;
                }
            }
        }

        for(start_col = 0; start_col < playfield::width -3; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                if (stoneat(start_col, start_row) == player_no &&
                    stoneat(start_col + 1, start_row - 1) == player_no &&
                    stoneat(start_col + 2, start_row - 2) == player_no &&
                    stoneat(start_col + 3, start_row - 3) == player_no) {
                    return true;
                }
            }
        }

        for(start_col = playfield::width - 1; start_col > 2; start_col--){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                if (stoneat(start_col, start_row) == player_no &&
                    stoneat(start_col - 1, start_row - 1) == player_no &&
                    stoneat(start_col - 2, start_row - 2) == player_no &&
                    stoneat(start_col - 3, start_row - 3) == player_no) {
                    return true;
                }
            }
        }
        return false;
    }
//    bool check_win(int player_no) {
//
//        bool hasWon = check_horizontal(player_no);
//        hasWon = hasWon || check_vertical(player_no);
//        hasWon = hasWon || check_diagonal(player_no);
//        return hasWon;
//    }
    
    /*
     * Simple one move ahead checking
     */
    bool try_move(int player_no, int col) {

        bool can_win = false;
        int stone_row = -1;

        // drop stone into column and return row at which it is
        for(int r = playfield::height - 1; r >= 0; --r) {
            if(stoneat(col,r) == playfield::none) {
                _field[col][r] = player_no;
                stone_row = r;
                break;
            }
        }

        if(stone_row != -1) {
            can_win = check_win(player_no);
            _field[col][stone_row] = playfield::none;
        }

        return can_win;
    }



    int player_turn(){
        int p1 = 0, p2 = 0;

        // count stones
        for(int i = 0; i < playfield::width; ++i) {
            for(int j = 0; j < playfield::height; ++j){
                if(stoneat(i,j) == playfield::player1)
                    ++p1;
                else if(stoneat(i,j) == playfield::player2)
                    ++p2;
            }
        }
        return (p1 <= p2 ? playfield::player1 : playfield::player2);
    }

    std::unique_ptr<std::vector<int>> actions(){
        std::unique_ptr<std::vector<int>> v( new std::vector<int>());

        for(int i = 0; i < playfield::width; ++i) {
                if(stoneat(i,0) == playfield::none)
                v->push_back(i);
        }
        return v;

    }


public:
    rc_cpu_player_dumb(){
        my_player_no = -1;

    }

    virtual
    int play(const playfield &field){
        // copys field
        for( int i = 0; i < playfield::width; i++){
            for( int j = 0; j < playfield::height; j++){
                _field[i][j] = field.stoneat(i,j);
            }
        }

        // am I player 1 or player 2?
        if(my_player_no == -1){
            my_player_no = player_turn();
        }

        std::cout << "Renato & Christian's AI is thinking ... " << std::endl;

        int selected_col = -1;

        // all columns where a move is possible (not full yet)
        auto possible_col = actions();

        // test for every possible move if its possible to win for both players
        for(int c : *possible_col){
            // check if I can win
            if(try_move(my_player_no, c)){
                selected_col = c;
                break;
            }

            // check if other player can win
            if(try_move((my_player_no == 1) ? 2 : 1, c)){
                selected_col = c;
            }
        }

        // if neither of the players can win, chose random
        if(selected_col == -1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, (int) possible_col->size());
            selected_col = possible_col->at((dis(gen) - 1));
        }

        std::cout << "Renato & Christian's dumb AI chose column: " << selected_col << std::endl;

        const int res = selected_col;
        return res;
    }
};
#endif //CPP16_EX8_CON4_CPU_DUMB
