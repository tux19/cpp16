#ifndef CPP16_EX6_CON4_INTEROP_MY_PLAYFIELD_H
#define CPP16_EX6_CON4_INTEROP_MY_PLAYFIELD_H

#include <assert.h>
#include "playfield.h"

class my_playfield : public playfield {
    // the internal representation of the field -- may be changed
    int field[ playfield::width][ playfield::height];
public:
    // constructor
    my_playfield();

    void setstoneat(int x, int y, int player_no);

    // copy constructor
    my_playfield(const playfield &field);

    // assignment operator
    my_playfield& operator=(playfield &field);

    // destructor
    ~my_playfield();


    bool check_horizontal(int player_no);
    bool check_vertical(int player_no);
    bool check_diagonal(int player_no);
    bool check_win(int player_no);
    bool check_full();
    void print_field();
    virtual int stoneat(int x, int y) const {
        assert(x < playfield::width && y < playfield::height);
        return field[x][y];}
};
#endif //CPP16_EX6_CON4_INTEROP_MY_PLAYFIELD_H
