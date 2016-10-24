#include <vector>
#include <string>
#include <typeinfo>
#include <fstream>
template<typename T>
class pvector
{
private:
	std::vector<T> vec;
	std::string filename;
	void write_vector() 
	{
		try
		{
			std::ofstream ofs(filename, std::ofstream::out | std::ofstream::trunc);
			T tmp;
			ofs << (typeid(tmp).name()) << std::endl;
			ofs << vec.size() << std::endl;
			ofs << vec.capacity() << std::endl;
			for (T elem : vec)
			{
				ofs << elem << std::endl;
			}
		}
		catch (std::exception e)
		{
			std::cout << e.what() << std::endl;
		}
	};

	void read_vector() 
	{
		std::ifstream ifs(filename.data());
		// File exists
		if (ifs.is_open())
		{
			std::string s_tmp;
			int size, capacity;
			
			T tmp;
			std::string t = typeid(tmp).name();
			if (std::getline(ifs, s_tmp)) {
				if ( t != s_tmp)
				{
					std::cout << "ERROR reading file, it contains a vector of a wrong type. creating an empty one..." << std::endl;
				}
				else
				{
					std::getline(ifs, s_tmp);
					size = std::stoi(s_tmp);
					std::getline(ifs, s_tmp);
					capacity = std::stoi(s_tmp);
					vec.reserve(capacity);

					while (ifs >> tmp)
					{
						vec.push_back(tmp);
					}
				}
			}
			else
			{
				std::cout << "ERROR reading file, it was empty" << std::endl;
			}
		}
	};
public:
	pvector(std::string fname) {
		filename = fname;
		read_vector();
	};
	pvector(std::string fname, unsigned int capacity) {
		filename = fname;
		read_vector();

		if (vec.capacity() < capacity) {
			vec.reserve(size);
		}
	};

	pvector(std::string fname, unsigned int capacity, const T & initial){};
	pvector(std::string fname, const pvector<T> & v) {
		filename = fname;
		vec = new std::vector<T>(v);
	};
	~pvector() { write_vector(); };
	
	typedef typename std::vector<T>::iterator* iterator;

	unsigned int capacity() { return vec.capacity(); }
	unsigned int size() { return vec.size(); };
	bool empty() { return vec.empty(); };
	iterator begin() { return &vec.begin(); };
	iterator  end() { return &vec.end(); };
	T & front() { return vec.front(); };
	T & back() { return vec.back(); };
	void push_back(const T & value) { vec.push_back(value); };
	void pop_back() { vec.pop_back(); };

	void reserve(unsigned int capacity) { vec.reserve(capacity); };
	void resize(unsigned int size) { vec.resize(size); };

	T & operator[](unsigned int index) { return vec[index]; };
	pvector<T> & operator=(const pvector<T> &v) {
		vec.clear();
		filename = v.filename;
		std:copy(v.vec.begin(), v.vec.end(), this.vec.begin());
		return this;
	};
	void clear() { vec.clear(); };
};
