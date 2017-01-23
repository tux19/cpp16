#ifndef CPP16_my_PLAYFIELD_H
#define CPP16_my_PLAYFIELD_H

#include <assert.h>
#include <array>
#include "playfield.h"
using field_array =std::array<std::array<int, playfield::height>, playfield::width>;

class my_playfield : public playfield {
    // the internal representation of the field -- may be changed
    field_array field;
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


    bool check_win(int player_no);
    bool check_full();
    void print_field();
    virtual int stoneat(int x, int y) const {
        assert(x < playfield::width && y < playfield::height);
        return field[x][y];}
};
#endif //CPP16_my_PLAYFIELD_H
