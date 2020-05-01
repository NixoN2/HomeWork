#include "String.h"
#include <iostream>
String::String(const char* str)
{
	_size = strlen(str);
	_data = new char[_size + 1];
	memcpy(_data, str, _size + 1);
}

String::String(String&& str)
{
	std::cout << "hi";
	_size = str.size();
	_data = std::move(str._data);
	str._data = nullptr;
	str._size = 0;
}
String::String(int size)
{
	_size = size;
	_data = new char[_size + 1];
	_data[0] = '\0';
}

String::String(const String& str)
{
	_size = str._size;
	_data = new char[_size + 1];
	memcpy(_data, str._data, _size + 1);
}

String::~String()
{
	if (_data) delete[] _data;
	_data = nullptr;
	_size = 0;
}

size_t String::size() const
{
	return _size;
}

size_t String::length() const
{
	return strlen(_data);
}

const char* String::str() const
{
	return _data;
}

char& String::operator[](size_t idx) const
{
	if (idx < 0 || idx > _size)
		throw "out of string limits";
	return _data[idx];
}

String& String::operator=(const String& str)
{
	if (this != &str) {
		if (_data) delete[] _data;
		_size = str._size;
		_data = new char[_size + 1];
		//memcpy(_data, str._data, _size + 1);
		for (size_t i = 0; i <= _size; ++i)
			_data[i] = str._data[i];
	}
	return *this;
}

String& String::operator=(String&& str)

{
	if (this != &str) {
		if (_data) delete[] _data;
		_size = str._size;
		_data = str._data;
		str._data = nullptr;
		str._size = 0;
	}
	return *this;
}

String& String::operator+=(const String& str)
{
	String tmp(length() + str.length());
	memcpy(tmp._data, _data, length());
	memcpy(tmp._data + length(), str._data, length() + 1);
	return *this = tmp;
}

String String::operator+(const String& str) const
{
	return String(*this) += str;
}

bool String::operator==(const String& str) const
{
	return !((*this < str) || (str < *this));
}

bool String::operator!=(const String& str) const
{
	return (*this < str) || (*this > str);
}

bool String::operator<(const String& str) const
{
	return strcmp(_data, str._data) < 0;
}

bool String::operator<=(const String& str) const
{
	return !(*this > str);
}

bool String::operator>(const String& str) const
{
	return str < _data;
}

bool String::operator>=(const String& str) const
{
	return !(str < *this);
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	return out << str.str();
}

std::istream& operator>>(std::istream& in, String& str)
{
	char what[128];
	in.getline(what, 128);
	str = what;
	return in;
}