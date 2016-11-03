#include <iostream>
#include "pvector.h"

int main(){
	pvector<int> sample= pvector<int>("pvec.txt");
	int x = 42;
	int y = 41;
	sample.push_back(x);
	sample.push_back(y);
	for (int n = 0; n < sample.size(); n++) {
            std::cout << '\t' << n << ". " << sample[n] << std::endl;
        }
	sample.pop_back();
	
	return 0;
}
