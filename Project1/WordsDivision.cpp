#include "WordsDivision.h"
#include <iostream>
#include <fstream>

WordsDivision::WordsDivision()
{
	hashtable = NULL;
}

WordsDivision::WordsDivision(std::string& dictname)
{

	hashtable = NULL;
	initDictionary(dictname);
}

void WordsDivision::initDictionary(std::string& dictname)
{
	delete hashtable;
	while (s.head->next != NULL)
		s.remove(s.head->next);

	std::wifstream in(dictname);
	int dict_len = 0;
	wchar_t dwch;

	printf("**********Start Reading Dict File**********\n");
	wchar_t dwcht[100];
	while (in.getline(dwcht, 256)) {
		s.add(CharString(dwcht));
	}
	in.close();
	printf("**********End Reading Dict File**********\n\n");

	printf("**********Start Building Hash Table**********\n");
	hashtable = new HashTable(s);
	printf("**********End Building Hash Table**********\n\n");
}

LList<CharString> WordsDivision::divideWords(CharString& s)
{
	int max_len = 15;
	int tk = 0;
	int current;
	LList<CharString> lsegre;
	while (tk < s.len)
	{
		current = max_len;
		while (current >= 2) {
			CharString mstr = s.substring(tk, tk + current);
			if (hashtable->exist(mstr))
			{
				LNode<CharString> *pN = lsegre.head->next;
				bool existed = false;
				while (!existed && pN) {
					if (pN->elem.equal(mstr))
						existed = true;
					pN = pN->next;
				}
				if (!existed)
					lsegre.add(mstr);
				break;
			}
			--current;
		}
		tk += current;
	}
	return lsegre;
}