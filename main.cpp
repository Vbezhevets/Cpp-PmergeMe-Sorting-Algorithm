#include "ex02.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>

#include <ratio>

int count = 0; //!

int binInsert(std::vector<int> &v, int n, int left, int right) {
	// left = 0; 
	// right = v.size() - 1;
	
	while (left <= right){

		count++;
		
		int middle = left + (right - left) / 2;
		if (n < v[middle])
			right = middle - 1;
		else 
			left = middle + 1;
	}

	v.insert(v.begin() + left, n);
	return left;
}

Level *intoPairs(std::vector <Level *>& levels, int l){

	Level *prevL = levels[l];
	if (prevL->pairs.size() < 2)
		return (prevL);
	Level *curL = new Level();

    size_t i = 0;
	while (i  < prevL->getSize() - 1) {
        if (prevL->pairs[i]->last < prevL->pairs[i + 1]->last)
		    curL->addPair(prevL->pairs[i], prevL->pairs[i + 1], prevL->pairs[i + 1]->last);
        else
			curL->addPair(prevL->pairs[i + 1], prevL->pairs[i], prevL->pairs[i]->last);
		i += 2;
		count++;
    }
	if (i < prevL->getSize()) 
		curL->takeReminder(prevL->pairs[i]);
	levels.push_back(curL);
	return(intoPairs(levels, l + 1)); 
}
 

std::vector <int>  mErGe(std::vector <Level *>& levels, int l) {

	std::vector<int>  mainChain;
	while (l > 0 && levels[l]->getSize() <2) // if only 2 ints! - exclusion; //<3
		l--;

	for (size_t i = 0; i< levels[l]->getSize(); i ++) 
		mainChain.push_back(levels[l]->pairs[i]->right->last); // b₁
	
	for (int lvl = l ; lvl > 0; lvl-- ){
		Level* level = levels[lvl];
		int Q = level->getSize(); 
		std::vector<int> jNums = getJacobsNums(Q ); // 
		
		
		int prevJ = -1; 
		for (size_t i = 0; i < jNums.size(); i++) {   // 1, 3, 5, 11, 21
			int	limit = jNums[i] - 1;
			if (limit >= Q)
				limit = Q -  1;
			
			for (int idx = limit; idx > prevJ; idx--) {
				int w = level->pairs[idx]->right->last;
				int winPos = lower_bound(mainChain.begin(), mainChain.end(), w) - mainChain.begin();

				int l = level->pairs[idx]->left->last;
				binInsert(mainChain, l, 0, winPos - 1 );
			}
			prevJ = limit;
		}
		for (int i = levels[lvl]->rem.size() - 1; i >= 0; i--)
			binInsert(mainChain, levels[lvl]->rem[i], 0, mainChain.size() - 1);
	}
 
	return mainChain;
}


int main(int argc, char **argv){ 
	if (argc!=2) 
		return 0;
    std::string s = argv[1];
	
	std::istringstream iss(s);
	int num; 
    Level *level0 = new Level;
	
	while ((iss >> num)) {
		// std::cout<<num << std::endl;
		level0->addPair(num); }
    
	if (!iss.eof()){
		std::cerr << "Error: invalid input\n";
		return (1);
	} 

	std::cout<<"Before: "; 
	for (int i = 0; i < level0->getSize(); i++)
		std::cout<< level0->pairs[i]->last << " "; 

	std::vector <Level *> levels; 
	levels.push_back(level0);
	
	
	intoPairs(levels, 0); 
	std::cout << "\n";
	
	std::cout << "pair comparisons: " << count << "\n";

	std::vector<int> res =  mErGe(levels, levels.size() - 1 ); 
	printVector(res);
	std::cout << "Total comparisons: " << count << "\n";
	for (int i = 0; i < levels.size(); i++)
		delete(levels[i]);
	// std::cout << "11 2 17 0 16 8 6 15 10 3 21 1 18 9 76 14 19 12 5 4 20 13 7 \n"; 
	// std::cout << jacob(8);
} 