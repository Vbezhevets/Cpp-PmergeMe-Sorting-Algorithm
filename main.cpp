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

Level intoPairs(std::vector <Level>& levels, int l){

	Level& prevL = levels[l];
	if (prevL.pairs.size() < 2)
		return (prevL);
	
    Level curL;
	pair *newPair;

    size_t i = 0;
	while (i  < prevL.pairs.size() - 1) {
        if (prevL.pairs[i]->last < prevL.pairs[i + 1]->last)
		    newPair = new pair(prevL.pairs[i], prevL.pairs[i + 1], prevL.pairs[i + 1]->last);
        else
			newPair = new pair(prevL.pairs[i + 1], prevL.pairs[i], prevL.pairs[i]->last);
		i += 2;
        curL.pairs.push_back(newPair);
		count++;
    }
	
	if (i < prevL.pairs.size()) 
		curL.rem = prevL.pairs[i]->goDeepTakeRight();  
	

	
	levels.push_back(curL);
	return(intoPairs(levels, l + 1)); 

}

// void binJacob(std::vector<pair *>& mainChain, std::vector<pair *>& pairs) {

// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector <int>  mErGe(std::vector <Level>& levels, int l) {

	std::vector<int>  mainChain;
	while (l > 0 && levels[l].pairs.size() <2) // if only 2 ints! - exclusion; //<3
		l--;

	for (size_t i = 0; i< levels[l].pairs.size(); i ++) 
		mainChain.push_back(levels[l].pairs[i]->right->last); // b₁
	
	for (int lvl = l ; lvl > 0; lvl-- ){
		Level& level = levels[lvl];
		int Q = level.pairs.size(); 
		std::vector<int> jNums = getJacobsNums(Q ); // 
		
		std::cout << "Q: " << Q << "jacob numbers for lvl " << lvl << " :"; printVector(jNums);
		
		int prevJ = -1; 
		for (size_t i = 0; i < jNums.size(); i++) {   // 1, 3, 5, 11, 21
			int	limit = jNums[i] - 1;
			if (limit >= Q)
				limit = Q -  1;
			
			for (int idx = limit; idx > prevJ; idx--) {
				int w = level.pairs[idx]->right->last;
				int winPos = lower_bound(mainChain.begin(), mainChain.end(), w) - mainChain.begin();

				int l = level.pairs[idx]->left->last;
				binInsert(mainChain, l, 0, winPos - 1 );
			}
			prevJ = limit;
		}
		for (int i = levels[lvl].rem.size() - 1; i >= 0; i--)
			binInsert(mainChain, levels[lvl].rem[i], 0, mainChain.size() - 1);
	}
 
	return mainChain;
}


int main(){ 
	// if (argc!=2) return 0;
    std::string s;// = argv[1];
	// s = "11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7 ";
	// s = "35962 5075 1825 91279 69392 67304 ";
	s = "22805 2014 87459 7912 1921 66115 73378 95497 21018 19247 50485 10916 30914 94957 58260 12847 58836 81996 18607 50917 46057 38902";
	// s = "25905 76879 67125 5855 81048 93272 59090 70792 64797 61994 8600 8777 48391 29123 40384 41141 67069 12146 1825 47437 52129 40954 80586 3778 45653 52509 72307 49861 34108 66147 22974 19648 19562 87699 41843 90020 79216 96508 39228 41169 25404 14251 45469 15773 82199 50768 96446 57040 23828 45620 62120 89701 70799 95776 31246 1784 32917 63649 44701 65535 93504 7908 29198 74622 69810 39488 70281 68027 74324 36044 30676 75258 79172 63328 15618 83627 15449 9462 88437 88342 56304 29459 49192 84329 91394 70411 99987 18249 37541 89127 62030 75529 8199 44978 55941 45731 7227 52818 64725 45428";
	std::cout<<s<<std::endl;
    Level level0;
	
	std::istringstream iss(s);
	int num; 

	while ((iss >> num)){
		pair *p = new pair(num);
		level0.pairs.push_back(p);
    }
	std::vector <Level> levels; 
	levels.push_back(level0);	

	intoPairs(levels, 0);
	// printLevels(levels);
	std::cout << "pair comparisons: " << count << "\n";

	std::vector<int> res =  mErGe(levels, levels.size() - 1 ); 
	printVector(res);
	std::cout << "Total comparisons: " << count << "\n";
	// std::cout << "11 2 17 0 16 8 6 15 10 3 21 1 18 9 76 14 19 12 5 4 20 13 7 \n"; 
	// std::cout << jacob(8);
} 