//
// Created by HEAD on 13.12.2016.
//

#ifndef CPP16_RANGECHECKINGITERATOR_H
#define CPP16_RANGECHECKINGITERATOR_H
#include <iostream>
#include <vector>
template <typename T>
class rangecheckingiterator {
    typedef typename std::vector<T>::iterator iterator;
private:

    iterator _begin;
    iterator _end;
    iterator _current;

public:
    rangecheckingiterator(iterator begin , iterator end, iterator current) :_begin(begin),_end(end),_current(current) {}
   ~rangecheckingiterator(){

   }

    T *operator->() const{
      return *(_current);
    }
    iterator begin(){ return _begin; }
    iterator end(){ return _end;}
    iterator current(){return _current;}
    void operator++(int) { // throws std::out_of_range
        if (_current++ != _end) {
            _current++;
        } else {
            throw std::out_of_range("Out of range");
        }
    }

    void operator--(int i){// throws std::out_of_range
        if(_current-- != _begin){
            _current--;
        }else{
            throw std::out_of_range("Out of range");
        }
    }


};


#endif //CPP16_RANGECHECKINGITERATOR_H
