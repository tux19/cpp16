/*
Containers to consider:
Sequentielle Containerklassen
array
vector
list
forward_list
deque
Assoziative Containerklassen

unordered_map
unordered_multimap
unordered_multiset
unordered_set
map
multimap
multiset
set
Containeradapterklassen (keine C++ Standardbibliothek-Iteratoren)

priority_queue
queue
stack
Only allow to merge container with higher specialization into lower specialization:list merge(list,forward-list);
											merge(vector,list);
and container of same kind: merge(array,array); 
			    merge(list,list);

*/
#include <iostream>
#include <vector>
template<typename T>
typename std::vector<T> merge(typename std::vector<T>::iterator begin1,typename std::vector<T>::iterator end1,
						typename std::vector<T>::iterator begin2,typename std::vector<T>::iterator end2){
		std::vector<T> mergedV;
		mergedV.insert( mergedV.end(), begin1, end1 );
		mergedV.insert( mergedV.end(), begin2, end2 );
		return mergedV;
}

int main(){
	static const int arr[] = {1,2,3,4};
	static const int arr2[] = {5,6,7,99};
	std::vector<int> first (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	std::vector<int> second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	std::vector<int> third = merge<int>(first.begin(),first.end(),second.begin(),second.end());
	
	for (auto i = third.begin(); i != third.end(); ++i){
    std::cout << *i << ' ';
	}
	return 0;
}
