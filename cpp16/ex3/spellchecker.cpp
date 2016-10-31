#include "../ex2/pvector.h"
#include <iostream>

using namespace std;

replace_word(string w,const string &newWord){}
add_word(string w){}

int main(int argc, char* argv[]){

/*	if(argc < 2){
		cout << "Example use:spellchecker.exe dictionary.txt text.txt" << endl;
		return 0;
	}
*/
	//Vector not working as intended
/*	pvector<string> dict(argv[1]);
	pvector<string> text(argv[2]);*/
	
	string dict[] = {"correctly", "spelled", "words", "are", "stored", "in", "this", "dictionary", "file"};
	string text[] = {"A", "comprehensive", "dictionary", "is", "important"};
	int i = 0;
	int j = 0;

	for(const string &word: text){ //Iterate through text
		j=0;
				bool inDict = false;
				do{
					if(dict[j].compare(word)== 0){
						inDict = true;
					}
					j++;
				}while(!inDict && j<9);
				
			if(!inDict){
				cout << word << endl;
				cout << "(a)dd, (i)gnore, (r)eplace?";
				string input;
				getline(cin,input);
				switch(input[0]){
					case 'a':
						add_word(word);
					break;
					case 'i':						
					break;
					case 'r':
						string newWord;
						getline(cin,newWord);
						replace_word(word,newWord);
					break;	
				}
			}
		}
	

	
	
	return 0;
}
