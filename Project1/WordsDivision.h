#ifndef WORDSDIVISION
#define WORDSDIVISION

#include "HashTable.h"
#include "CharString.h"
#include "LLink.h"

class WordsDivision {
private:
	HashTable *hashtable;
	LList<CharString> s;

public:
	WordsDivision();
	WordsDivision(std::string&);
	LList<CharString> divideWords(CharString&);
	void initDictionary(std::string& dictname);
};

#endif