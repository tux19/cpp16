//
// Created by HEAD on 18.12.2016.
//

#include "limitedstack.h"
#include "unlimitedstack.h"
#include <iostream>
#include <stack>
int main(){
    int array[] = { 34, 77, 16, 2 };

    std::stack<int> myStack;
    for(int i=0; i < 4; i++){
        myStack.push(array[i]);
    }

    limitedstack<int> ls(myStack);
    unlimitedstack<int> us(myStack);

    for(int j=0; j<255; j++){
        ls.push(j);
        us.push(j);
    }
    std::cout << "Limited stack top element:" << ls.top() << std::endl;
    std::cout << "Unlimited stack top element:" << us.top() << std::endl;
    return 0;
}