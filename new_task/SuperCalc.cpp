#include <iostream>
#include <stack>
#include "FormulaNode.h"
#include <map>
#include <functional>
#include <sstream>

std::map<char, std::function<double(double, double) >> operator_map =
{
	{'+', std::plus<double>()},
	{'-', std::minus<double>()},
	{'*', std::multiplies<double>()},
	{'/', std::divides<double>()}
};

double calc_postfix(const std::string& formula_str) {
	std::stack<double> container;
	for (char curr : formula_str) {
		if (isdigit(curr)) {
			container.push(curr - '0');
			continue;
		}
		double right = container.top(); container.pop();
		double left = container.top(); container.pop();
		container.push(operator_map[curr](left, right));
	}
	return container.top();
}

class Formula {

	// 1: char -> out_str, in_str++
	// 2: char -> stack, in_str++
	// 3: stack -> out_str + stack.pop
	// 4: finish
	enum Action { char2str, char2stack, stack2str, finish };
	const Action ActionTable[5][6] =
	{
		//     0          +           -          *           /           N
		{    finish, char2stack, char2stack, char2stack, char2stack, char2str}, // 0
		{ stack2str,  stack2str,  stack2str, char2stack, char2stack, char2str}, // +
		{ stack2str,  stack2str,  stack2str, char2stack, char2stack, char2str}, // -
		{ stack2str,  stack2str,  stack2str,  stack2str,  stack2str, char2str}, // *
		{ stack2str,  stack2str,  stack2str,  stack2str,  stack2str, char2str}  // /
	};

	size_t ActionColumn(char curr) {
		switch (curr) {
		case   0: return 0;
		case '+': return 1;
		case '-': return 2;
		case '*': return 3;
		case '/': return 4;
		}
		if (isdigit(curr)) return 5;
		return 5;
	}

	size_t ActionRow(const std::stack<char>& container) {
		if (container.empty()) return 0;
		char curr = container.top();
		switch (curr) {
		case   0: return 0;
		case '+': return 1;
		case '-': return 2;
		case '*': return 3;
		case '/': return 4;
		}
		return 0;
	}

	std::map<char, std::function<FormulaNode* (FormulaNode*, FormulaNode*)>> node_map =
	{
		{'+', [](FormulaNode* left, FormulaNode* right) {return new PlusNode(left,right); } },
		{'-', [](FormulaNode* left, FormulaNode* right) {return new MinusNode(left,right); } },
		{'*', [](FormulaNode* left, FormulaNode* right) {return new MultNode(left,right); } },
		{'/', [](FormulaNode* left, FormulaNode* right) {return new DivNode(left,right); } },
	};

	FormulaNode* from_postfix(const std::string& postfix_str) {
		std::stack<FormulaNode*> nodes;
		for (char curr : postfix_str) {
			if (isdigit(curr)) {
				nodes.push(new NumNode(curr - '0'));
				continue;
			}
			FormulaNode* node;
			auto right = nodes.top(); nodes.pop();
			auto left = nodes.top(); nodes.pop();
			nodes.push(node_map[curr](left, right));
		}
		return nodes.top();
	}
	std::string infix_to_postfix(const std::string& infix_str) {
		std::stringstream str_stream;
		size_t in_idx = 0;
		Action action;
		std::stack<char> container;
		do {
			size_t col = ActionColumn(infix_str[in_idx]);
			size_t row = ActionRow(container);
			action = ActionTable[row][col];
			switch (action) {
			case char2str: str_stream << infix_str[in_idx++]; break;
			case char2stack: container.push(infix_str[in_idx++]); break;
			case stack2str: {
				str_stream << container.top();
				container.pop();
				break;
			}
			}
		} while (action != finish);
		return str_stream.str();
	}

	FormulaNode* _root;
public:
	Formula(const std::string& str, bool is_postfix = false) { _root = from_postfix(is_postfix ? str : infix_to_postfix(str)); }
	double calc() const { return _root ? _root->calc() : 0; }
	std::string str() const { return _root ? _root->str() : ""; }
	Formula(FormulaNode* node) : _root(node) {}
	Formula operator+(const Formula& f) const {
		return Formula(new PlusNode(_root, f._root));
	}
	~Formula() {
		if (_root) delete _root;
		_root = nullptr;
	}
	FormulaNode* copy() { return _root->copy(); }
};

int main() {
	setlocale(LC_ALL, "Rus");
	//"2+2" <-> "22+"
	//"4*(2+3)-5/2" <-> "23+4*52/-"
	//"2+(3*4)" <-> "234*+" <-> "34*2+"
	//wrong translation: "23+4*"
	//"-2" <-> "02-"

	//std::cout << calc_postfix("23+4*50/-") << std::endl;

	//Formula f("23+4*52/-");
	//Formula f("2+3*4-5/2");
	Formula x("234*+52/-", true);
	Formula y("2+3*4-5/2");
	Formula f = x + y;
	try {
		std::cout << f.str() << " = " << f.calc() << std::endl;
	}
	catch (const Error& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	system("pause");
	return 0;
}
