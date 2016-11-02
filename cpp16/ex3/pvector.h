//
// Created by Christian Ott on 31.10.2016.
//

#ifndef PVECTOR_H_TRAITS
#define PVECTOR_H_TRAITS

#include <vector>
#include <string>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <locale>
#include <iostream>

// excluded read & write function for partial tmpl specialization
template<typename T>
struct pvec_persister {
    static bool read(std::ifstream &ifs, T &elem) {
        // File exists
        if (ifs.is_open()) {
            ifs >> elem;
            return !ifs.bad();
        }
        return false;
    };

    static bool write(std::ofstream &ofs, T &elem) {
        ofs << elem << std::endl;
        return true;
    };
};

template<>
struct pvec_persister<std::string> {
    static bool read(std::ifstream &ifs, std::string &elem) {
        // File exists
        if (ifs.is_open()) {
            std::getline(ifs, elem);

            return !ifs.eof();
        }
        return false;
    }

    static bool write(std::ofstream &ofs, std::string &elem) {
        ofs << elem << std::endl;
        return true;
    };
};


template<typename T, typename P=pvec_persister<T> >
class pvector {
private:
    typedef P persister;
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

    typedef typename std::vector<T>::iterator *iterator;

    size_t capacity() { return vec.capacity(); }

    size_t size() { return vec.size(); };

    bool empty() { return vec.empty(); };

    iterator begin() { return &vec.begin(); };

    iterator end() { return &vec.end(); };

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
#endif //PVECTOR_H_TRAITS
