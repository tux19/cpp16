//
// Created by HEAD on 19.12.2016.
//

#ifndef CPP16_CONSTDECONST_H
#define CPP16_CONSTDECONST_H
#include <iostream>

class constdeconst {
public:
    constdeconst(){
        std::cout << "Super constructor called" << std::endl;
    }
    ~constdeconst(){
        std::cout << "Super destructor called" << std::endl;
    }
};
class subconstdeconst : public constdeconst {
public:
    subconstdeconst(){
        std::cout << "Sub constructor called" << std::endl;
    }
    ~subconstdeconst(){
        std::cout << "Sub deconstructor called" << std::endl;
    }
};

#endif //CPP16_CONSTDECONST_H
