/*
 * computer.h
 *
 *  Created on: 13.11.2013
 *      Author: rko
 */

#include "rkoch_ai.h"
#include "../playfield.h"

using std::cin;
using std::cout;
using std::endl;

 int rkoch_ai::play(const playfield &field) {
    // That was playfield::player1 but the linker could not find those symbols? Strange C++!!
    int player_number = find_player_number(field);
    int enemy = (player_number == 1 ? 2 : 1);

    // Check if computer could win
    for (int x = 0; x < playfield::width; x++) {
        for (int y = 0; y < playfield::height; y++) {

            // Check  horizontal
            if ((x + 2 < playfield::width) && (field.stoneat(x, y) == player_number) && (field.stoneat(x + 1, y) == player_number) && (field.stoneat(x + 2, y) == player_number)) {
                if ((x + 3 < playfield::width) && (field.stoneat(x + 3, y) == 0) && ((y == playfield::height - 1) || (field.stoneat(x + 3, y - 1) != 0))) {
                    const int res = x + 3;
                    return res;
                }

                if ((x > 0) && (field.stoneat(x - 1, y) == 0) && ((y == playfield::height - 1) || (field.stoneat(x - 1, y - 1) != 0))) {

                    const int res = x - 1;
                    return res;
                }
            }

            // Check vertical
            if ((y + 2 < playfield::height) && (field.stoneat(x, y) == player_number) && (field.stoneat(x, y + 1) == player_number) && (field.stoneat(x, y + 2) == player_number)) {
                if ((y > 0) && (field.stoneat(x, y - 1) == 0)) {
                    const int res = x;
                    return res;
                }
            }

            // Check diagonal (top-left to bottom-right)
            if ((x + 2 < playfield::width) && (y + 2 < playfield::height) && (field.stoneat(x, y) == player_number) && (field.stoneat(x + 1, y + 1) == player_number)
                && (field.stoneat(x + 2, y + 2) == player_number)) {
                if ((x + 3 < playfield::width) && (y + 3 < playfield::width) && (field.stoneat(x + 3, y + 3) == 0)
                    && ((y + 3 == playfield::height - 1) || (field.stoneat(x + 3, y + 4) != 0))) {
                    const int res = x + 3;
                    return res;
                }

                if ((x > 0) && (y > 0) && (field.stoneat(x - 1, y - 1) == 0) && (field.stoneat(x - 1, y) != 0)) {
                    const int res = x - 1;
                    return res;
                }
            }

            // Check diagonal (bottom-left to top-right)
            if ((x + 2 < playfield::width) && (y - 2 >= 0) && (field.stoneat(x, y) == player_number) && (field.stoneat(x + 1, y - 1) == player_number)
                && (field.stoneat(x + 2, y - 2) == player_number)) {
                if ((x + 3 < playfield::width) && (y - 3 >= 0) && (field.stoneat(x + 3, y - 3) == 0) && (field.stoneat(x + 3, y - 2) != 0)) {
                    const int res = x + 3;
                    return res;
                }

                if ((x > 0) && (y < playfield::height - 1) && (field.stoneat(x - 1, y + 1) == 0) && ((y + 2 == playfield::height) || (field.stoneat(x - 1, y + 2) != 0))) {
                    const int res = x - 1;
                    return res;
                }
            }
        }
    }

    // Check if enemy has 2 or more stones next to each other -> haunt him
    for (int x = 0; x < playfield::width; x++) {
        for (int y = 0; y < playfield::height; y++) {

            // Check horizontal
            if ((x + 1 < playfield::width) && (field.stoneat(x, y) == enemy) && (field.stoneat(x + 1, y) == enemy)) {
                if ((x + 2 < playfield::width) && (field.stoneat(x + 2, y) == 0) && ((y == playfield::height - 1) || (field.stoneat(x + 2, y - 1) != 0))) {
                    const int res = x + 2;
                    return res;
                }

                if ((x > 0) && (field.stoneat(x - 1, y) == 0) && ((y == playfield::height - 1) || (field.stoneat(x - 1, y - 1) != 0))) {
                    const int res = x - 1;
                    return res;
                }
            }

            // Check vertical
            if ((y + 1 < playfield::height) && (field.stoneat(x, y) == enemy) && (field.stoneat(x, y + 1) == enemy)) {
                if ((y > 0) && field.stoneat(x, y - 1) == 0) {
                    const int res = x;
                    return res;
                }
            }

            // Check diagonal (top-left to bottom-right)
            if ((x + 1 < playfield::width) && (y + 1 < playfield::height) && (field.stoneat(x, y) == enemy) && (field.stoneat(x + 1, y + 1) == enemy)) {
                if ((x + 2 < playfield::width) && (y + 2 < playfield::height) && (field.stoneat(x + 2, y + 2) == 0)
                    && ((y + 3 == playfield::height - 1) || (field.stoneat(x + 2, y + 3) != 0))) {
                    const int res = x + 2;
                    return res;
                }

                if ((x > 0) && (y > 0) && (field.stoneat(x - 1, y - 1) == 0) && (field.stoneat(x - 1, y) != 0)) {
                    const int res = x - 1;
                    return res;
                }
            }

            // Check diagonal (bottom-left to top-right)
            if ((x + 1 < playfield::width) && (y - 1 >= 0) && (field.stoneat(x, y) == enemy) && (field.stoneat(x + 1, y - 1) == enemy)) {
                if ((x + 2 < playfield::width) && (y - 2 >= 0) && (field.stoneat(x + 2, y - 2) == 0) && (field.stoneat(x + 2, y - 1) != 0)) {
                    const int res = x + 2;
                    return res;
                }

                if ((x > 0) && (y < playfield::height - 1) && (field.stoneat(x - 1, y + 1) == 0) && ((y + 2 == playfield::height) || (field.stoneat(x - 1, y + 2) != 0))) {
                    const int res = x - 1;
                    return res;
                }
            }
        }
    }

    // Default behavior: return a random stone
     const int res = rand() % playfield::width;
     return res;
}

int rkoch_ai::find_player_number(const playfield &field) {
    int p1 = 0, p2 = 0;

    for (int x = 0; x < playfield::width; x++) {
        for (int y = 0; y < playfield::height; y++) {
            int stone = field.stoneat(x, y);
            if (stone == 1) {
                p1++;
            } else if (stone == 2) {
                p2++;
            }
        }
    }

    if (p1 == p2) {
        // players stones are evenly distributed, I am player 1
        return 1;
    } else {
        return 2;
    }
}