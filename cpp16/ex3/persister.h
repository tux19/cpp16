//
// Created by Christian Ott on 02.11.2016.
//

#ifndef CPP16_PERSISTER_H
#define CPP16_PERSISTER_H

#include <fstream>

template<typename T>
struct persister{
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
struct persister<std::string> {
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

#endif //CPP16_PERSISTER_H
