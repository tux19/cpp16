#include "stdafx.h"
#include "pvector.h"


template <typename T>
void pvector<T>::write_vector()
{
}

template <typename T>
void pvector<T>::read_vector()
{
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
}

template <typename T>
unsigned pvector<T>::capacity() const
{
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
}

template <typename T>
void pvector<T>::resize(unsigned size)
{
}

template <typename T>
T& pvector<T>::operator[](unsigned index)
{
	return vec[index];
}

template <typename T>
pvector<T>& pvector<T>::operator=(const pvector<T>&)
{
}

template <typename T>
void pvector<T>::clear()
{
	vec.clear();
}
