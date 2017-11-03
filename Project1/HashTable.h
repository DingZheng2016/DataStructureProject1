#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HASHMAXNUM 1000000
#include "CharString.h"
#include "LLink.h"

class HashTable {
private:
	LList<CharString> link[HASHMAXNUM];
public:
	HashTable();
	HashTable(LList<CharString> &);
	~HashTable();
	bool exist(CharString&);
	
private:
	int hash(CharString&);
	
};

#endif