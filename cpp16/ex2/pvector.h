#pragma once
#include <string>
template<typename T>
class pvector
{
private:
	std::string filename;
	std::vector<T> vec;

	void write_vector();
	void read_vector();
public:
	pvector(std::string fname);
	pvector(std::string fname, unsigned int size);
	pvector(std::string fname, unsigned int size, const T & initial);
	pvector(std::string fname, const pvector<T> & v);
	~pvector();

	typedef T * iterator;

	unsigned int capacity() const;
	unsigned int size() const;
	bool empty() const;
	iterator begin();
	iterator end();
	T & front();
	T & back();
	void push_back(const T & value);
	void pop_back();

	void reserve(unsigned int capacity);
	void resize(unsigned int size);

	T & operator[](unsigned int index);
	pvector<T> & operator=(const pvector<T> &);
	void clear();
};

