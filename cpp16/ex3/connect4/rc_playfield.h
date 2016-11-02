//
// Created by Christian Ott on 02.11.2016.
//

#ifndef CPP16_SC_PLAYFIELD_H
#define CPP16_SC_PLAYFIELD_H
#include "playfield.h"

class sc_playfield : public playfield {

public:
    // constructor
    sc_playfield();

    void setstoneat(int x, int y, int playerNo);

    // copy constructor
    sc_playfield(const playfield &field);

    // assignment operator
    sc_playfield& operator=(playfield &field);

    // destructor
    ~sc_playfield();


    bool checkHorizontal(int playerNo);
    bool checkVertical(int playerNo);
    bool checkDiagonal(int playerNo);
    bool checkWin(int playerNo);
    bool checkFull();
    void printField();

};
#endif //CPP16_SC_PLAYFIELD_H
