#include <vector>
#include <sstream>

class rpn {
private:
    std::vector<double> stack;
    double tmp;

    void evaluate_postfix(const char operation);

    void print_stack();

public:
    rpn();

    ~rpn();

    void run();
};

