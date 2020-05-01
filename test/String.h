#pragma once
class String
{
	size_t _size;
	char* _data;
public:
	String(const char* str = "");
	String(int size);
	String(const String&);
	String(String&&);
	~String();

	size_t size() const;
	size_t length() const;
	const char* str() const;

	char& operator[](size_t idx) const;
	String& operator= (const String&);
	String& operator= (String&& str);

	String& operator+=(const String&);
	String  operator+ (const String&) const;

	bool operator==(const String& str) const;
	bool operator!=(const String& str) const;
	bool operator< (const String& str) const;
	bool operator<=(const String& str) const;
	bool operator> (const String& str) const;
	bool operator>=(const String& str) const;
};

#include <iostream>
std::ostream& operator<< (std::ostream&, const String&);
std::istream& operator>> (std::istream&, String&);