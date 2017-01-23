
#ifndef CPP16_EX8_CON4_FAC_CPU
#define CPP16_EX8_CON4_FAC_CPU
#include <iostream>

#include <vector>
#include <boost/thread.hpp>
#include <climits>
#include <limits>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <algorithm>
#include "playfield.h"
#include "cpu_playfield.h"
#include "player.h"
using field_array =std::array<std::array<int, playfield::height>, playfield::width>;

class rc_cpu_player : public player{
private:

    cpu_playfield _field;

    int my_player_no;
    int depth_limit = 8;
    int max_action;
    bool first_round;

    // vector containing pairs of possible_fields and their best responses
    std::vector<std::pair<cpu_playfield, int> > predicted_fields;

    // mutex lock for best_responses
    boost::mutex predicted_fields_mutex;

    // vector containing threads which compute the best response given a possible_field
    std::vector<boost::thread> prediction_threads;


    /*
     * Simple one move ahead checking
     */
    bool try_move(cpu_playfield &state, int player, int col) {

        bool can_win = false;
        int stone_row = -1;

        // drop stone into column and return row at which it is
        for(int r = playfield::height - 1; r >= 0; --r) {
            if(state.stoneat(col,r) == playfield::none) {
                state.setstoneat(col, r, player);
                stone_row = r;
                break;
            }
        }

        if(stone_row != -1) {
            can_win = state.check_win(player);
            state.setstoneat(col,stone_row, playfield::none);
        }
        return can_win;
    }



    int try_line(const cpu_playfield &state, int player, int col, int row, int colOffset, int rowOffset){

        int score = 0;
        for(int count = 0; count < 4; ++count){

            if(col >= playfield::width || row >= playfield::height || row < 0 || col < 0)
                return 0;

            if(state.stoneat( col, row) == (player== playfield::player1 ? playfield::player2 : playfield::player1) )
                return 0;
            if(state.stoneat( col, row) == player)
                score++;

            col += colOffset;
            row += rowOffset;
        }
        return score;
    }

    int try_line2(const cpu_playfield &state, int player, int col, int row, int colOffset, int rowOffset){

        int score = 0;
        for(int count = 0; count < 3; ++count){
            col += colOffset;
            row += rowOffset;
            if(col >= playfield::width || row >= playfield::height || row < 0 || col < 0)
                return 0;
            if(state.stoneat( col, row) == playfield::none && count == 2)
                return 1;
            if(state.stoneat( col, row) != player )
                return 0;

        }
        return score;
    }
    int count_threats(const cpu_playfield &state, int player, int col, int row){
        return 	try_line2(state, player, col, row, 0, 1) +
                  try_line2(state, player, col, row, 1, 0) +
                  try_line2(state, player, col, row, 1, 1) +
                  try_line2(state, player, col, row, -1, -1);

    }


    int count_winningrows(const cpu_playfield &state, int player){
        int res = 0;
        int start_col = 0;
        for(start_col = 0; start_col < playfield::width; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res +=  try_line(state, player, start_col, start_row, 0, -1);
            }
        }

        for(start_col = 0; start_col < playfield::width-3; start_col++){
            for(int start_row = 0; start_row < playfield::height; start_row++){
                res +=  try_line(state,player, start_col, start_row, 1, 0);
            }
        }

        for(start_col = 0; start_col < playfield::width - 3; start_col++){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res += try_line( state, player, start_col, start_row, 1, -1);
            }
        }

        for(start_col = playfield::width - 1; start_col > 2; start_col--){
            for(int start_row = playfield::height - 1; start_row > 2; start_row--) {
                res += try_line( state, player, start_col, start_row, -1, -1);
            }
        }
        return res;
    }


    double eval2(const cpu_playfield &state, int player){
        int win = 0, lose = 0;
        //player = (player == playfield::player1 ? playfield::player2 : playfield::player1);
        int other_player = (player == playfield::player1 ? playfield::player2 : playfield::player1);


        if(state.check_win(player)){
            win = 1;
            lose = 0;
        } else if(state.check_win(other_player)){
            win = 0;
            lose = 1;
        } else {
            win = 0;
            lose = 0;
        }

        int my_odd_threats = 0, their_odd_threats = 0;
        for(int row = playfield::height -1 ; row > 0; row -=2){
            for(int col = 0; col < playfield::width; ++col){
                my_odd_threats += count_threats(state, player, col, row);
                their_odd_threats += count_threats(state, other_player, col, row);
            }
        }

        int my_even_threats = 0, their_even_threats = 0;
        for(int row = playfield::height -2 ; row > 0; row -=2){
            for(int col = 0; col < playfield::width; ++col){
                my_even_threats += count_threats(state, player, col, row);
                their_even_threats += count_threats(state, other_player, col, row);
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
    double eval(const cpu_playfield &state, int player){
        int win = 0, lose = 0;

        win = count_winningrows( state, player);
        return win;//-lose;
    }


    void make_move(int action, int player){
        _field.setstoneat(action, player);
    }

    void undo_move(int action, int player){
        int result = -1;
        for(int r = playfield::height - 1; r >= 0 && result != 0; --r) {
            if(_field.stoneat(action, r) == player) {
                _field.setstoneat(action,r, playfield::none);
                result = 0;
            }
        }
    }

    double evaluation(const cpu_playfield &state, bool max_player){

        return 1;
    }

    bool is_terminal_state(const cpu_playfield &state, int p1, int p2) {
        return state.check_win(p1)||state.check_win(p2);
    }

    double ab_minimax(const cpu_playfield &state, int depth, double a, double b, bool max_player){

        int other_player =  this->my_player_no == playfield::player1 ? playfield::player2 : playfield::player1;
        auto possible = state.actions();

        if( depth >= this->depth_limit ||
                state.check_full() ||
                state.check_win(playfield::player1)||
                state.check_win(playfield::player2)){

            if (max_player) {
                return eval2(state, this->my_player_no);
            } else {
                return eval2(state, other_player);
            }
        }

        if(max_player){
            for(auto col : *possible) {
                cpu_playfield child(state);
                child.setstoneat(col, this->my_player_no);
                a = std::max(a, ab_minimax(child, depth + 1, a, b, false));
                if (b <= a) {
                    break;
                }
            }
            return a;
        } else{
            for(auto col : *possible){
                cpu_playfield child(state);
                child.setstoneat(col, other_player);
                b = std::max(b, ab_minimax(child, depth + 1, a, b, true));
                if(b <= a){
                    break;
                }
            }
            return b;
        }
    }


    void predict_response(cpu_playfield &possible_field){
        // best response
        int slot;
        cpu_playfield field(possible_field);

        auto possible = field.actions();

        std::vector<std::pair<int,double >> moves;
        std::vector<cpu_playfield> children (possible->size(), field);
        auto child_iter = std::begin(children);
        // test for every possible move if its possible to win for both players
        for(int c :  *possible){

            if(try_move(*child_iter,playfield::player1,c)||try_move(*child_iter,playfield::player2,c)){
                slot = c;
            }
            child_iter->setstoneat(c,my_player_no);
            double weight = ab_minimax(*child_iter,0,-std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                                       true);
            moves.push_back(std::make_pair(c,weight));
        }
        auto selection = std::min_element(moves.begin(),moves.end(),[&] (std::pair<int,double > &lhs, std::pair<int,double > &rhs) {
            return lhs.second > rhs.second ;
        });
        slot = selection->first;

        predicted_fields_mutex.lock();
        predicted_fields.push_back(std::pair<cpu_playfield, int>(field, slot));
        predicted_fields_mutex.unlock();
    }
public:
    rc_cpu_player(){
        my_player_no = -1;
        max_action = 0;
        first_round = true;
    }

    int play(const playfield &field){
        // copys field

        int stone = -1;
        if(first_round){
            cpu_playfield init_field(field);
            int slot;
            my_player_no = init_field.is_empty() ? playfield::player1 : playfield::player2;
            if(my_player_no == playfield::player1){
                slot = 3;
                init_field.setstoneat(slot,my_player_no);
            } else{
                slot = rand() % playfield::width-1;
                init_field.setstoneat(slot,my_player_no);
            }
            // best responses when playing second
            for(int x = 0; x < playfield::width; ++x){
                cpu_playfield possible_field(init_field);
                possible_field.setstoneat(x, my_player_no == 1 ? 2 : 1);
                predicted_fields.push_back(std::pair<cpu_playfield, int>(possible_field, x));
            }
            first_round = false;
            return slot;
        }
        for (boost::thread &thread : prediction_threads) {
            thread.join();
        }
        int slot = -1;
        cpu_playfield tmpfield(field);


        // find which best_response matches the actual field
        predicted_fields_mutex.lock();
        for(std::pair<cpu_playfield, int> &best : predicted_fields){
            if (best.first == field)
                slot = best.second;
        }
        predicted_fields.clear();
        predicted_fields_mutex.unlock();

        // start next round's computation
        prediction_threads.clear();

        cpu_playfield new_field(tmpfield);
        new_field.setstoneat(slot,my_player_no);

        // create every possible enemy move and assign a thread towards calculating the best response
        std::vector<int> poss_other;
        for(int i = 0; i < playfield::width; ++i) {
            if(new_field.stoneat(i,0) == playfield::none)
                poss_other.push_back(i);
        }
        for (int col : poss_other){
            cpu_playfield possible_field(new_field);
            possible_field.setstoneat(col,my_player_no == 1 ? 2 : 1);
            prediction_threads.push_back(boost::thread (&predict_response, this, possible_field));
        }
        return slot; //selection->first;
    }
};



#endif //CPP16_EX8_CON4_CPU
