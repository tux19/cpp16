
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

struct Base{
    virtual void print() = 0;
};

struct Derived1 : public Base{
    void print(){
        std::cout << "Derived1" << std::endl;
    }
};

struct Derived2 : public Base{
    void print(){
        std::cout << "Derived2" << std::endl;
    }
};
