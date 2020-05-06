#pragma once
#include <string>
#include "Errors.h"

class FormulaNode {
public:
	virtual double calc() const = 0;
	virtual std::string str() const = 0;
	virtual FormulaNode* copy() = 0;
	virtual ~FormulaNode() {}
};

class NumNode : public FormulaNode {
    double _num;
public:
	NumNode(double num) : _num(num) {}
	NumNode(const NumNode& node) { _num = node._num; }
	NumNode(const NumNode&& node) { _num = std::move(node._num); }
	double calc() const override { return _num; }
	NumNode* copy() { NumNode* node = &NumNode(_num); return node; }
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
	PlusNode* copy() { PlusNode* node = &PlusNode(_left, _right); return node; }
};

class MinusNode : public BinNode {
public:
	MinusNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override { return _left->calc() - _right->calc(); }
	std::string str() const override { return _left->str() + " - " + _right->str(); }
	MinusNode* copy() { MinusNode* node = &MinusNode(_left, _right); return node; }
};

class MultNode : public BinNode {
public:
	MultNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override { return _left->calc() * _right->calc(); }
	std::string str() const override { return "(" + _left->str() + ")*(" + _right->str() + ")"; }
	MultNode* copy() { MultNode* node = &MultNode(_left, _right); return node; }
};

class DivNode : public BinNode {
public:
	DivNode(FormulaNode* left, FormulaNode* right) : BinNode(left, right) {}
	double calc() const override {
		if (_right->calc() == 0) throw ErrorDivByZero();
		return _left->calc() / _right->calc();
	}
	std::string str() const override { return "(" + _left->str() + ")/(" + _right->str() + ")"; }
	DivNode* copy() { DivNode* node = &DivNode(_left, _right); return node; }
};
