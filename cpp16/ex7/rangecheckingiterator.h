//
// Created by HEAD on 13.12.2016.
//

#ifndef CPP16_RANGECHECKINGITERATOR_H
#define CPP16_RANGECHECKINGITERATOR_H
#include <iostream>
#include <vector>
template <typename iterator>
class rangecheckingiterator {

private:

    iterator _begin;
    iterator _end;
    iterator _current;
    typedef typename std::iterator_traits<iterator>::value_type value_type;
    typedef typename std::iterator_traits<iterator>::pointer pointer;
    typedef typename std::iterator_traits<iterator>::reference reference;

public:
    rangecheckingiterator(iterator begin , iterator end, iterator current)
            :_begin(begin),_end(end),_current(current) {}
    rangecheckingiterator(iterator begin , iterator end)
            :_begin(begin),_end(end),_current(begin) {}

   ~rangecheckingiterator(){}

    //preincrement
    rangecheckingiterator operator++(){
        if (_current == (_end - 1)) { // end - 1 because end is AFTER the last element; mathematically: [begin, end)
            throw std::range_error("Iterator overflow");
        }
        _current++;
        return *this;
    }
    rangecheckingiterator operator--(){
        if (_current == _begin) {
            throw std::range_error("Iterator underflow");
        }
        _current--;

        return *this;
    }
    //postincrement
    rangecheckingiterator operator++(int){
        rangecheckingiterator tmp(*this);
        operator++();
        return tmp;
    }
    rangecheckingiterator operator--(int){
        rangecheckingiterator tmp(*this);
        operator--();
        return tmp;
    }

    value_type operator *(){
        if (_current == _end) {
            throw std::range_error("Out of bounds");
        }
        return *_current;;

    }
    pointer operator->() const{
        return &*_current;
    }

    bool operator ==(rangecheckingiterator const& other) const{
        return (_begin == other._begin) && (_end == other._end) && (_current == other._current);
    }
    bool operator !=(rangecheckingiterator const& other) const{
        return !operator==(other);
    }
};


#endif //CPP16_RANGECHECKINGITERATOR_H
