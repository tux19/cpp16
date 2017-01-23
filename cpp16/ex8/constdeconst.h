//
// Created by HEAD on 19.12.2016.
//

#ifndef CPP16_CONSTDECONST_H
#define CPP16_CONSTDECONST_H
#include <iostream>

class base {
public:
    base(){
        std::cout << "base constructor called" << std::endl;
    }
    ~base(){
        std::cout << "base destructor called" << std::endl;
    }
};

class base2 {
public:
    base2(){
        std::cout << "base2 constructor called" << std::endl;
    }
    ~base2(){
        std::cout << "base2 destructor called" << std::endl;
    }
};


class deriv1 : public base {
public:
    deriv1(){
        std::cout << "child1 constructor called" << std::endl;
    }
    ~deriv1(){
        std::cout << "child1 deconstructor called" << std::endl;
    }
};

class deriv2 : public base, base2 {
public:
    deriv2(){
        std::cout << "child2 constructor called" << std::endl;
    }
    ~deriv2(){
        std::cout << "child2 deconstructor called" << std::endl;
    }
};


class deriv3 : public  base2, base {
public:
    deriv3(){
        std::cout << "child3 constructor called" << std::endl;
    }
    ~deriv3(){
        std::cout << "child3 deconstructor called" << std::endl;
    }
};
#endif //CPP16_CONSTDECONST_H
