

#ifndef EX02_HPP
#define EX02_HPP
#include <climits>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <type_traits>
#include <vector>
#include <string>
#include <iostream>
#include <deque>



class pair {
	
	public:
		pair *left;
		pair *right;
		int	 last;

		pair() : left(nullptr), right(nullptr), last(INT_MIN) {};
		pair(int i) : left(nullptr), right(nullptr), last(i) {};
		pair(pair* small, pair *big, int i) : left(small), right(big), last(i)  {};

		std::vector<int> goDeep() ;

		std::vector <int> goDeepTakeRight() ;
	}; 
	
	std::vector<int>& operator+=(std::vector<int>& v,  pair const *other); //only for reminder
		


class Level {
	public:
	std::vector <pair *> pairs; /// сделать шаблон вместо вектора
	std::vector<int> rem;
};



void printLevels(const std::vector<Level>& levels) ; 
void printVector(const std::vector<int>& v);
int jacob( int n);
std::vector <int> getJacobsNums(int n);

// void printQ(std::deque<std::vector<int> >& q, char c);
// void printV(std::vector<int>& p);
#endif
