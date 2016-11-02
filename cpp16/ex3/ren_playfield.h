#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

class ren_playfield {
public:
    // size of the field
    const static int width = 7;
    const static int height = 6;

    // the elements stored at individual field positions
    const static int none = 0;
    const static int player1 = 1;
    const static int player2 = 2;

    int currentplayer = 1; //Player 1 always starts the first game
    int winner = 0;
protected:
    // the internal representation of the field
    char rep[ren_playfield::width][ren_playfield::height];
public:
    ren_playfield();

    //returns the stone (none/player1/player2) at the position position(x,y)
    // 0 <= x <= width
    // 0 <= y <= height
    // stoneat(0,0) ... top left
    // stoneat(width-1, height-1) .. bottom right
    // if we insert a stone in a new game in column i,
    // it lands at (i,height-1)
	void stoneset(int x, int y, int toSet);
	int gravity(int x, int y); //returns if move is legal
	void drawfield(); //console output
	int checkwinner(); // sets winner => 0:no winner 1:player1 2:player2 3:draw
		int checkwinnervertical();
		int checkwinnerhorizontal();
		int checkwinnerdiagonal1();
		int checkwinnerdiagonal2();

	void resetfield(); // reset rep[][]
	void nextplayer();
    int stoneat(int x, int y) const { return rep[x][y]; }

    ~ren_playfield() {

    }
};

#endif
