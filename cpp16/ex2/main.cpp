#include "stdafx.h"
#include <iostream>
#include "pvector.h"
#include "rpn.h"
#include "rpn_templ.h"
#include "fraction.h"
int main(int argc, char* argv[])
{
	std::cout << "------------------------------------------------------------\n|		TASK 2.1 Persistent Vector \n ------------------------------------------------------------" << std::endl;

	{
		pvector<std::string> int_vec("intvec.vec");
		//int_vec.clear();

		int_vec.push_back("DAS");
		int_vec.push_back("asd");
	}
	pvector<std::string> int_vec("intvec.vec");

	for (int i = 0; i < int_vec.size(); i++)
	{
		std::cout << int_vec[i] << std::endl;
	}
	
	std::cout << "------------------------------------------------------------\n|		TASK 2.1 Inline Showcase \n ------------------------------------------------------------" << std::endl;

	std::cout << "------------------------------------------------------------\n|		TASK 2.2 RPN demo \n ------------------------------------------------------------" << std::endl;
	rpn r;
	r.run();
	std::cout << "------------------------------------------------------------\n|		TASK 2.2 RPN template \n ------------------------------------------------------------" << std::endl;
	rpn_templ<fraction> rt;
	rt.run();
	std::cout << "------------------------------------------------------------\n|		TASK 2.2 RPN template & persistent \n ------------------------------------------------------------" << std::endl;

	std::cin.get();
	return 0;
}