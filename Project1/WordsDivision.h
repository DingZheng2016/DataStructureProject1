#ifndef WORDSDIVISION
#define WORDSDIVISION

#include "HashTable.h"
#include "CharString.h"
#include "LLink.h"
#include "WordsStatistics.h"

#define MAXLEN 20

class WordsDivision {
private:
	HashTable *hashtable;
	LList<CharString> s;

public:
	WordsDivision();
	WordsDivision(std::string&);
	LList<CharString> divideWords(CharString&); //最大正向匹配法进行分词
	LList<CharString> divideWords(CharString&, WordsStatistics&);
	void initDictionary(std::string& dictname);
};

#endif