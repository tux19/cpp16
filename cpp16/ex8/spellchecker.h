//
// Created by HEAD on 19.12.2016.
//

#ifndef CPP16_SPELLCHECKER_H
#define CPP16_SPELLCHECKER_H
#include <iostream>
#include <string>
#include <iterator>
#include <regex>
class spellchecker {

    public:
       void loadwords(std::string string);
       void  loadregex(std::string string);
       std::vector<std::string> checkwords();
       void run();
    private:
    std::string words;
    std::vector<std::regex> regexlist;
};


#endif //CPP16_SPELLCHECKER_H
