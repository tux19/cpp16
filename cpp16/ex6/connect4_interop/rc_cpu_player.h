
#ifndef CPP16_EX6_CON4_INTEROP_CPU
#define CPP16_EX6_CON4_INTEROP_CPU
#include <iostream>

#include <vector>

#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include "playfield.h"
#include "player.h"

class rc_cpu_player : public player{
private:

    int _field[ playfield::width][ playfield::height];

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



    bool check_horizontal(int player_no) {

        bool has_won= false;
        int counter = 0;

        // for each row
        for(int r = 0; r < playfield::height && !has_won; ++r) {
            for(int c = 0; c < playfield::width && !has_won; ++c) {
                counter = stoneat(c,r) == player_no ? counter + 1 : 0;
                // if 4 stones in a row
                if(counter == 4) {
                    has_won = true;
                }
            }
            counter = 0;
        }
        return has_won;
    }

// check if player has won with 4 vertical stones
    bool check_vertical(int player_no) {

        bool has_won = false;
        int counter = 0;

        // for each column
        for(int c = 0; c < playfield::width && !has_won; ++c) {
            for(int r = 0; r < playfield::height && !has_won; ++r) {
                counter = stoneat(c,r) == player_no ? counter + 1 : 0;
                if(counter == 4) {
                    has_won = true;
                }
            }
            counter = 0;
        }
        return has_won;
    }

// check if player has won with 4 diagonal stones
    bool check_diagonal(int player_no) {

        bool has_won = false;
        int counter = 0;

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
        for(start_col = 0; start_col < playfield::width-3; start_col++){
            for(int start_row = 3; start_row < playfield::height; start_row++){
                for (int h = 0 ; h < 4; ++h) {
                    counter = stoneat(start_col + h, start_row - h) == player_no ? counter + 1 : 0;
                    if (counter == 4) {
                        has_won = true;
                    }
                }
            }
        }
        counter = 0;
        for(start_col = playfield::width - 1; start_col > 2; start_col--){
            for(int start_row = 3; start_row < playfield::height; start_row++){
                for (int h = 0 ; h < 4; ++h) {
                    counter = stoneat(start_col - h, start_row - h) == player_no ? counter + 1 : 0;
                    if (counter == 4) {
                        has_won = true;
                    }
                }
            }
        }
        return has_won;
    }
    bool check_win(int player_no) {

        bool hasWon = check_horizontal(player_no);
        hasWon = hasWon || check_vertical(player_no);
        hasWon = hasWon || check_diagonal(player_no);
        return hasWon;
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

        for(int i = 0; i < playfield::width; ++i) {
            if(stoneat(i,0) == playfield::none)
                v->push_back(i);
        }
        return v;
    }

    int try_line(int player, int col, int row, int colOffset, int rowOffset){

        for(int count = 0; count < 3; ++count){
            col += colOffset;
            row += rowOffset;
            if(col >= playfield::width || row >= playfield::height){
                return 0;
            }
            else if(stoneat(col, row) != player)
                return 0;
        }
        return 1;
    }

    int count_threats(int player, int col, int row){
        if(stoneat(col,row) == playfield::none)
            return 0;

        return 	try_line(player, col, row, 1, 1) +
                  try_line(player, col, row, 1, -1) +
                  try_line(player, col, row, -1, -1) +
                  try_line(player, col, row, -1, 1);

    }

    double eval(int player){
        int win = 0, lose = 0;
        int other_player = (player == playfield::player1 ? playfield::player2 : playfield::player1);

        if(check_win(player)){
            win = 1;
            lose = 0;
        } else if(check_win(other_player)){
            win = 0;
            lose = 1;
        } else {
            win = 0;
            lose = 0;
        }

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
        std::vector<double> c{	0.2502943943301069,
                             -0.4952316649483701,
                             0.3932539700819625,
                             -0.2742452616759889,
                             0.4746881137884282,
                             0.2091091127191147};

        return 	(c.at(0) * win) +
                  (c.at(1) * lose) +
                  (c.at(2) * my_odd_threats) +
                  (c.at(3) * their_odd_threats) +
                  (c.at(4) * my_even_threats) +
                  (c.at(5) * their_even_threats);
    }

    bool cutoff_test( int d){
        int player = player_turn();

        if(player == playfield::player1){
            return check_win(playfield::player1) ||
                      d >= depth_limit ||
                      actions()->size() == 0;
        } else {
            return check_win(playfield::player2) ||
                      d >= depth_limit ||
                      actions()->size() == 0;
        }
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

        //tests if recursion depth is too high
        if(cutoff_test(depth)){
            //evaluates the current state of the board and sets max_action and exits
            return eval(player);
        }

        //all possible actions
        std::unique_ptr<std::vector<int>> possibleActions = actions();

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
                if(field.stoneat(i,j)!= _field[i][j]){
                    stone = field.stoneat(i,j);
                    setstoneat(i,j,stone);
                    break;
                }
                if(field.stoneat(i,j)== playfield::none){
                    break;
                }
            }
            if(stone > -1){
                break;
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
#endif //CPP16_EX6_CON4_INTEROP_CPU
