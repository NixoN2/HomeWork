#include "DictPair.h"

DictPair::DictPair(const String& w, const String& t) : _word(w), _translate(t)
{
}

DictPair::DictPair(DictPair&& pair)
{
	_word = std::move(pair._word);
	_translate = std::move(pair._translate);
}

const String& DictPair::word() const
{
	return _word;
}

const String& DictPair::translate() const
{
	return _translate;
}

bool DictPair::operator<(const DictPair& pair) const
{
	return _word < pair._word;
}

bool DictPair::operator<=(const DictPair& pair) const
{
	return !(pair < *this);
}

bool DictPair::operator>(const DictPair& pair) const
{
	return pair < *this;
}

bool DictPair::operator>=(const DictPair& pair) const
{
	return !(*this < pair);
}

bool DictPair::operator==(const DictPair& pair) const
{
	return !((*this < pair) || (pair < *this));
}

bool DictPair::operator!=(const DictPair& pair) const
{
	return (*this < pair) || (pair < *this);
}

DictPair& DictPair::operator=(const DictPair& pair)
{
	_word = pair._word;
	_translate = pair._translate;
	return *this;
}

DictPair& DictPair::operator=(DictPair&& pair)
{
	_word = std::move(pair._word);
	_translate = std::move(pair._translate);
	return *this;
}

std::ostream& operator<<(std::ostream& out, const DictPair& pair)
{
	return out << pair.word() << ": " << pair.translate() << std::endl;
}

std::istream& operator>>(std::istream& in, DictPair& pair)
{
	char tmp[1024];
	in.getline(tmp, 1024);
	char* p = tmp;
	while ((*p != '$') && (*p)) ++p;
	if (*p) { *p = '\0'; ++p; }
	pair = DictPair(String(tmp), String(p));
	return in;
}