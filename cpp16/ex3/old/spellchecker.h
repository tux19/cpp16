
#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "pvector.h"
#include "pset.h"

class spellchecker{
    void replace_word(pvector<std::string>& tV,const std::string &w,const std::string &newWord);
    void add_word(pset<std::string>& dV, const std::string &w);
    void check_dict(pset<std::string>& dictV, pvector<std::string>& textV);
    void writetext(std::vector<std::string> tV,std::string const &filename);
    void loadtext(std::vector<std::string> *tV,std::string filename);
    void loaddict(std::set<std::string> *tV,std::string filename);
    void writedict(std::set<std::string> tV,std::string const &filename);

public:
    int run(std::string dict, std::string txt);
};

#endif
