#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Pair.hpp"
template <typename PairsContainer, typename RemContainer>
class Level {

	private:

	Level(Level& other){
		pairs = other.pairs;
		rem = other.rem;
	}
	Level& operator=(Level& other){
		if (this == &other)
			return *this;
		pairs = other.pairs;
		rem = other.rem;
		return *this;
	}
	

	public:
		PairsContainer pairs;
		RemContainer  rem;
	Level() {};
	void addPair(int n) {
		pair *newPair = new pair(n);
		pairs.push_back(newPair);
	}
	void addPair(pair *small, pair* big, int last) {
		pair *newPair = new pair(small, big, last);
		pairs.push_back(newPair);
	}
	void takeReminder (pair *remPair){
		rem = remPair->goDeepTakeRight<RemContainer>(); 
	}
 
	int getSize(){
		return pairs.size();
	}

	~Level() {
		for (int i = 0; i < static_cast<int>(pairs.size()); i++) 
			delete(pairs[i]);
	}
};

#endif
