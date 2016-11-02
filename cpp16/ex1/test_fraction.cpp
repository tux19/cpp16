#include "test_fraction.h"
#include <iostream>
#include "fraction.h"
#include <sstream>


test_fraction::test_fraction() {

}


test_fraction::~test_fraction() {
}

void test_fraction::run_static() {
    fraction f(2, 3);
    fraction f2(1, 6);
    fraction f3(3, 4);
    std::stringstream os;
    os << f;

    std::cout << "Ostream test: should output (2/3)\n\t";
    std::cout << os.str() << " -> ";
    std::cout << (os.str() == "(2/3)" ? "OK" : "NOT OK") << std::endl;


    std::cout << "Istream test: (5/2) into fraction, should be equal to fraction(5,2)\n\t";
    os = std::stringstream("(5/2)");
    os >> f;
    std::cout << (f == fraction(5, 2) ? "OK" : "NOT OK") << std::endl;

    std::cout << "operator-() test: (5/2) shold turn to (-5/2) \n\t";
    std::cout << f << " -> " << (-f);
    std::cout << (-f == fraction(-5, 2) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator+(fraction) test: (5/2) + (1/6) shold turn to (8/3) \n\t";
    std::cout << f << "+" << f2 << " -> " << f + f2;
    std::cout << ((f + f2) == fraction(8, 3) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator+(fraction) commutative test: (1/6) + (5/2) shold turn to (8/3) \n\t";
    std::cout << f2 << "+" << f << " -> " << f2 + f;
    std::cout << ((f2 + f) == fraction(8, 3) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator-(fraction) test: (5/2) - (1/6) shold turn to (7/3) \n\t";
    std::cout << f << "-" << f2 << " -> " << f - f2;
    std::cout << ((f - f2) == fraction(7, 3) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator-(fraction) anti-commutative test: (1/6) - (5/2) shold be equal to -((5/2) - (1/6)) \n\t";
    std::cout << f << "-" << f2 << " == -(" << f2 << " - " << f << ") == " << -(f2 - f);
    std::cout << (-(f2 - f) == (f - f2) ? " OK" : " NOT OK") << std::endl;

    std::cout << "operator*(fraction) test: (5/2) * (1/6) shold turn to (5/12) \n\t";
    std::cout << f << "*" << f2 << " -> " << f * f2;
    std::cout << ((f * f2) == fraction(5, 12) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator*(fraction) commutative test: (1/6) * (5/2) shold turn to (5/12) \n\t";
    std::cout << f2 << "*" << f << " -> " << f2 * f;
    std::cout << ((f2 * f) == fraction(5, 12) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator*(fraction) test: (5/2) / (3/4) shold turn to (10/3) \n\t";
    std::cout << f << "/" << f3 << " -> " << f / f3;
    std::cout << ((f / f3) == fraction(10, 3) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator+(int) test: (5/2) + 2 shold turn to (9/2) \n\t";
    std::cout << f << "+" << 2 << " -> " << f + 2;
    std::cout << ((f + 2) == fraction(9, 2) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator+(int,fraction) commutative test: 2 + (5/2) shold turn to (9/2) \n\t";
    std::cout << 2 << "+" << f << " -> " << 2 + f;
    std::cout << ((2 + f) == fraction(9, 2) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator-(int) test: (5/2) - 2 shold turn to (1,2) \n\t";
    std::cout << f << "-" << 2 << " -> " << f - 2;
    std::cout << ((f - 2) == fraction(1, 2) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator-(int,fraction) anti-commutative test: 2 - (5/2) shold be equal to -((5/2) - 2) \n\t";
    std::cout << 2 << "-" << f << " == -(" << f << " - " << 2 << ") == " << 2 - f;
    std::cout << (-(f - 2) == (2 - f) ? " OK" : " NOT OK") << std::endl;

    std::cout << "operator*(int) test: (5/2) * 2 shold turn to (5/1) \n\t";
    std::cout << f << "*" << 2 << " -> " << f * 2;
    std::cout << ((f * 2) == fraction(5, 1) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator*(int,fraction) commutative test: 2 * (5/2) shold turn to (5/1) \n\t";
    std::cout << 2 << "*" << f << " -> " << 2 * f;
    std::cout << ((2 * f) == fraction(5, 1) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator/(int) test: (5/2) / 2 shold turn to (5/4) \n\t";
    std::cout << f << "/" << 2 << " -> " << f / 2;
    std::cout << ((f / 2) == fraction(5, 4) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator/(int,fraction) test: 2 / (5/2) shold turn to (4/5) \n\t";
    std::cout << 2 << "/" << f << " -> " << 2 / f;
    std::cout << ((2 / f) == fraction(4, 5) ? " OK" : "NOT OK") << std::endl;

    fraction f4(6, 8);

    std::cout << "operator==(fraction) test: (6/8) == (3/4) shold turn to 'true' \n\t";
    std::cout << f4 << "==" << f3 << " -> true";
    std::cout << (f4 == f3 ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator==(fraction) commutative test: (3/4) == (6/8) shold turn to 'true' \n\t";
    std::cout << f3 << "==" << f4 << " -> true";
    std::cout << (f3 == f4 ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator==(fraction) test: (6/8) == (5/2) shold turn to 'false' \n\t";
    std::cout << f4 << "==" << f << " -> false";
    std::cout << (!(f4 == f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator==(fraction) commutative test: (5/2) == (6/8) shold turn to 'false' \n\t";
    std::cout << f << "==" << f4 << " -> false";
    std::cout << (!(f == f4) ? " OK" : "NOT OK") << std::endl;


    std::cout << "operator!=(fraction) test: (6/8) != (3/4) shold turn to 'false' \n\t";
    std::cout << f4 << "!=" << f3 << " -> false";
    std::cout << (!(f4 != f3) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator!=(fraction) commutative test: (3/4) != (6/8) shold turn to 'false' \n\t";
    std::cout << f3 << "!=" << f4 << " -> false";
    std::cout << (!(f3 != f4) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator!=(fraction) test: (6/8) != (5/2) shold turn to 'true' \n\t";
    std::cout << f4 << "!=" << f << " -> true";
    std::cout << ((f4 != f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator!=(fraction) commutative test: (5/2) != (6/8) shold turn to 'true' \n\t";
    std::cout << f << "!=" << f4 << " -> true";
    std::cout << ((f != f4) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator<(fraction) test: (3/4) < (5/2) shold turn to 'true' \n\t";
    std::cout << f4 << "<" << f << " -> true";
    std::cout << ((f4 < f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator<(fraction)  test: (5/2) < (3/4) shold turn to 'false' \n\t";
    std::cout << f << "<" << f4 << " -> false";
    std::cout << (!(f < f4) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator<(fraction)  test: (5/2) < (5/2) shold turn to 'false' \n\t";
    std::cout << f << "<" << f << " -> false";
    std::cout << (!(f < f) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator>(fraction) test: (3/4) > (5/2) shold turn to 'false' \n\t";
    std::cout << f4 << ">" << f << " -> false";
    std::cout << (!(f4 > f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator>(fraction) test: (5/2) > (5/2) shold turn to 'false' \n\t";
    std::cout << f << ">" << f << " -> false";
    std::cout << (!(f > f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator>(fraction)  test: (5/2) > (3/4) shold turn to 'true' \n\t";
    std::cout << f << ">" << f4 << " -> true";
    std::cout << ((f > f4) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator<=(fraction) test: (3/4) <= (5/2) shold turn to 'true' \n\t";
    std::cout << f4 << "<=" << f << " -> true";
    std::cout << ((f4 <= f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator<=(fraction)  test: (5/2) <= (3/4) shold turn to 'false' \n\t";
    std::cout << f << "<=" << f4 << " -> false";
    std::cout << (!(f <= f4) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator<=(fraction)  test: (5/2) <= (5/2) shold turn to 'true' \n\t";
    std::cout << f << "<=" << f << " -> true";
    std::cout << ((f <= f) ? " OK" : "NOT OK") << std::endl;

    std::cout << "operator>=(fraction) test: (3/4) >= (5/2) shold turn to 'false' \n\t";
    std::cout << f4 << ">0" << f << " -> false";
    std::cout << (!(f4 >= f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator>=(fraction) test: (5/2) >= (5/2) shold turn to 'true' \n\t";
    std::cout << f << ">=" << f << " -> true";
    std::cout << ((f >= f) ? " OK" : "NOT OK") << std::endl;
    std::cout << "operator>=(fraction)  test: (5/2) >= (3/4) shold turn to 'true' \n\t";
    std::cout << f << ">=" << f4 << " -> true";
    std::cout << ((f >= f4) ? " OK" : "NOT OK") << std::endl;

}

void test_fraction::run_dynamic() {
std::cout << "Enter a fraction: ";
	fraction f1, f2;
	std::cin >> f1;
	std::cout << "Enter a second fraction: ";
	std::cin >> f2;
	std::cout << "Enter '+', '-', '*', '/' , '>' ,'<', '>=' ,'<=', '==' ,'!='\n";
	std::string input;
	std::cin >> input;
	if(input == "+"){
		std::cout << f1 + f2<< "\n";
	}else if(input == "-"){
		std::cout << f1 - f2<< "\n"; 
	}else if(input == "*"){
		std::cout << f1 * f2<< "\n";
	}else if(input == "/"){
		std::cout << f1 / f2<< "\n"; 
	}else if(input == ">"){
		std::cout << (f1>f2)<< "\n";
	}else if(input == "<"){
		std::cout << (f1<f2)<< "\n";
	}else if(input == ">="){
		std::cout << (f1>=f2)<< "\n";
	}else if(input == "<="){
		std::cout << (f1<=f2)<< "\n";
	}else if(input == "=="){
		std::cout << (f1==f2)<< "\n";
	}else if(input == "!="){
		std::cout << (f1!=f2)<< "\n";
	}
	
	std::cout << "Abort testing? [y/n] :\n";
	std::cin >> input;
	if(input[0]!='y') { run_dynamic(); }
}
