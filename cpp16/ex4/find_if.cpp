#include <iostream>
#include <Vector>

template<typename T>
class Matcher{
	public:
		bool match(T elem){
		if(true){
			std::cout << "matched";
			return true;
		}
	}
};
template<>
class Matcher<std::string>{
	public:
		bool match(std::string elem){
		if(elem.compare("Hello") == 0){
			std::cout << "matched";
			return true;
		}
	}
};

template<typename T>
	bool findif(typename std::vector<T>::iterator begin,typename std::vector<T>::iterator end, Matcher<T> m){ 
		while(begin != end){
			if(m.match(*begin)){return true;}
			*begin++;
		}
	}
	
int main(){
	std::vector<std::string> vector(1000000,"Hello");
	Matcher<std::string> matcher;
	std::vector<std::string>::iterator begin = vector.begin();
	std::vector<std::string>::iterator end = vector.end();

	findif<std::string>(begin,end,matcher);
	
	
	return 0;
}
