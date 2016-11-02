#include "rpn.h"
#include <regex>
#include <iostream>
#include <string>

class myexception : public std::exception {
    virtual const char *what() const throw() {
        return "ERROR: Devision by 0!";
    }
} division_by_zero;

rpn::rpn() {
}


rpn::~rpn() {
}

void rpn::run() {
    std::cout
            << " --------------------------\n� Simple RPN Calculator\n--------------------------\n\t'n <number>' to put a number on the stack'\n\t'<opertation>' to du an operation on the stack\n\t 'd' to delete a number from the stack\n\t 'q' to quit the calculator"
            << std::endl;
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
}

void rpn::evaluate_postfix(const char operation) {

    double left, right, result;

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
            if (right == 0) {
                throw division_by_zero;
            } else {
                result = left / right;
            }
            break;
        }
        default:
            break;
    }

    stack.push_back(result);
}

void rpn::print_stack() {
    for (int n = 0; n < stack.size(); n++) {
        std::cout << "\t(" << n << ") -> " << stack[n] << std::endl;
    }
}


