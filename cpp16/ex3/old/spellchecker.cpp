
#include "spellchecker.h"
#include <iostream>
#include <fstream>
#include <algorithm> //std::replace
#include <set>
#include <string>
#include "pset.h"
#include "pvector.h"

using namespace std;

void spellchecker::replace_word(pvector<string>& tV,const string &w,const string &newWord){replace(tV.begin(),tV.end(),w,newWord);}
void spellchecker::add_word(pset<string>& dV,const string& w){dV.insert(w);}


void spellchecker::loadtext(pvector<std::string>& tV,std::string filename){
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
void spellchecker::writetext(vector<std::string> tV,std::string const &filename){
	 ofstream myfile(filename);
 	 if (myfile.is_open()) {
	 	for(vector<string>::iterator word = tV.begin(); word != tV.end(); ++word){ 
	    myfile << *word<<" "; 
		}
		myfile.close();
	}
}

void spellchecker::loaddict(set<std::string> *tV,std::string filename){
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
void spellchecker::writedict(std::set<std::string> tV,std::string const &filename){
	 ofstream myfile(filename);
 	 if (myfile.is_open()) {
	 	for(set<string>::iterator word = tV.begin(); word != tV.end(); ++word){ 
	    myfile << *word<<" "; 
		}
		myfile.close();
	}
}

void spellchecker::check_dict(pset<string>& dictV, pvector<string>& textV){
	for(vector<string>::iterator word = textV.begin(); word != textV.end(); ++word){
		bool inDict = false;
		for(set<string>::iterator dictword = dictV.begin(); dictword != dictV.end(); ++dictword){
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
					add_word(dictV,*word);
				break;
				case 'i':
				break;
				case 'r':
					string newWord;
					cout << "Enter replacement word: ";
					getline(cin,newWord);
					replace_word(textV,*word,newWord);
				break;
			}
		}
	}
	
		
}


int spellchecker::run(std::string dict, std::string txt){

	string filename1 = dict;//Dict
	string filename2 = txt;//Text
	pvector<string> text(txt);
	pset<string> dictS(dict);


	check_dict(dictS,text);
	filename2 += ".corrected";

	pset<string> dictC(filename2,dictS);

	return 0;
}
