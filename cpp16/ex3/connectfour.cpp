#include "playfield.h"
#include <iostream>
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

using namespace std;

void playfield::stoneset(int x, int y, int toSet){
	playfield::rep[x][y] = toSet;
	return;
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
	if( x < playfield::height && playfield::stoneat(x+1,y) == 0 ){
		playfield::gravity(x+1,y);
	}else{
		playfield::stoneset(x,y,currentplayer);
		return 0;
	}
	playfield::stoneat(x,y);
	return 0;
}


void playfield::drawfield(){
	for(int i=0;i<playfield::width;i++){
			for(int j=0;j<playfield::height;j++){
				cout <<"|"<< playfield::stoneat(i,j)<"|";
			}
				cout << endl;
		}
}

// Intialize game array with 0s
// Loop:Return which player starts
//  Read inputs
// UpdateGameView
// Determine winner


int main(){
	playfield game;
	int input;
	game.drawfield();
	while(game.winner == 0){
	cout << "Player "<< game.currentplayer << "please enter in which column you want to put your stone:"<< endl;
	cin >> input;
	while(input > 7 || input < 0){
		cout << "Wrong input" << endl;
		cout << "Enter again:" << endl;
		cin >> input;
	}
	while(game.gravity(0,input) != 0){
	 cout << "Illegal move" << endl;
	 cin >> input;
		while(input > 7 || input < 0){
			cout << "Wrong input" << endl;
			cout << "Enter again:" << endl;
			cin >> input;
		}
	} 
	
	game.nextplayer();
	game.drawfield();
	}
	
	
	return 0;
}
