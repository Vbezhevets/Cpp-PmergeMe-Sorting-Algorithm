
#include <climits>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <iterator>
#include <ostream>
#include <type_traits>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

#include <deque>
#include <iomanip>
#include "Level.hpp"

// int count = 0;
template <typename Container>
void print(const Container& v) {
    for (int i = 0; i < static_cast<int>(v.size()); ++i) 
        std::cout  << v[i] << " ";
    std::cout << "\n";
}


int jacob( int n) {
	if (n <= 1)
		return 1;
	return (jacob(n - 1) + 2 * jacob(n - 2));
}
template <typename Container>
Container getJacobsNums(int n) {
	Container jnums;
	int j = 0;
	int i = 1;
	while (j  <= n){
		j = jacob(i);
		jnums.push_back(j);
		i++;
	}
	return jnums;
}

template <typename Container>
int binInsert(Container &v, int n, int left, int right) {
	while (left <= right){
		// count++;
		int middle = left + (right - left) / 2;
		if (n < v[middle])
			right = middle - 1;
		else 
			left = middle + 1;
	}
	v.insert(v.begin() + left, n);
	return left;
}
template <typename Container, typename LevelType>
LevelType *intoPairs(Container& levels, int l){

	LevelType *prevL = levels[l];
	if (prevL->pairs.size() < 2) 
		return (prevL);
	LevelType *curL = new LevelType();

    int i = 0;
	while (i  < prevL->getSize() - 1) {
        if (prevL->pairs[i]->last < prevL->pairs[i + 1]->last)
		    curL->addPair(prevL->pairs[i], prevL->pairs[i + 1], prevL->pairs[i + 1]->last);
        else
			curL->addPair(prevL->pairs[i + 1], prevL->pairs[i], prevL->pairs[i]->last);
		i += 2;
		// count++;
    }
	if (i < prevL->getSize()) 
		curL->takeReminder(prevL->pairs[i]);
	levels.push_back(curL);
	
	return(intoPairs<Container, LevelType>(levels, l + 1)); 
}
 
 
template <template <typename, typename> class Container, typename LevelType>
Container <int, std::allocator <int> > mErGe(Container<LevelType*, std::allocator<LevelType*> >& levels, int l) {
	Container <int, std::allocator<int> > mainChain;
	for (int i = 0; i< levels[l]->getSize(); i ++) 
		mainChain.push_back(levels[l]->pairs[i]->right->last); 
	for (int lvl = l ; lvl > 0; lvl-- ){
		LevelType* level = levels[lvl];
		int Q = level->getSize(); 
		Container <int, std::allocator<int> > jNums = getJacobsNums<Container<int, std::allocator<int> > >(Q ); 
		
		Container <int, std::allocator<int> > rightIndexes (Q);
		for (int i = 0; i < Q; i ++) {
			
			int r = level->pairs[i]->right->last;
			for (int n = 0; n < static_cast<int>(mainChain.size()); n++)
				if (r == mainChain[n]) {
					rightIndexes[i] = n;
					break;
				}
		}
		int prevJ = -1; 
		for (int i = 0; i < static_cast<int>(jNums.size()); i++) {  
			int	limit = jNums[i] - 1;
			if (limit >= Q)
				limit = Q -  1;
			for (int idx = limit; idx > prevJ; idx--) {
				
				int l = level->pairs[idx]->left->last;
				int insertedPos = binInsert(mainChain, l, 0, rightIndexes[idx] - 1 );
				
				for (int k = 0; k < static_cast<int>(rightIndexes.size()); k++){
					if (insertedPos <= rightIndexes[k])
						rightIndexes[k] ++;
				}
			}
			prevJ = limit;
		}
		for (int i = levels[lvl]->rem.size() - 1; i >= 0; i--) 
			binInsert(mainChain, levels[lvl]->rem[i], 0, mainChain.size() - 1);
		
	}
 
	return mainChain;
}

int main(int argc, char **argv){ 
	std::clock_t start, vecEnd, deqEnd;
	
	if (argc!=2) 
		return 0;
    std::string s = argv[1];
	
	       
	std::vector<int> nums;
	int num;
	std::istringstream iss(s);
	while ((iss >> num)) {
		if (num < 0)
			return (std::cout << "negative number not accepted\n", 1);
		nums.push_back(num);}
	if (!iss.eof()){
		std::cerr << "Error: invalid input\n";
		return (1);
	}
	int s1ze = nums.size();

		std::cout<<"Before: ";
		for (size_t i = 0; i < nums.size(); i++)
			std::cout<< nums[i] << " "; 
					std::cout<< "\n"; 

		{
			start = std::clock();
			
			typedef Level<std::vector<pair*>, std::vector<int> > VecLevel; 
			VecLevel *level0 = new VecLevel;
			
			for (size_t i = 0; i < nums.size(); i++)
				level0->addPair(nums[i]); 

			std::vector <VecLevel *> levels; 
			levels.push_back(level0);
			
			intoPairs<std::vector<VecLevel *>, VecLevel>(levels, 0); 
			
			std::vector<int> res =  mErGe<std::vector, VecLevel>(levels, levels.size() - 1 ); 

			for (int i = 0; i < static_cast<int>(levels.size()); i++)
				delete(levels[i]);
			
			std::cout<<"After: ";
				print(res);

			vecEnd = std::clock();
			vecEnd -= start;
		}
		{	
			start = std::clock();

			typedef Level<std::deque<pair*>, std::deque<int> > DeqLevel; 
			DeqLevel *level0 = new DeqLevel;
			
			for (size_t i = 0; i < nums.size(); i++)
				level0->addPair(nums[i]); 

			std::deque <DeqLevel *> levels; 
			levels.push_back(level0);
			intoPairs<std::deque<DeqLevel *>, DeqLevel>(levels, 0); 
			
			std::deque<int> res =  mErGe<std::deque, DeqLevel>(levels, levels.size() - 1 );
			deqEnd = std::clock();
			deqEnd -= start;


			for (int i = 0; i < static_cast<int>(levels.size()); i++)
				delete(levels[i]);
			
		}

		std::cout << "Time to process a range of " << s1ze 
				<< " elements with std::vector: " 
				<< static_cast<double>(vecEnd) * 1e6 / CLOCKS_PER_SEC 
				<< " us" << std::endl;

		std::cout << "Time to process a range of " << s1ze 
				<< " elements with std::deque: " 
				<< static_cast<double>(deqEnd) * 1e6 / CLOCKS_PER_SEC 
				<< " us" << std::endl;
} 
