#ifndef CPP16_EX3_PVEC_H
#define CPP16_EX3_PVEC_H

#include <vector>
#include <string>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <locale>
#include <iostream>
#include "persister.h"


template<typename T, typename P=persister<T> >
class pvector {
private:
    typedef P persister;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    std::vector<T> vec;
    std::string filename;

    void write_vector() {
        try {
            std::ofstream ofs(filename, std::ofstream::out | std::ofstream::trunc);
            T tmp;
            ofs << (typeid(tmp).name()) << std::endl;
            ofs << vec.size() << std::endl;
            ofs << vec.capacity() << std::endl;
            for (T elem : vec) {
                persister::write(ofs, elem);
            }
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    };

    void read_vector() {
        std::ifstream ifs(filename.data());
        // File exists
        if (ifs.is_open()) {
            std::string s_tmp = "";
            size_t size, capacity;

            T tmp;
            std::string t = typeid(tmp).name();
            std::getline(ifs, s_tmp);
            if (s_tmp != "") {
                if (t != s_tmp) {
                    std::cout << "ERROR reading file, it contains a vector of a wrong type. creating an empty one..."
                              << std::endl;
                } else {
                    std::getline(ifs, s_tmp);
                    std::stringstream ss(s_tmp);
                    ss >> size;
                    std::getline(ifs, s_tmp);
                    std::stringstream ss2(s_tmp);
                    ss2 >> capacity;

                    while (persister::read(ifs, tmp)) {
                        vec.push_back(tmp);
                    }
                }
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
            vec.reserve(capacity);
        }
    };

    pvector(const pvector<T> &v) {
        filename = v.filename;
        vec = v.vec;
    };

    pvector(const pvector<T> &&v) {
        filename = std::move(v.filename);
        vec = std::move(v.vec);
    };

    ~pvector() { write_vector(); };

    size_t capacity() { return vec.capacity(); }

    size_t size() { return vec.size(); };

    bool empty() { return vec.empty(); };

    iterator begin() { return vec.begin(); };

    iterator end() { return vec.end(); };

    T &front() { return vec.front(); };

    T &back() { return vec.back(); };

    void push_back(const T &value) { vec.push_back(value); };

    void pop_back() { vec.pop_back(); };

    void reserve(size_t capacity) { vec.reserve(capacity); };

    void resize(size_t size) { vec.resize(size); };

    T &operator[](unsigned int index) { return vec[index]; };

    pvector<T> &operator=(const pvector<T> &other) {

        if (this != &other) {
            filename = other.filename;
            vec = other.vec;
        }
        return *this;
    };

    pvector<T> &operator=(const pvector<T> &&other) {

        if (this != &other) {
            filename = std::move(other.filename);
            vec = std::move(other.vec);
        }
        return *this;
    };

    void clear() { vec.clear(); };
};

#endif
