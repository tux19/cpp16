#include <iostream>
#include <vector>
#include <forward_list>

// type returned by std::distance
template<typename I> using DifferenceTypeOf =
typename std::iterator_traits<I>::difference_type;

template<typename I> using IteratorCategoryOf =
typename std::iterator_traits<I>::iterator_category;

template<typename I> using IsRandomAccessIterator =
std::is_base_of<std::random_access_iterator_tag, IteratorCategoryOf<I>>;

template<typename I> using IsInputIterator =
std::is_base_of<std::input_iterator_tag, IteratorCategoryOf<I>>;

// returns T if B is true,
// if B is false it evaluates to empty, leads to invalid template substition and is ignored
// equal to enable_if_t in c++14
template<bool B, typename T = void>
using enableif = typename std::enable_if<B,T>::type ;


template<typename II>
DifferenceTypeOf<enableif<IsInputIterator<II>::value, II>>
_distance(II first, II last, std::input_iterator_tag dummy){
    int n = 0;
    while(first != last){
        ++first;
        ++n;
    }
    std::cout<< "Used II Iter distance!" << std::endl;
    return n;
}
template<typename RAI>
DifferenceTypeOf<RAI>
// ::value -> true or false
_distance(RAI first, RAI last, std::random_access_iterator_tag dummy){
    std::cout<< "Used RA Iter distance!" << std::endl;
    return last-first;
}


template<typename I>
DifferenceTypeOf<I>
my_distance(I first, I last){
    using cat = IteratorCategoryOf<I>;
    return _distance(first, last, cat());
}


int main() {
    std::vector<int> v{2,8,2,9,42,9876,2,64,98,2,13};
    std::forward_list<int> l{2,8,2,9,42,9876,2,64,98,2,13};
    std::cout << "------------------------------------------------------------\n|	   TASK 10.1 \n ------------------------------------------------------------"
              << std::endl;

    std::cout << "Distance of begin and end InputIter: " <<my_distance(l.begin(), l.end()) << std::endl;
    std::cout << "Distance of begin and end RAIter: " << my_distance(v.begin(), v.end()) << std::endl;
    return 0;
}