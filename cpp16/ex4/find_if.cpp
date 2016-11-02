#include <iostream>
#include <Vector>

class Matcher{
	public:
		bool match(std::string elem){
		if(elem.compare("Hello") == 0){
			std::cout << "matched";
			return true;
		}
	}
};

bool findif(std::vector<std::string>::iterator begin,std::vector<std::string>::iterator end ,Matcher m){ 
	while(begin != end){
		if(m.match(*begin)){return true;}
		*begin++;
	}
}

int main(){
	std::vector<std::string> vector(1000000,"Hello");
	Matcher matcher;
	std::vector<std::string>::iterator begin = vector.begin();
	std::vector<std::string>::iterator end = vector.end();
	findif(begin,end,matcher);
	
	return 0;
}
