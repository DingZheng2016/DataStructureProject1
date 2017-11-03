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
	long long hash_num = 0;
	long long pnum = 10007;
	int ph[] = {281279 ,281291 ,281297 ,281317 ,281321 ,281327 ,281339 ,281353 ,281357 ,281363 ,281381 ,281419, 281423 ,281429 ,281431 };
	for (long long i = 0; i < str.len; ++i)
		hash_num = (hash_num + str.s[i] * pnum * ph[i % 15]) % HASHMAXNUM;
	return (int)hash_num;
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