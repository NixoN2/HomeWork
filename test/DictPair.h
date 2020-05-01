#pragma once

#include "String.h"

class DictPair {
	String _word;
	String _translate;
public:
	DictPair(const String& w = "", const String& t = "");
	DictPair(DictPair&&);
	const String& word() const;
	const String& translate() const;
	DictPair& operator=(const DictPair&);
	DictPair& operator=(DictPair&&);
	bool operator< (const DictPair&) const;
	bool operator<=(const DictPair&) const;
	bool operator> (const DictPair&) const;
	bool operator>=(const DictPair&) const;
	bool operator==(const DictPair&) const;
	bool operator!=(const DictPair&) const;

};

#include <iostream>

std::ostream& operator<< (std::ostream& out, const DictPair&);
std::istream& operator>> (std::istream& in, DictPair&);
