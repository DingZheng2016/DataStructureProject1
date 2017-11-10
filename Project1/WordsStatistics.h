#ifndef WORDSSTATISTICS_H
#define WORDSSTATISTICS_H

#include "CharString.h"
#include "LLink.h"

class WordsStatistics {
private:
	LList<CharString> words;
	LList<int> num;

public:
	WordsStatistics();
	void add(CharString);

	void sort();
	void output();
};

#endif