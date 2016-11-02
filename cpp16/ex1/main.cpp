#include "test_fraction.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout
            << "------------------------------------------------------------\n|		TASK 1.1 \n ------------------------------------------------------------"
            << std::endl;

    std::cout << "Hello World!" << std::endl;

    std::cout
            << "------------------------------------------------------------\n|		TASK 1.2 STATIC TEST DRIVER \n ------------------------------------------------------------"
            << std::endl;

    test_fraction test;

    test.run_static();

    std::cout
            << "------------------------------------------------------------\n|		TASK 1.2 DYNAMIC TEST DRIVER \n ------------------------------------------------------------"
            << std::endl;
    std::cout << "Press a key to start dynamic test! ->" << std::endl;

    //test.run_dynamic();

    std::cin.get();
    return 0;
}
