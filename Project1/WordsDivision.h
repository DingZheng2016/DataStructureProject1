#ifndef WORDSDIVISION
#define WORDSDIVISION

#include "HashTable.h"
#include "CharString.h"
#include "LLink.h"

#define MAXLEN 20

class WordsDivision {
private:
	HashTable *hashtable;
	LList<CharString> s;

public:
	WordsDivision();
	WordsDivision(std::string&);
	LList<CharString> divideWords(CharString&); //�������ƥ�䷨���зִ�
	void initDictionary(std::string& dictname);
};

#endif