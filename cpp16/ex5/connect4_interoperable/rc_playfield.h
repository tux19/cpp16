#ifndef CPP16_SC_PLAYFIELD_H
#define CPP16_SC_PLAYFIELD_H
#include "playfield.h"

class sc_playfield : public playfield {

public:
    // constructor
    sc_playfield();

    void setstoneat(int x, int y, int player_no);

    // copy constructor
    sc_playfield(const playfield &field);

    // assignment operator
    sc_playfield& operator=(playfield &field);

    // destructor
    ~sc_playfield();


    bool check_horizontal(int player_no);
    bool check_vertical(int player_no);
    bool check_diagonal(int player_no);
    bool check_win(int player_no);
    bool check_full();
    void print_field();

};
#endif //CPP16_SC_PLAYFIELD_H
