#include <iostream>
#include <vector>
#include <set>

#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H
void replace_word(std::vector<std::string> *tV,const std::string &w,const std::string &newWord);
void add_word(std::set<std::string> *dV,std::string w);
void check_dict(std::vector<std::string> dictV, std::vector<std::string> textV);
void writetext(std::vector<std::string> tV,std::string const &filename);
void loadtext(std::vector<std::string> *tV,std::string filename);
#endif

