

#include <iostream>
#include "DictPair.h"
#include "String.h"
#include "AvlTree.h"
int main()
{
	AvlTree<DictPair> tree;
	DictPair pair("wind", "wind$");
	tree.push_back(pair);
}

