#include "ex02.hpp"
#include <cstddef>
#include <iostream>
#include <ratio>



void binInsert(std::vector<int> &v, int n ) {

	int left = 0, right = v.size() - 1;
	
	while (left <= right){
		
		int middle = left + (right - left) / 2;
		if (n < v[middle])
			right = middle - 1;
		else 
			left = middle + 1;
	}

	v.insert(v.begin() + left, n);

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
    }
	
	if (i < prevL.pairs.size())
		curL.rem = prevL.pairs[i]->goDeepTakeRight(); 
		

	
	levels.push_back(curL);
	return(intoPairs(levels, l + 1));

}

// void binJacob(std::vector<pair *>& mainChain, std::vector<pair *>& pairs) {

// }


std::vector <int>  mErGe(std::vector <Level>& levels, int l) {

	std::vector<int>  mainChain;
	
	mainChain.push_back(levels[l].pairs[0]->right->last);

	
	for (int lvl = l ; lvl > 0; lvl-- ){
		int currLvlSize = levels[lvl].pairs.size();
		std::vector<int> jNums = getJacobsNums(currLvlSize );
		printVector(jNums);
		
		int j = 0;
		int prevJ = -1; 
		for (size_t i = 0; i < jNums.size(); i++) {
			if(i > 0)
				prevJ = jNums[i - 1] - 1;
			j = jNums[i] - 1;
			if (j >= currLvlSize)
				j = currLvlSize -  1;
	
			while (j > prevJ && j >= 0) {
				// std:: cout << " || lvl: " << lvl << " - inserting " << levels[lvl].pairs[j]->left->last << " now j: " << j << " prevJ: "<< prevJ<<"\n";
				binInsert(mainChain, levels[lvl].pairs[j]->left->last);

				j--;
			}

		}
		std::cout<< "\n";
		for (int i = levels[lvl].rem.size() - 1; i >= 0; i--) {
			binInsert(mainChain, levels[lvl].rem[i]);
			// std:: cout << "lvl " << lvl << " - inserting " << levels[lvl].rem[i] << "\n";

		}
	}
 
	return mainChain;
}


int main(){ 
	// if (argc!=2) return 0;
    std::string s;// = argv[1];
	s = "11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7 ";
	std::cout<<s<<std::endl;
    Level level0;
	
    char        delim = ' ';
    size_t      pos;
	
    while ((pos = s.find(delim)) != std::string::npos){
		std::string str = s.substr(0, pos);
		s.erase(0, pos + 1);
		pair *p = new pair((stoi(str)));
		level0.pairs.push_back(p);
    }
	std::vector <Level> levels; 
	levels.push_back(level0);
	intoPairs(levels, 0);
	printLevels(levels);
	std::vector<int> res =  mErGe(levels, levels.size() - 1 );
	printVector(res);
	std::cout << "11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7 \n"; 
	// std::cout << jacob(8);
} 