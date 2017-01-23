//
// Created by HEAD on 19.12.2016.
//

#include "spellchecker.h"
#include <iostream>
#include <regex>

void spellchecker::loadwords(std::string s) {
 this->words = s;
    std::cout << "Words:" << s << std::endl;
}
void spellchecker::loadregex(std::string regex) {
    std::regex newregex(regex);

    this->regexlist.push_back(newregex);
    std::cout << "Regex:" << regex << std::endl;
}
std::vector<std::string> spellchecker::checkwords() {
    std::vector<std::string> output;
    for(std::regex const& i: this->regexlist){
        std::sregex_iterator rit(this->words.begin(),this->words.end(),i);
        std::sregex_iterator rend;
        while(rit != rend){
            if(rit->str().size() > 0) {
                output.push_back(rit->str());
            }
            ++rit;
        }
    }

    return output;
}
void spellchecker::run() {
    std::cout << "Please enter your word string: (or press 1 for default string) :" << std::endl;
    std::string input;
    std::string regex;
    std::vector<std::string> output;
    std::getline(std::cin,input);
    if (input == "1") {
        input = "This is our sample dictionary that shall be matched.";
    }
    loadwords(input);

    std::cout<< "Please enter your regex: (or press 1 for default) :"<< std::endl;
    std::getline(std::cin,input);
    if(input == "1"){
        input = "([a-z]+)";
    }
    loadregex(input);
    while(input!= "0"){
        std::cout << "Would you like to add another regex? (or press 0 to exit)" << std::endl;
        std::getline(std::cin,input);
        loadregex(input);
    }


    output = checkwords();
    std::cout << "output size:" << output.size() << std::endl;
    for(std::vector<std::string>::iterator it = output.begin(); it != output.end(); it++){
        std::cout<< *it << std::endl;
    }

}
