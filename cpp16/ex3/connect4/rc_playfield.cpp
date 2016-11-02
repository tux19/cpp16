//
// Created by Christian Ott on 02.11.2016.
//
#include <iostream>
#include <istream>
#include <ostream>

#include "rc_playfield.h"

// constructor, initialize field with none
sc_playfield::sc_playfield(){
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; j++) {
            field[i][j] = none;
        }
    }
}


void sc_playfield::setstoneat(int x, int y, int player_no){
    field[x][y] = player_no;
}


// copy constructor
sc_playfield::sc_playfield(const playfield &f){
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; j++) {
            field[i][j] = f.stoneat(i,j);
        }
    }
}

// assignment operator
sc_playfield& sc_playfield::operator=(playfield &f){
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; j++) {
            field[i][j] = f.stoneat(i,j);
        }
    }
    return *this;
}

// destructor
sc_playfield::~sc_playfield(){

}

// check if player has won with 4 horizontal stones
bool sc_playfield::check_horizontal(int player_no) {

    bool hasWon = false;
    int counter = 0;

    // for each row
    for(int r = 0; r < height && !hasWon; ++r) {

        // for each column
        for(int c = 0; c < width && !hasWon; ++c) {
            if(stoneat(c,r) == player_no) {
                ++counter;
            } else {
                counter = 0;
            }

            // if 4 stones in a row
            if(counter == 4) {
                hasWon = true;
            }
        }
        counter = 0;
    }

    return hasWon;
}

// check if player has won with 4 vertical stones
bool sc_playfield::check_vertical(int player_no) {

    bool hasWon = false;
    int counter = 0;

    // for each column
    for(int c = 0; c < width && !hasWon; ++c) {

        // for each row
        for(int r = 0; r < height && !hasWon; ++r) {
            if(stoneat(c,r) == player_no) {
                ++counter;
            } else {
                counter = 0;
            }

            if(counter == 4) {
                hasWon = true;
            }
        }
        counter = 0;
    }

    return hasWon;
}

// check if player has won with 4 diagonal stones
bool sc_playfield::check_diagonal(int player_no) {

    bool hasWon = false;
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
    int startCol = 0;
    // for every possible start col
    for(startCol = 0; startCol < width-4; startCol++){
        for(int start_row = 3; start_row < height; start_row++){
            for (int h = 0 ; h < 4; ++h) {
                if(stoneat(startCol + h,start_row - h) == player_no) {
                    ++counter;
                } else {
                    counter = 0;
                }

                if(counter == 4) {
                    hasWon = true;
                }
            }

        }
    }
    for(startCol = width - 1; startCol >= 3; startCol--){
        for(int start_row = 3; start_row < height; start_row++){
            for (int h = 0 ; h < 4; ++h) {
                if(stoneat(startCol - h,start_row - h) == player_no) {
                    ++counter;
                } else {
                    counter = 0;
                }

                if(counter == 4) {
                    hasWon = true;
                }
            }
        }
    }
    return hasWon;
}
bool sc_playfield::check_win(int player_no) {

    bool hasWon = false;

    hasWon = check_horizontal(player_no);

    if(!hasWon) {
        hasWon = check_vertical(player_no);
    }

    if(!hasWon) {
        hasWon = check_diagonal(player_no);
    }

    return hasWon;
}

bool sc_playfield::check_full() {
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

void sc_playfield::print_field(){
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