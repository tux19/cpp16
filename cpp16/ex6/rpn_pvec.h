#ifndef CPP16_EX6_RPN_PVEC_FOREACH_H
#define CPP16_EX6_RPN_PVEC_FOREACH_H
#include <vector>
#include <sstream>
#include <iostream>
#include "pvector.h"
#include <string>
#include <algorithm>
#include <stdexcept>



template<typename T>
class rpn_pvec {
    pvector<T> stack = pvector<T>("stack.vec");
    T tmp;

    inline std::pair<T,T> get_pair(){
        T first, second;
        second = stack.back();
        stack.pop_back();
        first = stack.back();
        stack.pop_back();
        return std::pair<T, T>(first, second);
    }
    template<typename T2>
    inline T2 my_min(T2 a, T2 b){ return a<b?a:b; };

    inline std::complex<double > my_min(std::complex<double > a, std::complex<double> b){ throw std::invalid_argument("ERROR: called min on complex numbers, nothing done..."); };

    void evaluate_postfix(const char operation) {

        T left, right, result, min;


        //Pull out top two elements
        right = stack.back();
        stack.pop_back();
        left = stack.back();
        stack.pop_back();
        // Perform the maths
        switch (operation) {
            case '+':
                result = left + right;
                break;
            case '-':
                result = left - right;
                break;
            case '*':
                result = left * right;
                break;
            case '/': {

                result = left / right;
                break;
            }
            case 'm': {
                try {
                    auto smallest = my_min(left,right);
                    std::for_each(stack.begin(), stack.end(), [&](T &c) { smallest = my_min(smallest,c); });
                    stack.clear();
                    result = smallest;

                }catch(std::invalid_argument &e){
                    std::cout << e.what() << std::endl;
                    stack.push_back(left);
                    result = right;
                    break;
                }
                break;
            }
            default:
                break;
        }

        stack.push_back(result);
    };

    void print_stack() {
        for (int n = 0; n < stack.size(); n++) {
            std::cout << '\t' << n << ". " << stack[n] << std::endl;
        }
    }

public:
    rpn_pvec() {};

    ~rpn_pvec() {};

    void run() {
        std::cout
                << " --------------------------\n| Simple RPN Calculator\n--------------------------\n\t'n <number>' to put a number on the stack'\n\t'<opertation>' to du an operation on the stack\n\t 'd' to delete a number from the stack\n\t 'q' to quit the calculator"
                << std::endl;
        std::cout << "\nCurrent Stack: " << std::endl;
        print_stack();

        std::string line, s;

        do {
            std::cout << "Command: ";
            std::getline(std::cin, line);

            std::stringstream ss(line);
            ss >> s;

            if (s.length() > 1) {
                std::cout << "ERROR: command too long, try again!" << std::endl;
            } else {

                switch (s[0]) {
                    case 'q':
                        break;

                    case 'd':
                        tmp = stack.back();
                        stack.pop_back();
                        print_stack();
                        break;
                    case '+':
                        evaluate_postfix(s[0]);
                        print_stack();
                        break;
                    case '-':
                        evaluate_postfix(s[0]);
                        print_stack();
                        break;
                    case '*':
                        evaluate_postfix(s[0]);
                        print_stack();
                        break;
                    case '/':
                        evaluate_postfix(s[0]);
                        print_stack();
                        break;
                    case 'm':
                        evaluate_postfix(s[0]);
                        print_stack();
                        break;
                    case 'n':
                        ss >> tmp;
                        stack.push_back(tmp);
                        print_stack();
                        break;
                    default:
                        std::cout << "ERROR: unknown command, try again!" << std::endl;
                        break;
                }
            }
        } while (s != "q");
    };
};

#endif