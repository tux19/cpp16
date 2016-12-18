//
// Created by HEAD on 18.12.2016.
//

#ifndef CPP16_UNLIMITEDSTACK_H
#define CPP16_UNLIMITEDSTACK_H

#endif //CPP16_UNLIMITEDSTACK_H
#include "limitedstack.h"

template <typename T>
class unlimitedstack
        : public limitedstack<T>{

public:
    unlimitedstack(std::stack<T> stack): limitedstack<T>(stack) {}
    virtual void push(T e){
        limitedstack<T>::s.push(e);
    }
};