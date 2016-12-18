//
// Created by HEAD on 17.11.2016.
//
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>



int main(){
    std::vector<std::string*> numbers;
    numbers.push_back(new std::string(""));
    numbers.push_back(new std::string("yadda yaddad"));
    numbers.push_back(new std::string("three programmers had"));
    numbers.push_back(new std::string(""));
    std::vector<bool> empty (numbers.size());
    transform( numbers.begin(),numbers.end(),empty.begin(), std::mem_fun(&std::string::empty));
    for(std::vector<bool>::iterator it = empty.begin(); it != empty.end(); it++){
        std::cout << "Is string empty? " << *it << std::endl;
    }
    return 0;

}