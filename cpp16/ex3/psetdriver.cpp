#include <iostream>
#include "pset.h"

int main(){
	pset<int> sample= pset<int>("pvec.txt");
	int x = 42;
	int y = 41;
	sample.insert(y);
	sample.insert(x);
	sample.insert(x);
	sample.erase(y);
	for (pset<int>::iterator i = pset.begin(); i != pset.end(); i++) {
		std::cout << '\t' << n << ". " << *i << std::endl;
	}
	return 0;
}
