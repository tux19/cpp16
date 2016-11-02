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


void sc_playfield::setstoneat(int x, int y, int playerNo){
    field[x][y] = playerNo;
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
bool sc_playfield::checkHorizontal(int playerNo) {

    bool hasWon = false;
    int counter = 0;

    // for each row
    for(int r = 0; r < height && !hasWon; ++r) {

        // for each column
        for(int c = 0; c < width && !hasWon; ++c) {
            if(stoneat(c,r) == playerNo) {
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
bool sc_playfield::checkVertical(int playerNo) {

    bool hasWon = false;
    int counter = 0;

    // for each column
    for(int c = 0; c < width && !hasWon; ++c) {

        // for each row
        for(int r = 0; r < height && !hasWon; ++r) {
            if(stoneat(c,r) == playerNo) {
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
bool sc_playfield::checkDiagonal(int playerNo) {

    bool hasWon = false;
    int counter = 0;

    /*
     *      /
     *     //
     *    ///
     * 3 ///
     * 4 //
     * 5 /
     *   0123456
     */

    int startCol = 0;

    // for row 3, 4, 5
    for(int h = 3; h < height; ++h) {
        // start at (0,3), then (1,2), (2,1), (3,0)
        for(int currentHeight = h; currentHeight >= 0 && startCol < width; --currentHeight) {
            if(stoneat(startCol,currentHeight) == playerNo) {
                ++counter;
            } else {
                counter = 0;
            }

            if(counter == 4) {
                hasWon = true;
            }

            ++startCol;
        }
        counter = 0;
        startCol = 0;
    }


    /*
     * 0  ///////
     * 1  ///////
     * 2  //////
     * 3  /////
     * 4  ////
     * 5  ///
     *   0123456
     */

    startCol = 1;

    // do the following for startCol = 1,2,3
    for(int w = 1; w < 4; ++w) {

        // start at (1,5), then (2,4), (3,3), (4,2)
        for(int currentHeight = height-1; currentHeight >= 0 && startCol < width; --currentHeight) {
            if(stoneat(startCol,currentHeight) == playerNo) {
                ++counter;
            } else {
                counter = 0;
            }

            if(counter == 4) {
                hasWon = true;
            }

            ++startCol;
        }
        counter = 0;
        startCol = w;
    }


    /*
     * 0  \\\
     * 1   \\\
     * 2    \\\
     * 3     \\\
     * 4      \\
     * 5       \
     *   0123456
     */

    startCol = 6;

    for(int h = 3; h < height; ++h) {
        for(int hh = h; hh >= 0 && startCol >= 0; --hh) {
            if(stoneat(startCol,hh) == playerNo) {
                ++counter;
            } else {
                counter = 0;
            }

            if(counter == 4) {
                hasWon = true;
            }

            --startCol;
        }
        counter = 0;
        startCol = 6;
    }

    startCol = 5;

    for(int w = 5; w > 2; --w) {
        for(int hh = height-1; hh >= 0 && startCol >= 0; --hh) {
            if(stoneat(startCol,hh) == playerNo) {
                ++counter;
            } else {
                counter = 0;
            }

            if(counter == 4) {
                hasWon = true;
            }

            --startCol;
        }
        counter = 0;
        startCol = w;
    }

    return hasWon;
}
bool sc_playfield::checkWin(int playerNo) {

    bool hasWon = false;

    hasWon = checkHorizontal(playerNo);

    if(!hasWon) {
        hasWon = checkVertical(playerNo);
    }

    if(!hasWon) {
        hasWon = checkDiagonal(playerNo);
    }

    return hasWon;
}

bool sc_playfield::checkFull() {
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

void sc_playfield::printField(){
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