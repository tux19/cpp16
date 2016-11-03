#include <iostream>
#include "pvector.h"
#include "rpn.h"
#include "rpn_templ.h"
#include "rpn_pvec.h"
#include "fraction.h"

int main(int argc, char *argv[]) {
	std::cout << "------------------------------------------------------------\n|		TASK 2.1 Persistent Vector \n ------------------------------------------------------------" << std::endl;

	{
		pvector<std::string> str_vec("intvec.vec");
		//int_vec.clear();

        str_vec.push_back("DAS");
        str_vec.push_back("aö\tsd");
	}
	pvector<std::string> str_vec("intvec.vec");

	for (int i = 0; i < str_vec.size(); i++)
	{
		std::cout << str_vec[i] << std::endl;
	}

	std::cout << "------------------------------------------------------------\n|		TASK 2.1 Inline Showcase \n ------------------------------------------------------------" << std::endl;
    std::cout << "\n\t see external program...\n"<< std::endl;
	std::cout << "------------------------------------------------------------\n|		TASK 2.2 RPN demo \n ------------------------------------------------------------" << std::endl;
	rpn r;
    r.run();
    std::cout
            << "------------------------------------------------------------\n|		TASK 2.2 RPN template \n ------------------------------------------------------------"
            << std::endl;
    rpn_templ<fraction> rt;
    rt.run();
    std::cout
            << "------------------------------------------------------------\n|		TASK 2.2 RPN template & persistent \n ------------------------------------------------------------"
            << std::endl;
    {
        rpn_pvec<fraction> rp;
        rp.run();
    }
    rpn_pvec<fraction> rp;
    rp.run();

    std::cin.get();
    return 0;
}