//
// Created by Christian Ott on 22.01.2017.
//

#ifndef CPP16_CPU_PLAYFIELD_H
#define CPP16_CPU_PLAYFIELD_H

#include <array>
#include <assert.h>
#include <vector>
#include <bits/unique_ptr.h>
#include "playfield.h"
using field_array =std::array<std::array<int, playfield::height>, playfield::width>;

class cpu_playfield : public playfield {
    field_array _field; 
public:
    cpu_playfield() : playfield() {
        for(int i = 0; i < width; ++i) {
            for (int j = 0; j < height; j++) {
                _field[i][j] = playfield::none;
            }
        }
    }

    void setstoneat(int x, int y, int player_no){
        _field[x][y] = player_no;
    }

    void setstoneat(int col, int player_no) {
        for(int r = playfield::height - 1; r >= 0; --r) {
            if(stoneat(col,r) == playfield::none) {
                setstoneat(col, r, player_no);
                break;
            }
        }
    }
    // copy constructor
    cpu_playfield(const playfield &f){
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; j++) {
                _field[i][j] = f.stoneat(i,j);
            }
        }
    }

    // assignment operator
    cpu_playfield& operator=(playfield &f){
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; j++) {
                _field[i][j] = f.stoneat(i,j);
            }
        }
        return *this;
    }

    // assignment operator
    bool operator==(const playfield &f){
        bool res = true;
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; j++) {
                if(_field[i][j] != f.stoneat(i,j)){
                    res = false;
                }
            }
        }
        return res;
    }
    bool check_win(int player_no) const {

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

    bool is_empty() const{
        bool is_empty = true;
        for(auto c : _field ){
            for(auto r : c){
                if(r != playfield::none){
                    is_empty = false;
                }
            }
        }
        return is_empty;
    }

    bool check_full()const {
        bool isFull = true;

        for(int i = 0; i < width && isFull; ++i) {
            for(int j = 0; j < height && isFull; j++) {
                if(stoneat(i,j) == playfield::none) {
                    isFull = false;
                }
            }
        }

        return isFull;
    }

    std::unique_ptr<std::vector<int>> actions() const{
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
// destructor
    ~cpu_playfield(){

    }
    int stoneat(int x, int y) const {
        return this->_field[x][y];
    }
};
#endif //CPP16_CPU_PLAYFIELD_H
