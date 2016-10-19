#include "stdafx.h"
#include "pvector.h"
#include <fstream>

template <typename T>
void pvector<T>::write_vector()
{
	std::ofstream ofs(filename);
	
	T tmp;
	ofs << std::type_info(tmp).name();
	ofs << vec.size() << std::endl;
	ofs << vec.capacity() << std::endl;
	for (T elem : vec)
	{
		ofs << elem << std::endl;
	}
	
}

template <typename T>
void pvector<T>::read_vector()
{
	std::ifstream ifs(filename);
	// File exists
	if(ifs.is_open())
	{
		std::string t_name; 
		ifs >> t_name;
		int size;
		ifs >> size;
		int capacity;
		ifs >> capacity;

		vec = new std::vector<T>(capacity);

		T elem;
		while (ifs.good())
		{
			ifs >> elem;
			vec.push_back(elem);
		}
	}
	// File does not exist
	else
	{
		vec = new std::vector<T>();
	}
}

template <typename T>
pvector<T>::pvector(std::string fname)
{
}

template <typename T>
pvector<T>::pvector(std::string fname, unsigned size)
{
}

template <typename T>
pvector<T>::pvector(std::string fname, unsigned size, const T& initial)
{
}

template <typename T>
pvector<T>::pvector(std::string fname, const pvector<T>& v)
{
}

template <typename T>
pvector<T>::~pvector()
{
	write_vector();
}

template <typename T>
unsigned pvector<T>::capacity() const
{
	return vec.capacity();
}

template <typename T>
unsigned pvector<T>::size() const
{
	return vec.size();
}

template <typename T>
bool pvector<T>::empty() const
{
	return vec.empty();
}

template <typename T>
typename pvector<T>::iterator pvector<T>::begin()
{
	return vec.begin();
}

template <typename T>
typename pvector<T>::iterator pvector<T>::end()
{
	return vec.end();
}

template <typename T>
T& pvector<T>::front()
{
	return vec.front();
}

template <typename T>
T& pvector<T>::back()
{
	return vec.back();
}

template <typename T>
void pvector<T>::push_back(const T& value)
{
	vec.push_back(value);
}

template <typename T>
void pvector<T>::pop_back()
{
	vec.pop_back();
}

template <typename T>
void pvector<T>::reserve(unsigned capacity)
{
	vec.reserve(capacity);
}

template <typename T>
void pvector<T>::resize(unsigned size)
{
	vec.resize(size);
}

template <typename T>
T& pvector<T>::operator[](unsigned index)
{
	return vec[index];
}

template <typename T>
pvector<T>& pvector<T>::operator=(const pvector<T>& v)
{
	vec.clear();
	filename = v.filename;
	std:copy(v.vec.begin(), v.vec.end(), this.vec.begin());
	return this;
}

template <typename T>
void pvector<T>::clear()
{
	vec.clear();
}
