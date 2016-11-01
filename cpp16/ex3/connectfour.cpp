#include "playfield.h"
#include <iostream>
#include <future>
/*

   |1|2|3|4|5|6|7| y
   | | | | | | | |  
   | | | | | | | | 
   | | | | | | | |
   | | | | | | | |
   | | | | | | | |
   | | | | | | | | 
   x->
*/

template<typename F>
class player {
public:
	player();
	
 // returns the column where the player decides to throw in his
 // stone
 // F is the playfield which may be any playfield implementing
 // the stoneat method, if you expect a different class because
 // you need methods to verify whether the opponent can win,
 // copy the field into the class that you expect.
 int play(const F &field);
};

using namespace std;

void playfield::stoneset(int x, int y, int toSet){
	playfield::rep[x][y] = toSet;
	return;
}
int playfield::checkwinnerhorizontal(){
	int player = playfield::currentplayer;
	for(int x=0;x<playfield::width;x++){
		for(int y=0;y<playfield::height-3;y++){	
				if(playfield::stoneat(x,y) == player && playfield::stoneat(x,y+1) == player && playfield::stoneat(x,y+2)== player && playfield::stoneat(x,y+3) == player){
					return player;
				}
		}
	}
	return 0;
}
int playfield::checkwinnervertical(){
	int player = playfield::currentplayer;
	for(int y=0;y<playfield::height;y++){
		for(int x=0;x<playfield::width-3;x++){
				if(playfield::stoneat(x,y) == player && playfield::stoneat(x+1,y) == player && playfield::stoneat(x+2,y)== player && playfield::stoneat(x+3,y) == player){
					return player;
				}
		}		
	}
	return 0;
}
int playfield::checkwinnerdiagonal1(){
	int player = playfield::currentplayer;
	for(int y=0;y<playfield::height-3;y++){
		for(int x=0;x<playfield::width-3;x++){
				if(playfield::stoneat(x,y) == player && playfield::stoneat(x+1,y+1) == player && playfield::stoneat(x+2,y+2)== player && playfield::stoneat(x+3,y+3) == player){
					return player;
				}
		}		
	}
	return 0;
}
int playfield::checkwinnerdiagonal2(){
	int player = playfield::currentplayer;
	for(int y=0;y<playfield::height-3;y++){
		for(int x=0;x<playfield::width-3;x++){
				if(playfield::stoneat(x,y) == player && playfield::stoneat(x-1,y+1) == player && playfield::stoneat(x-2,y+2)== player && playfield::stoneat(x-3,y+3) == player){
					return player;
				}
		}		
	}
	return 0;
}

                
int playfield::checkwinner(){
	int player = playfield::currentplayer;
	//Just check for the player who put in the last stone
	if(playfield::checkwinnervertical() !=0 ||
	playfield::checkwinnerhorizontal() !=0||
	playfield::checkwinnerdiagonal1() !=0 ||
	playfield::checkwinnerdiagonal2() !=0){
		playfield::winner = player;
	}else{
		if(playfield::stoneat(0,0) !=0 && 
		playfield::stoneat(1,0) !=0 && 
		playfield::stoneat(2,0) !=0 && 
		playfield::stoneat(3,0) !=0 && 
		playfield::stoneat(4,0) !=0 && 
		playfield::stoneat(5,0) !=0 && 
		playfield::stoneat(6,0) !=0 )
		{
			playfield::winner = 3;
		}
		}
	return playfield::winner;
}

playfield::playfield(){
		for(int i=0;i<playfield::width;i++){
			for(int j=0;j<playfield::height;j++){
				stoneset(i,j,0);
			}
		}
}


void playfield::nextplayer(){
	if(playfield::currentplayer == 1){
		playfield::currentplayer = 2;
	}else{
		playfield::currentplayer = 1;
	}
}
 int playfield::gravity(int x,int y){ //Return 1 if illegal move (column full)
 	if(playfield::stoneat(x,y) != 0){
 		return 1;
	 }
	if( y < playfield::height && playfield::stoneat(x,y+1) == 0 ){
		playfield::gravity(x,y+1);
	}else{
		if(y==6){y--;}
		playfield::stoneset(x,y,currentplayer);
		return 0;
	}
	playfield::stoneat(x,y);
	return 0;
}


void playfield::drawfield(){
	for(int y=0;y<playfield::height;y++){
		for(int x=0;x<playfield::width;x++){
			cout <<"|"<< playfield::stoneat(x,y)<"|";

			}
				cout << endl;
		}
}

void playGame(/*player<T> player1, player<T> player2*/){
	playfield game;
	int input;
	game.drawfield();
	while(game.winner == 0){
	if(player1 != 0 | player2!= 0){ //If we have only Computerplayers
		
	}else{ // If we have human players:
		cout << "Player "<< game.currentplayer << " please enter in which column you want to put your stone (0-6):"<< endl;
		cin >> input;
		while(input > 7 || input < 0){
			cout << "Wrong input" << endl;
		cin.clear();	
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
			cout << "Enter again:" << endl;
			cin >> input ;
		}
		while(game.gravity(input,0) != 0){
		 cout << "Illegal move" << endl;
		cin.clear();	
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		 cin >> input;
			while(input > 7 || input < 0){
				cout << "Wrong input" << endl;
				cout << "Enter again:" << endl;
				cin.clear();	
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> input;
			}
		}
	}
	auto myFuture = std::async(std::launch::async, &playfield::checkwinner, &game); //Wait for the check to complete before skipping to nextplayer();
	int winner = myFuture.get();
	game.nextplayer();
	game.drawfield();
	}
	if(game.winner != 0 && game.winner != 3){
		cout << "Congrats player" << game.winner << endl;
	}else if(game.winner == 3){
		cout << "Looks like a draw" << endl;
	}
	
}

// Intialize game array with 0s
// Loop:Return which player starts
//  Read inputs
// UpdateGameView
// Determine winner

int main(){
	playGame();
	return 0;
}
