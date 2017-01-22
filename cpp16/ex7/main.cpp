#include <iostream>
#include <vector>
#include "rangecheckingiterator.h"
#include "merger.h"


int main() {
    std::cout << "------------------------------------------------------------\n|		TASK 7.1 \n ------------------------------------------------------------"
              << std::endl;
    std::vector<int> vec;
    std::vector<double> vec2;

    for (int i = 0; i < 5; i++) {
        vec.push_back(std::rand());
        vec2.push_back(std::rand() + 0.03);
    }

    //rangecheckingiterator<std::vector<int>::iterator> itr(vec.begin(), vec.end());
    rangecheckingiterator<std::vector<double>::iterator> itr(vec2.begin(), vec2.end());

    try {
        for (int i = 0; i < 5; i++) {
            std::cout << *itr << std::endl;
            ++itr;
        }
    } catch (const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    try {
        for (int i = 0; i < 5; i++) {
            std::cout << *itr << std::endl;
            --itr;
        }
    } catch (const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }


    std::cout << "------------------------------------------------------------\n|		TASK 7.2 \n ------------------------------------------------------------"
              << std::endl;

    std::cout << "------------------------------------------------------------\n|		TASK 7.3 \n ------------------------------------------------------------"
              << std::endl;
    std::vector<int> v1, v2, o;

    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(1);

    v2.push_back(6);
    v2.push_back(5);
    v2.push_back(4);

    merger<std::vector<int> >::merge(v1, v2, o);

    for( auto e : o){
        std::cout << e << std::endl;
    }

    std::cout << "------------------------------------------------------------\n|		TASK 7.4 \n ------------------------------------------------------------"
              << std::endl;
    return 0;
}