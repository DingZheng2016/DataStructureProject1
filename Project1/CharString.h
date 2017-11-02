#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <string>

#define CHARSTRING_SIZE_INIT 50
#define CHARSTRING_SIZE_INCREMENT 500

class CharString {
public:
	wchar_t *s;
	unsigned int len;
	unsigned int size;

public:
	CharString();
	CharString(CharString&);
	CharString(std::wstring);
	~CharString();
	
	//Interface
	void concat(std::wstring);
	void concat(wchar_t);
	void concat(CharString&);
	void assign(std::wstring);
	CharString& operator = (CharString&);
	bool equal(CharString&);
	int toInt();

	//Test
	void output(bool space = true);
	CharString& substring(int, int);
};

#endif