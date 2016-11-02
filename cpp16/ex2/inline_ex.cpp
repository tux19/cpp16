#include <iostream>

// A compiler CAN inline a recursive function, but not COMPLETELY.
int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 12; ++i)
        std::cout << factorial(i) << std::endl;
}

