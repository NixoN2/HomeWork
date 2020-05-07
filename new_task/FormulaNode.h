#pragma once
#include <string>
#include "Errors.h"
#include <cmath>
class FormulaNode {
public:
	virtual double calc() const = 0;
	virtual std::string str() const = 0;
	virtual FormulaNode* copy() const = 0;
	virtual ~FormulaNode() {}
};

class NumNode : public FormulaNode {
    double _num;
public:
	NumNode(double num) : _num(num) {}
	NumNode(const NumNode& node) { _num = node._num; }
	NumNode(const NumNode&& node) { _num = std::move(node._num); }
	double calc() const override { return _num; }
	NumNode* copy() const override { NumNode* node = new NumNode(_num); return node; }
	std::string str() const override { return std::to_string(_num); }

};

class BinNode : public FormulaNode {
protected:
	FormulaNode* _left, * _right;
public:
	BinNode(FormulaNode* left, FormulaNode* right) : _left(left), _right(right) {}
	BinNode(const BinNode& node) : _left(node._left), _right(node._right) {}
	BinNode(const BinNode&& node)
	{
		_left = std::move(node._left);
		_right = std::move(node._right);
	}
	~BinNode() {
		if (_left) delete _left;
		if (_right) delete _right;
		_left = _right = nullptr;
	}
};

class PlusNode : public BinNode {
public:
	PlusNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override { return _left->calc() + _right->calc(); }
	std::string str() const override { return _left->str() + " + " + _right->str(); }
	PlusNode* copy() const override { PlusNode* node = new PlusNode(_left->copy(), _right->copy()); return node; }
};

class MinusNode : public BinNode {
public:
	MinusNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override { return _left->calc() - _right->calc(); }
	std::string str() const override { return _left->str() + " - " + _right->str(); }
	MinusNode* copy() const override { MinusNode* node = new MinusNode(_left->copy(), _right->copy()); return node; }
};

class MultNode : public BinNode {
public:
	MultNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override { return _left->calc() * _right->calc(); }
	std::string str() const override { return "(" + _left->str() + ")*(" + _right->str() + ")"; }
	MultNode* copy() const override { MultNode* node = new MultNode(_left->copy(), _right->copy()); return node; }
};

class DivNode : public BinNode {
public:
	DivNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override {
		if (_right->calc() == 0) throw ErrorDivByZero();
		return _left->calc() / _right->calc();
	}
	std::string str() const override { return "(" + _left->str() + ")/(" + _right->str() + ")"; }
	DivNode* copy() const override { DivNode* node = new DivNode(_left->copy(), _right->copy()); return node; }
};
class PowNode : public BinNode {
public: 
	PowNode(FormulaNode* left, FormulaNode* right) : BinNode(left,right) {}
	double calc() const override {
		return pow(_left->calc(), _right->calc());
	}
	std::string str() const override { return "(" + _left->str() + ")^(" + _right->str() + ")"; }
	PowNode* copy() const override { PowNode* node = new PowNode(_left->copy(), _right->copy()); return node; }
};
