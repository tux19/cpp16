#include "../ex2/pvector.h"
#include "spellchecker.h"
#include <iostream>
#include <algorithm> //std::replace
#include <vector>

using namespace std;

void replace_word(vector<string> tV, const string &w, const string &newWord) {
    replace(tV.begin(), tV.end(), w, newWord);
}

void add_word(vector<string> dV, string w) { dV.push_back(w); }

void write_textcorrected(string dest) {
    dest.append(".corrected");
}

void check_dict(vector<string> dictV, vector<string> textV) {
    for (vector<string>::iterator word = textV.begin(); word != textV.end(); ++word) {
        bool inDict = false;
        for (vector<string>::iterator dictword = dictV.begin(); dictword != dictV.end(); ++dictword) {
            if (*dictword == *word) {

                inDict = true;
                break;
            }
        }
        if (!inDict) {
            cout << *word << endl;
            cout << "(a)dd, (i)gnore, (r)eplace?";
            string input;
            getline(cin, input);
            switch (input[0]) {
                case 'a':
                    add_word(dictV, *word);
                    break;
                case 'i':
                    break;
                case 'r':
                    string newWord;
                    getline(cin, newWord);
                    replace_word(textV, *word, newWord);
                    break;
            }
        }
    }

}


int main(int argc, char *argv[]) {

/*	if(argc < 2){
		cout << "Example use:spellchecker.exe dictionary.txt text.txt" << endl;
		return 0;
	}*/

    //Vector not working as intended
/*	pvector<string> dictV(argv[1]);
	pvector<string> textV(argv[2]);*/
    vector<string> dictV;
    vector<string> textV;
    //Temporary workaround
    string dict[] = {"correctly", "spelled", "words", "are", "stored", "in", "this", "dictionary", "file"};
    string text[] = {"A", "comprehensive", "dictionary", "is", "important"};
    for (const string &word:text) {
        textV.push_back(word);
    }
    for (const string &word: dict) {
        dictV.push_back(word);
    }

    check_dict(dictV, textV);


    return 0;
}
