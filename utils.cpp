#include "ex02.hpp"
#include <vector>

inline std::vector <int> pair:: goDeep()  {
		std::vector<int> res;
		if (!left && !right){
			res.push_back(last);
			return  res;
		}
        if (left) {
		    std::vector<int> leftSubtree = left->goDeep();
            res.insert(res.end(), leftSubtree.begin(), leftSubtree.end());
        }
        if (right) {
            std::vector<int> rightSubtree = right->goDeep();
            res.insert(res.end(), rightSubtree.begin(), rightSubtree.end());
        }
		return res;			
	}

    int jacob( int n) {
        if (n <= 1)
            return 1;
        return (jacob(n - 1) + 2 * jacob(n - 2));
    }

    std::vector <int> getJacobsNums(int n) {
        std::vector <int> jnums;
        int j = 0;
        int i = 1;
        while (j - 1 < n){
            j = jacob(i);
            jnums.push_back(j);
            i++;
            std::cout << "for " << i << " j = " << j << "\n";
        }
        return jnums;
    }

  std::vector <int> pair:: goDeepTakeRight()  {
		std::vector<int> res;
		if (!left && !right){
			res.push_back(last);
			return  res;
		}
        // if (left) {
		//     std::vector<int> leftSubtree = left->goDeep();
        //     res.insert(res.end(), leftSubtree.begin(), leftSubtree.end());
        // }
        if (right) {
            std::vector<int> rightSubtree = right->goDeepTakeRight();
            res.insert(res.end(), rightSubtree.begin(), rightSubtree.end());
        }
		return res;			
	}


std::vector<int>& operator+=(std::vector<int>& v,  pair  *other) { //only for reminder
	
	std::vector<int> res = other->goDeep(); //take leafs of the odd pair
	v.insert(v.end(), res.begin(), res.end());
	return v;
}

void printPairSubtree(pair* node, int indent = 0) {
    if (!node) return;
    // отступ
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    if (!node->left && !node->right) {
        // это лист
        std::cout << "Leaf: " << node->last << "\n";
    } else {
        // это внутренняя пара
        // std::cout << "Node last=" << node->last << "\n";
        std::cout << "Node last=" << node->last << "\n";

        // печатаем левое поддерево
        printPairSubtree(node->left, indent + 1);
        // печатаем правое поддерево (если есть)
        printPairSubtree(node->right, indent + 1);
    }
}
void printLevels(const std::vector<Level>& levels) {
    for (size_t lvl = 0; lvl < levels.size(); ++lvl) {
        const Level& L = levels[lvl];
        std::cout << "=== Level " << lvl
                  << "  (pairs: " << L.pairs.size()
                  << ", reminder subtree:)\n";
        // печатаем все полные пары
        for (size_t i = 0; i < L.pairs.size(); ++i) {
            std::cout << "Pair[" << i << "] subtree:\n";
            std::cout <<"\n";		

            printPairSubtree(L.pairs[i], 1);
        }
        // печатаем reminder как целое поддерево
        if (!L.rem.empty()) {
            std::cout << "Reminder:\n";
			for (size_t i = 0; i < L.rem.size(); ++i) 
				std::cout << " " << L.rem[i] << " ";
        }
        std::cout << "\n";
    }
}
void printVector(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) 
        std::cout << " " << v[i] << " ";
    std::cout << "\n";
}