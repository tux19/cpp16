#include <iostream>
#include "pvector.h"

int main(){
	pvector<int> sample= pvector<int>("pvec.txt");
	int x = 42;
	sample.push_back(x);
	
	for (int n = 0; n < sample.size(); n++) {
            std::cout << '\t' << n << ". " << sample[n] << std::endl;
        }
	sample.pop_back();
	
	return 0;
}
