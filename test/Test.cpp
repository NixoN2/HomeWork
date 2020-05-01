

#include <iostream>
#include "DictPair.h"
#include "String.h"
#include "AvlTree.h"
#include "Dictionary.h"
int main()
{
	
	DictPair pair1("wind", "wind&");
	DictPair pair2("earth", "earth&");
	DictPair pair3("water", "water&");
	Dictionary<String, String> dict;
	dict.push_back(pair1);
	dict.push_back(pair2);
	dict.push_back(pair3);
	auto it = dict.erase(dict.begin());
}





/*AvlTree<DictPair> tree;
	DictPair pair("wind", "wind$");
	tree.push_back(pair);
	auto it = tree.begin();
	std::cout << (*it).word();*/
	/*std::cout << dict["wind"];*/
	/*std::cout << *it << std::endl;*/