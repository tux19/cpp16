//
// Created by Christian Ott on 19.01.2017.
//

#ifndef CPP16_EX8_CON4_RETO
#define CPP16_EX8_CON4_RETO
    #include <string>
    #include <vector>
    #include "../playfield.h"
    #include "../player.h"

    class retos_computerplayer : public player
    {
    private:
        int boardcopy[7][6];
        int my_representation;
        int oponent_representation;

        bool checkwinning(int playerrepresentation);
        void copyboard(const playfield &field);
        bool updatecopyboard(int column, int playerrepresentation);
    public:
        retos_computerplayer() {};
        retos_computerplayer(int representation);
        retos_computerplayer(const retos_computerplayer& cp);
        virtual ~retos_computerplayer();

        virtual int play(const playfield &field);
};
#endif //CPP16_EX8_CON4_RETO
