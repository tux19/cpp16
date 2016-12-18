//
// Created by HEAD on 18.12.2016.
//
#include <iostream>
#include <vector>
#include <stack>

template<typename T>
void merge(std::vector<T> *dest, std::vector<T> *origin){
    std::copy(origin->begin(),origin->end(),std::back_inserter(*dest));
}

int main(){
    int list1[] = {0 ,1 ,2, 3};
    int list2[] = {5, 6,7,8};
    std::vector<int> vector;
    std::vector<int> vector1;
    for(int i: list1){
        vector.push_back(i);
    }
    for(int i: list2){
        vector1.push_back(i);
    }

    merge<int>(&vector1,&vector);
    for(int i: vector1){
        std::cout << i << std::endl;
    }
    return 0;

}
