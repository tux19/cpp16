//
// Created by Christian Ott on 01.11.2016.
//

#ifndef CPP16_PSET_H
#define CPP16_PSET_H

#include <set>
#include <string>
#include <fstream>
#include <iterator>
#include <initializer_list>
#include <utility>
#include <typeinfo>
#include <iostream>
#include <sstream>
#include "persister.h"


template <typename T, typename P = persister<T>>
class pset {
private:
    typedef P persister;
    typedef typename std::set<T>::iterator iterator;
    typedef typename std::set<T>::const_iterator const_iterator;

    std::string filename;
    std::set<T> s;

    void write_set() {
        try {
            std::ofstream ofs(filename, std::ofstream::out | std::ofstream::trunc);
            T tmp;
            ofs << (typeid(tmp).name()) << std::endl;
            ofs << s.size() << std::endl;
            for (T elem : s) {
                persister::write(ofs, elem);
            }
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    };

    void read_set() {
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


                    while (persister::read(ifs, tmp)) {
                        s.insert(tmp);
                    }
                }
            }
        }
    };

public:
    pset(std::string fname) : filename {fname}, s {} {
        persister::read_set();
    };
    ~pset() {
        persister::write_set();
    };

    size_t size() {
        return s.size();
    }

    bool empty() {
        return s.empty();
    }

    size_t count(const T& key) const {
        return s.count(key);
    }

    void clear() {
        s.clear();
    }

    void erase(iterator pos) {
        s.erase(pos);
    }

    void erase(iterator first, iterator last) {
        s.erase(first, last);
    }

    size_t erase(const T& key) {
        return s.erase(key);
    }

    std::pair<iterator, bool> insert (const T& value) {
        return s.insert(value);
    }

    void insert (typename std::initializer_list<T> iList) {
        s.insert(iList);
    }
/* TODO: Make this work.
    std::pair<iterator, bool> emplace(T&& arg) {
      return s.emplace(arg);
    }*/

    typename std::set<T>::iterator find (const T& key) {
        return s.find(key);
    }

    typename std::set<T>::const_iterator find (const T& key) const {
        return s.find(key);
    }

    typename std::set<T>::iterator begin() {
        return s.begin();
    }

    typename std::set<T>::iterator end() {
        return s.end();
    }

    typename std::set<T>::const_iterator begin() const {
        return s.begin();
    }

    typename std::set<T>::const_iterator end() const {
        return s.end();
    }
};

#endif //CPP16_PSET_H
