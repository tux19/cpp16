
#include "spellchecker.h"
#include <iostream>
#include <fstream>
#include <algorithm> //std::replace
#include <set>
#include <string>

using namespace std;

void replace_word(vector<string> *tV,const string &w,const string &newWord){replace((*tV).begin(),(*tV).end(),w,newWord);}
void add_word(set<string> *dV,string w){(*dV).insert(w);}

void parse_cmdline(int argc, char *argv[])
{
    
}
void loadtext(vector<std::string> *tV,std::string filename){
	ifstream myReadFile;
	 myReadFile.open(filename);
	 char output[100];
	 if (myReadFile.is_open()) {
		 while (!myReadFile.eof()) {
	    myReadFile >> output;
	    (*tV).push_back(output);
		}
	}
}
void writetext(vector<std::string> tV,std::string const &filename){
	 ofstream myfile(filename);
 	 if (myfile.is_open()) {
	 	for(vector<string>::iterator word = tV.begin(); word != tV.end(); ++word){ 
	    myfile << *word<<" "; 
		}
		myfile.close();
	}
}

void loaddict(set<std::string> *tV,std::string filename){
	ifstream myReadFile;
	 myReadFile.open(filename);
	 char output[100];
	 if (myReadFile.is_open()) {
		 while (!myReadFile.eof()) {
	  	 myReadFile >> output;
	    (*tV).insert(output);
		}
	}
}
void writedict(std::set<std::string> tV,std::string const &filename){
	 ofstream myfile(filename);
 	 if (myfile.is_open()) {
	 	for(set<string>::iterator word = tV.begin(); word != tV.end(); ++word){ 
	    myfile << *word<<" "; 
		}
		myfile.close();
	}
}

void check_dict(set<string> *dictV, vector<string> *textV){
	for(vector<string>::iterator word = (*textV).begin(); word != (*textV).end(); ++word){ 
				bool inDict = false;
			for(set<string>::iterator dictword = (*dictV).begin(); dictword != (*dictV).end(); ++dictword){
				if(*dictword == *word){
					//cout << *dictword << " " << *word << endl;
					inDict = true;
				 	break;
				}
			}
			if(!inDict){
				cout << *word << endl;
				cout << "(a)dd, (i)gnore, (r)eplace?";
				string input;
				getline(cin,input);
				switch(input[0]){
					case 'a':
						add_word(&(*dictV),*word);
					break;
					case 'i':						
					break;
					case 'r':
						string newWord;
						getline(cin,newWord);
						replace_word(&(*textV),*word,newWord);
					break;	
				}
			}
		}
	
		
}


int main(int argc, char* argv[]){

	if(argc < 2){
		cout << "Example use:spellchecker.exe dictionary.txt text.txt" << endl;
		return 0;
	}
	string filename1 = argv[1];//Dict
	string filename2 = argv[2];//Text
	vector<string> text;
	set<string> dictS;
	loaddict(&dictS, filename1);
	loadtext(&text,filename2);
	/*string dict[] = {"correctly", "spelled", "words", "are", "stored", "in", "this", "dictionary", "file"};
	for(const string&word: dict){
		dictS.insert(word);
	}*/

	check_dict(&dictS, &text);
		filename2 += ".corrected";
	writetext(text,filename2);

	writedict(dictS,filename1);
	
	
	return 0;
}
