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

using namespace std;

void playfield::stoneset(int x, int y, int toSet){
	playfield::rep[x][y] = toSet;
	return;
}
int playfield::checkforwinnervertically(){
	int player = playfield::currentplayer;

	for(int y=0;y<playfield::height;y++){
		for(int x=0;x<playfield::width-3;x++){	
		cout << "Vchecking:" << x << "|" << y << endl;
				if(playfield::stoneat(x,y) == player && playfield::stoneat(x+1,y) == player && playfield::stoneat(x+2,y)== player && playfield::stoneat(x+3,y) == player){
					
					return player;
				}else{
					return 0;
				}
			}
	}
	return 0;
}
int playfield::checkforwinnerhorizontally(){
	int player = playfield::currentplayer;

	for(int x=0;x<playfield::width;x++){	
		for(int y=0;y<playfield::height-3;y++){
			cout << "Vchecking:" << x << "|" << y << endl;
				if(playfield::stoneat(x,y) == player && playfield::stoneat(x,y+1) == player && playfield::stoneat(x,y+2)== player && playfield::stoneat(x,y+3) == player){
					cout << "Hchecking:" << x << "|" << y << endl;
					return player;
				}else{
					return 0;
				}
			}
	}
	return 0;
}

int playfield::checkforwinner(){
	int player = playfield::currentplayer;
	//Just check for the player who put in the last stone
	if(playfield::checkforwinnervertically() !=0 ||
	playfield::checkforwinnerhorizontally() !=0/*||
	playfield::checkforwinnerdiagonal1() !=0 ||
	playfield::checkforwinnerdiagonal2() !=0*/){
		playfield::winner = player;
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
			cout << "Set "<<x <<"|" <<  y << endl;
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
	cin.clear();	
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
		cout << "Enter again:" << endl;
		cin >> input;
	}
	if(game.gravity(input,0) != 0){
	 cout << "Illegal move" << endl;
	cin.clear();	
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 cin >> input;
		while(input > 7 || input < 0){
			cout << "Wrong input" << endl;
			cout << "Enter again:" << endl;
			cin.clear();	
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> input; //Check Gravity!
		}
	} 
	auto myFuture = std::async(std::launch::async, &playfield::checkforwinner, &game); //Wait for the check to complete before skipping to nextplayer();
	int winner = myFuture.get();
	game.nextplayer();
	game.drawfield();
	}
	if(game.winner != 0){
		cout << "Congrats player " << game.winner << endl;
	}else{
		cout << "looks like a draw" << endl;
	}
	
	return 0;
}
