#pragma once
#include <string>

class Error {
public:
	virtual std::string what() const { return "Error"; }
};

class ErrorDivByZero : public Error {
public:
	std::string what() const override { return "Division by zero"; }
};
