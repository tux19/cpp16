#include <iostream>
#include <istream>
#include <ostream>

#include "my_playfield.h"

// constructor, initialize field with none
my_playfield::my_playfield(){
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; j++) {
            field[i][j] = none;
        }
    }
}


void my_playfield::setstoneat(int x, int y, int player_no){
    field[x][y] = player_no;
}


// copy constructor
my_playfield::my_playfield(const playfield &f){
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; j++) {
            field[i][j] = f.stoneat(i,j);
        }
    }
}

// assignment operator
my_playfield& my_playfield::operator=(playfield &f){
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; j++) {
            field[i][j] = f.stoneat(i,j);
        }
    }
    return *this;
}

// destructor
my_playfield::~my_playfield(){

}
//
bool my_playfield::check_win(int player_no) {

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

bool my_playfield::check_full() {
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

void my_playfield::print_field(){
    // Rows
    for(int r = 0; r < height; ++r) {

        // Columns
        for(int c = 0; c < width; ++c) {
            if(stoneat(c, r) == playfield::player1) {
                std::cout << "X";
            } else if(stoneat(c,r) == playfield::player2) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }
        }

        std::cout << "|" << std::endl;
    }

    for(int i = 0; i < width; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    for(int i = 0; i < width; i++) {
        std::cout << i;
    }
    std::cout << std::endl << std::endl;
}