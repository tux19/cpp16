#include <iostream>
#include <sstream>


class Form{
public:
    int prc;
    std::ios_base::fmtflags fmt;
    Form(int p=6) : prc(p) {
    }
    Form& scientific() {
        fmt = std::ios_base::scientific;
        return *this;
    }
    Form& precision(int p) {
        prc=p;
        return *this;
    }
    std::string operator()(double value){
        std::stringstream ss;
        ss.setf(fmt, std::ios_base::floatfield);
        ss.precision(prc);
        ss << value;
        std::string myString = ss.str();
        return myString;
    }

};
std::ostream& operator<<(std::ostream& os, const Form &f){
    os.setf(f.fmt, std::ios_base::floatfield);
    os.precision(f.prc);
    return os;
}


Form gen4(4);

void f(double d){
    Form sci8 = gen4;
    sci8.scientific().precision(8);
    std::cout << sci8(d) << " back to old option: " << d << std::endl;
}

int main() {
    std::cout << "------------------------------------------------------------\n|		TASK 9.1 \n ------------------------------------------------------------"
              << std::endl;
    f(1./3);
    
    return 0;
}
