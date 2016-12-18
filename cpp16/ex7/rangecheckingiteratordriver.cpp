//
// Created by HEAD on 13.12.2016.
//
#include "rangecheckingiterator.h"
#include <forward_list>
#include <iostream>


int main(){
    std::vector<int> mylist = { 34, 77, 16, 2 };
    rangecheckingiterator<int> r =rangecheckingiterator<int>(mylist.begin(),mylist.end(),mylist.end());
    rangecheckingiterator<int> x = rangecheckingiterator<int>(mylist.begin(),mylist.end(),mylist.begin());
    std::cout << *--r.current() << std::endl;
    std::cout << *x.current() << std::endl;
   try{ r++;
   }catch(std::out_of_range e){ std::cout << "Out of range (++)" << std::endl; }
    try{ x--;
    }catch(std::out_of_range e){ std::cout << "Out of range (--)" << std::endl;
    }
    return 0;
}
