#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

class playfield {
public:
    // size of the field
    const static int width=7;
    const static int height=6;

    // the elements stored at individual field positions
    const static int none=0;
    const static int player1=1;
    const static int player2=2;
    
    int currentplayer = 1; //Player 1 always starts the first game
    int winner = 0;
	protected:
	// the internal representation of the field
	char rep[playfield::width][playfield::height];
	public:
	playfield();
    //returns the stone (none/player1/player2) at the position position(x,y)
    // 0 <= x <= width
    // 0 <= y <= height
    // stoneat(0,0) ... top left
    // stoneat(width-1, height-1) .. bottom right
    // if we insert a stone in a new game in column i,
    // it lands at (i,height-1)
	void stoneset(int x, int y, int toSet);
	int gravity(int x, int y); //Has to return if move was legal
	void drawfield();
	void checkforwinner();
	void nextplayer();
    int stoneat(int x, int y) const { return rep[x][y]; }
     ~playfield() {

    }
};
#endif
