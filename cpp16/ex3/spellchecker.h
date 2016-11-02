#include <iostream>
#include <vector>

#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

void replace_word(std::vector<string> tV, const std::string &w, const std::string &newWord);

void add_word(std::vector<string> dV, string w);

void check_dict(std::vector<string> dictV, std::vector<string> textV);

void write_textcorrected(std::string filename);

#endif

