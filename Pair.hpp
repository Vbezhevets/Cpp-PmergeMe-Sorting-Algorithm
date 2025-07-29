

#ifndef PAIR_HPP
#define PAIR_HPP
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
        pair(pair &other){
            left = other.left;
            right = other.right;
            last = other.last;
        };
       pair& operator=(const pair &other){
            if (&other == this)
              return *this;
            left = other.left;
            right = other.right;
            last = other.last;
        return *this;

        };


        ~pair(){};
        template <typename RemContainer>
        RemContainer goDeepTakeRight()  {
            RemContainer res;
            if (!left && !right){
                res.push_back(last);
                return  res;
            }
            if (right) {
                RemContainer rightSubtree = right->goDeepTakeRight<RemContainer>();
                res.insert(res.end(), rightSubtree.begin(), rightSubtree.end());
            }
            return res;			
        }

		
	}; 

#endif