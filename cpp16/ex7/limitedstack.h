//
// Created by HEAD on 18.12.2016.
//

#ifndef CPP16_LIMITEDSTACK_H
#define CPP16_LIMITEDSTACK_H
#include <stack>
#include <iostream>

template <typename T>
class limitedstack{
private:
    int limit = 255;

public:
    std::stack<T> s;
    limitedstack(std::stack<T> stack):s(stack){};
    virtual void push(T e){
        if(s.size() < limit) {
            s.push(e);
        }else{
            std::cout << "Limit of 255 exceeded" << std::endl;
        }
    }
    void pop(){
        return s.pop();
    }
    T top(){
        return s.top();
    }

};



#endif //CPP16_LIMITEDSTACK_H
