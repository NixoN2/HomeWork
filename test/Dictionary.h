#pragma once

#include "AvlTree.h"
#include "DictPair.h"
#include <iostream>
template<typename Key, typename Value>
class Dictionary
{
private:
	AvlTree<DictPair> _tree;
public:
	Dictionary() { ; }
	void push_back(const DictPair& pair)
	{
		_tree.push_back(pair);
	}
	void clear()
	{
		_tree.clear();
	}
	size_t size()
	{
		return _tree.size();
	}
	AvlTree<DictPair>::iterator find(Key key)
	{
		for (auto it = begin(); it != end(); ++it)
		{
			if ((*it).word() == key)
			{
				return AvlTree<DictPair>::iterator(it);
			}
		}
		return end();
	}
	AvlTree<DictPair>::iterator erase(AvlTree<DictPair>::iterator it)
	{
		return _tree.erase(it);
	}
	Value& operator[](Key key) const
	{
		auto it = find(key);
		return (*it).translate();
	}
	AvlTree<DictPair>::iterator erase(Key key)
	{
		auto it = find(key);
		return _tree.erase(it);
	}
	AvlTree<DictPair>::iterator begin() const { return _tree.begin(); }
	AvlTree<DictPair>::iterator end() const { return _tree.end(); }
};

