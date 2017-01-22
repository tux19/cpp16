
#ifndef CPP16_EX8_CON4_CPU
#define CPP16_EX8_CON4_CPU
#include <iostream>

#include <vector>

#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include "playfield.h"
#include "player.h"
using field_array =std::array<std::array<int, playfield::height>, playfield::width>;

class rc_cpu_player : public player{
private:

    field_array _field;
    int my_player_no;
    int depth_limit = 3;
    int max_action;

    int stoneat(int col, int row) const {
        assert(col < playfield::width && row < playfield::height);
        return _field[col][row];
    }

    void setstoneat(int col, int row, int player) {
        assert(col < playfield::width && row < playfield::height);
        _field[col][row] = player;
    }

    int stoneat(const field_array &state, int col, int row) const {
        assert(col < playfield::width && row < playfield::height);
        return state[col][row];
    }

    void setstoneat(field_array &state, int col, int row, int player) {
        assert(col < playfield::width && row < playfield::height);
        state[col][row] = player;
    }

    bool check_win(const field_array &state, int player_no) {


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
    bool try_move(field_array &state, int col) {
        int player = player_turn(state);

        bool can_win = false;
        int stone_row = -1;

        // drop stone into column and return row at which it is
        for(int r = playfield::height - 1; r >= 0; --r) {
            if(stoneat(state,col,r) == playfield::none) {
                setstoneat(state, col, r, player);
                stone_row = r;
                break;
            }
        }

        if(stone_row != -1) {
            can_win = check_win(state, player);
            setstoneat(state, col,stone_row, playfield::none);
        }
        return can_win;
    }


    /*
     *  H-MiniMax methods
     */

    int player_turn(const field_array &state){
        int p1 = 0, p2 = 0;

        // count stones
        for(int i = 0; i < playfield::width; ++i) {
            for(int j = 0; j < playfield::height; ++j){
                if(stoneat(state, i,j) == playfield::player1)
                    ++p1;
                else if(stoneat(state, i,j) == playfield::player2)
                    ++p2;
            }
        }
        return (p1 <= p2 ? playfield::player1 : playfield::player2);
    }

    std::vector<int> actions(const field_array &state){
        std::vector<int> v;

        for(int i = 0; i < playfield::width; ++i) {
            if(stoneat(state,i,0) == playfield::none)
                v.push_back(i);
        }
        return v;
    }

    int try_line(const field_array &state, int player, int col, int row, int colOffset, int rowOffset){
        int score = 0;
        for(int count = 0; count < 3; ++count){

            if(col >= playfield::width || row >= playfield::height || row < 0 || col < 0)
                return 0;
            if(stoneat(state, col, row) != player || stoneat(state, col, row) != playfield::none)
                return 0;
            if(stoneat(state, col, row) == player)
                score++;

            col += colOffset;
            row += rowOffset;
        }
        return score;
    }


    int count_winningrows(const field_array &state, int player){
        int res = 0;
        for(start_col = 0; start_col < playfield::width; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res +=  try_line(state, player, i, j, 0, -1);
            }
        }

        for(start_col = 0; start_col < playfield::width-3; start_col++){
            for(int start_row = 0; start_row < playfield::height; start_row++){
                res +=  try_line(state, player, i, j, 1, 0);
            }
        }

        for(start_col = 0; start_col < playfield::width - 3; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res += try_line(state, player, i, j, 1, -1);
            }
        }

        for(start_col = playfield::width - 1; start_col > 2; start_col--){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res += try_line(state, player, i, j, -1, -1);
            }
        }
        return res;
    }

    double eval(const field_array &state, int player) {
        int win = count_winningrows(state, player);
        int other_player = (player == playfield::player1 ? playfield::player2 : playfield::player1);
        int lose = count_winningrows(state, other_player);


        return win - lose;
    }

    bool cutoff_test(const field_array &state, int d){
        int player = player_turn(state);

        if(player == playfield::player1){
            return check_win(state, playfield::player1) ||
                      d >= depth_limit ||
                      actions(state).size() == 0;
        } else {
            return check_win(state, playfield::player2) ||
                      d >= depth_limit ||
                      actions(state).size() == 0;
        }
    }

    void make_move(field_array &state, int action){
        int player = player_turn(state);
        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(stoneat(state, action, r) == playfield::none) {
                setstoneat(state, action,r, player);
                result = 0;
            }
        }
    }

    void undo_move(field_array &state, int action){
        int player = player_turn(state);

        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(stoneat(state, action, r) == player) {
                setstoneat(state, action,r, playfield::none);
                result = 0;
            }
        }
    }

    void make_move(int action){
        int player = player_turn(_field);

        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(stoneat(action, r) == playfield::none) {
                setstoneat(action,r, player);
                result = 0;
            }
        }
    }

    void undo_move(int action){
        int player = player_turn(_field);

        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(stoneat(action, r) == player) {
                setstoneat(action,r, playfield::none);
                result = 0;
            }
        }
    }

    double h_minimax(field_array &state, int depth){
        int player = player_turn(_field);
        //tests if recursion depth is too high
        if(cutoff_test(state, depth)){
            //evaluates the current state of the board and sets max_action and exits
            return eval(state, this->my_player_no);
        }

        //all possible actions
        std::vector<int> possibleActions = actions(state);

        if(player == my_player_no){
            // max
            int maxAction = -1;
            double maxValue = -1 * std::numeric_limits<double>::max();

            // iteration over all possible actions
            for(int a : possibleActions){
                //try the move
                make_move(state, a);

                //recursive call to get the highest value
                double value = h_minimax(state, depth + 1);

                // remove stone
                undo_move(state, a);

                // if value of next iteration > set maxValue and max_action
                if(value > maxValue){
                    maxValue = value;
                    maxAction = a;
                }
            }
            max_action = maxAction;

            return maxValue;

        } else {
            // min

            double minValue = std::numeric_limits<double>::max();
            for(int a : possibleActions){
                make_move(state, a);
                double value = h_minimax(state, depth + 1);

                undo_move(state, a);
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
            my_player_no = player_turn(_field);
        }

        std::cout << "Renato & Christian's AI is thinking ... " << std::endl;

        int selectedCol = -1;

        // all columns where a move is possible (not full yet)
        auto possibleCol = actions(_field);

        // test for every possible move if its possible to win for both players
        for(int c : possibleCol){
            // check if I can win
            if(try_move(_field, c)){
                selectedCol = c;
            }

            // check if other player can win
            if(try_move(_field, c)){
                selectedCol = c;
            }
        }

        // if neither of the players can win, evaluate next move with minimax method
        if(selectedCol == -1) {
            h_minimax(_field, 0);
            selectedCol = max_action;
        }

        std::cout << "Renato & Christian's AI chose column: " << selectedCol << std::endl;
        make_move(selectedCol);
        return selectedCol;
    }
};
#endif //CPP16_EX8_CON4_CPU
