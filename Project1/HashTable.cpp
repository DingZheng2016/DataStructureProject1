#include "HashTable.h"

HashTable::HashTable()
{

}

HashTable::HashTable(LList<CharString> &s)
{
	LNode<CharString> *p = s.head->next;
	while (p != NULL) {
		link[hash(p->elem)].add(p->elem);
		p = p->next;
	}
}

HashTable::~HashTable()
{

}

int HashTable::hash(CharString& str)
{
	int hash_num = 0;
	int pnum = 12983;
	//for (int i = 0; i < str.len; ++i)
	//	printf("%d ", str.s[i]);

	for (int i = 0; i < str.len; ++i)
		hash_num = (hash_num + str.s[i] * pnum) % HASHMAXNUM;

	//printf("%d\n", hash_num);
	return hash_num;
}

bool HashTable::exist(CharString& str)
{
	int num = hash(str);
	LNode<CharString> *p = link[num].head->next;
	while (p != NULL) {
		if (p->elem.equal(str))
			return true;
		p = p->next;
	}
	return false;
}