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

#include "persister.h"


template <typename T, typename P = persister<T>>
class pset {
private:
    typedef P persister;
    typedef typename std::set<T>::iterator iterator;
    typedef typename std::set<T>::const_iterator const_iterator;

    std::string filename;
    std::set<T> s;

    void read();
    void write);

public:
    pset(std::string fname) : filename {fname}, s {} {
        persister::read();
    };
    ~pset() {
        persister::write();
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
