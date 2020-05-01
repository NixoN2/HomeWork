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
			return end();
		}
		
	}
	AvlTree<DictPair>::iterator erase(AvlTree<DictPair>::iterator it)
	{
		return _tree.erase(it);
	}
	AvlTree<DictPair>::iterator erase(Key key)
	{
		auto it = find(key);
		return _tree.erase(it);
	}
	//Value operator[](Key key) 
	//{
	//	auto it = find(key);
	//	return (*it).translate();
	//}
	friend class DictProxy;
	class DictProxy
	{
	private:
		Key _key;
	public:
		DictProxy(Key key) 
		{
			_key = key;
		}
		DictProxy& operator=(Value val)
		{
			auto it = find(_key);
			if (it == end())
			{
				DictPair pair(_key, val);
				push_back(pair);
			}
			else
			{
				(*it).setTranslate(val);
			}
		}
		operator String()
		{
			auto it = find(_key);
			return (*it).translate();
		}
		friend class Dictionary;
	};
	DictProxy operator[](const Key& key)
	{
		return DictProxy(key);
	}
	void erase(AvlTree<DictPair>::iterator beg, AvlTree<DictPair>::iterator ending)
	{
		auto iter = beg;
		if (beg == begin())
		{
			iter++;
			 erase(_tree.begin());
			 
		}
		if (ending == end())
		{
			erase(ending);
		}
		auto end_key = (*ending).word();
		while (iter != find(end_key))
			{
				iter = erase(iter);
				
			}

	}
	AvlTree<DictPair>::iterator begin() const { return _tree.begin(); }
	AvlTree<DictPair>::iterator end() const { return _tree.end(); }
};

