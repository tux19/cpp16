
#ifndef CPP16_EX8_CON4_FAC_CPU
#define CPP16_EX8_CON4_FAC_CPU
#include <iostream>

#include <vector>

#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include <cmath>
#include "playfield.h"
#include "player.h"
using field_array =std::array<std::array<int, playfield::height>, playfield::width>;

class rc_cpu_player : public player{
private:

    field_array _field;

    int my_player_no;
    int depth_limit = 8;
    int max_action;

    int stoneat(int col, int row) const {
        assert(col < playfield::width && row < playfield::height);
        return _field[col][row];
    }

    void setstoneat(int col, int row, int player) {
        assert(col < playfield::width && row < playfield::height);
        _field[col][row] = player;
    }

    bool check_win(int player_no) {

        int start_col = 0;
        // horizontal
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
        // vertical
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

        // diagonal bottom left to top right
        for(start_col = 0; start_col < playfield::width - 3; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                if (stoneat(start_col, start_row) == player_no &&
                    stoneat(start_col + 1, start_row - 1) == player_no &&
                    stoneat(start_col + 2, start_row - 2) == player_no &&
                    stoneat(start_col + 3, start_row - 3) == player_no) {
                    return true;
                }
            }
        }
        // same principle for other diagonal, but from the other side
        // diagonal bottom right to top left
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
    /*
     * Simple one move ahead checking
     */
    bool try_move(int player, int col) {

        bool can_win = false;
        int stone_row = -1;

        // drop stone into column and return row at which it is
        for(int r = playfield::height - 1; r >= 0; --r) {
            if(stoneat(col,r) == playfield::none) {
                setstoneat(col, r, player);
                stone_row = r;
                break;
            }
        }

        if(stone_row != -1) {
            can_win = check_win(player);
            setstoneat(col,stone_row, playfield::none);
        }
        return can_win;
    }


    /*
     *  H-MiniMax methods
     */

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
        int mid = playfield::width/2;

        int dir = 0;
        int offset = 0;
        for( int i = 0; i < playfield::width; i++){
            if(stoneat(mid + offset*dir, 0) == playfield::none)
                v->push_back(mid + offset*dir);

            if(dir == -1){
                dir = 1;
                continue;
            }
            if(dir == 1 || dir == 0){
                dir = -1;
                offset++;
            }
        }
        return v;
//        for(int i = 0; i < playfield::width; ++i) {
//            if(stoneat(i,0) == playfield::none)
//                v->push_back(i);
//        }
//        return v;
    }

    int try_line(int player, int col, int row, int colOffset, int rowOffset){

        int score = 0;
        for(int count = 0; count < 4; ++count){

            if(col >= playfield::width || row >= playfield::height || row < 0 || col < 0)
                return 0;

            if(stoneat( col, row) == (player== playfield::player1 ? playfield::player2 : playfield::player1) )
                return 0;
            if(stoneat( col, row) == player)
                score++;

            col += colOffset;
            row += rowOffset;
        }
        return score;
//        for(int count = 0; count < 3; ++count){
//            col += colOffset;
//            row += rowOffset;
//            if(col >= playfield::width || row >= playfield::height || row < 0 || col < 0){
//                return 0;
//            }
//            else if(stoneat(col, row) != player)
//                return 0;
//        }
//        return 1;
    }

    int count_threats(int player, int col, int row){
        return 	try_line(player, col, row, 0, 1) +
                  try_line(player, col, row, 1, 0) +
                  try_line(player, col, row, 1, 1) +
                  try_line(player, col, row, -1, -1);

    }

    int count_winningrows(int player){
        int res = 0;
        int start_col = 0;
        for(start_col = 0; start_col < playfield::width; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res +=  try_line(player, start_col, start_row, 0, -1);
            }
        }

        for(start_col = 0; start_col < playfield::width-3; start_col++){
            for(int start_row = 0; start_row < playfield::height; start_row++){
                res +=  try_line(player, start_col, start_row, 1, 0);
            }
        }

        for(start_col = 0; start_col < playfield::width - 3; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res += try_line( player, start_col, start_row, 1, -1);
            }
        }

        for(start_col = playfield::width - 1; start_col > 2; start_col--){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res += try_line( player, start_col, start_row, -1, -1);
            }
        }
        return res;
    }
    double eval(int player){
        int win = 0, lose = 0;
        player = (player == playfield::player1 ? playfield::player2 : playfield::player1);
        int other_player = (player == playfield::player1 ? playfield::player2 : playfield::player1);


        win = count_winningrows( player);
        lose = count_winningrows( other_player);
//        if(check_win(player)){
//            win = 1;
//            lose = 0;
//        } else if(check_win(other_player)){
//            win = 0;
//            lose = 1;
//        } else {
//            win = 0;
//            lose = 0;
//        }

        int my_odd_threats = 0, their_odd_threats = 0;
        for(int row = 0; row < playfield::height; row +=2){
            for(int col = 0; col < playfield::width; ++col){
                my_odd_threats += count_threats(player, col, row);
                their_odd_threats += count_threats(other_player, col, row);
            }
        }

        int my_even_threats = 0, their_even_threats = 0;
        for(int row = 1; row < playfield::height; row +=2){
            for(int col = 0; col < playfield::width; ++col){
                my_even_threats += count_threats(player, col, row);
                their_even_threats += count_threats(other_player, col, row);
            }
        }

        // coefficients found via genetic algorithms (https://github.com/TJSomething/cs773c-connect4-minimax)
//        std::vector<double> c{	0.2502943943301069,
//                             -0.4952316649483701,
//                             0.3932539700819625,
//                             -0.2742452616759889,
//                             0.4746881137884282,
//                             0.2091091127191147};

        std::vector<double> c{	1,-1.2,0,0,0,0};

        return 	(c.at(0) * win) +
                  (c.at(1) * lose) +
                  (c.at(2) * my_odd_threats) +
                  (c.at(3) * their_odd_threats) +
                  (c.at(4) * my_even_threats) +
                  (c.at(5) * their_even_threats);
    }


    void make_move(int action, int player){
        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(stoneat(action, r) == playfield::none) {
                setstoneat(action,r, player);
                result = 0;
            }
        }
    }

    void undo_move(int action, int player){
        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(stoneat(action, r) == player) {
                setstoneat(action,r, playfield::none);
                result = 0;
            }
        }
    }

    double h_minimax(int depth, int player){

        std::unique_ptr<std::vector<int>> possibleActions = actions();

        //tests if recursion depth is too high
        if(check_win(playfield::player1) ||
           check_win(playfield::player2) ||
           depth >= depth_limit ||
           possibleActions->size() == 0){
            //evaluates the current state of the board and sets max_action and exits
            return eval(player);
        }

        //all possible actions

        if(player == my_player_no){
            // max
            int maxAction;
            double maxValue = -1 * std::numeric_limits<double>::max();

            // iteration over all possible actions
            for(int a : *possibleActions){
                //try the move
                make_move(a,player);

                //recursive call to get the highest value
                double value = h_minimax(depth + 1, player == playfield::player1 ? playfield::player2 : playfield::player1);

                // remove stone
                undo_move(a,player);

                // if value of next iteration > set maxValue and max_action
                if(value > maxValue){
                    maxValue = value;
                    max_action = a;
                }
            }
            return maxValue;

        } else {
            // min

            double minValue = std::numeric_limits<double>::max();
            for(int a : *possibleActions){
                make_move(a, player);
                double value = h_minimax(depth + 1, player == playfield::player1 ? playfield::player2 : playfield::player1);

                undo_move(a, player);
                if(value < minValue){
                    minValue = value;
                }
            }
            return minValue;
        }
    }

public:
    rc_cpu_player(){
        my_player_no = -1;
        max_action = 0;
        for(int i = 0; i < playfield::width; ++i) {
            for(int j = 0; j < playfield::height; ++j){
                setstoneat(i,j,playfield::none);
            }
        }
    }

    int play(const playfield &field){
        // copys field
        int stone = -1;
        for(int i = 0; i < playfield::width; ++i) {
            for(int j = playfield::height -1 ; j >= 0; --j){
                setstoneat(i,j,field.stoneat(i,j));
            }
        }

        // am I player 1 or player 2?
        if(my_player_no == -1){
            my_player_no = player_turn();
        }

        std::cout << "Renato & Christian's AI is thinking ... " << std::endl;

        int selectedCol = -1;

        // all columns where a move is possible (not full yet)
        auto possibleCol = actions();

        // test for every possible move if its possible to win for both players
        for(int c : *possibleCol){
            // check if I can win
            if(try_move(my_player_no, c)){
                selectedCol = c;
                break;
            }

            // check if other player can win
            if(try_move((my_player_no == 1) ? 2 : 1, c)){
                selectedCol = c;
            }
        }

        // if neither of the players can win, evaluate next move with minimax method
        if(selectedCol == -1) {
            h_minimax(0,my_player_no);
            selectedCol = max_action;
        }

        std::cout << "Renato & Christian's AI chose column: " << selectedCol << std::endl;
        make_move(selectedCol, my_player_no);
        return selectedCol;
    }
};

#endif //CPP16_EX8_CON4_CPU
