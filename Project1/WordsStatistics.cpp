#include "WordsStatistics.h"
#include <fstream>

WordsStatistics::WordsStatistics() 
{

}

void WordsStatistics::add(CharString elem)
{
	LNode<CharString> *p = words.head->next;
	LNode<int> *pt = num.head->next;
	while (p) {
		if (p->elem.equal(elem)) {
			++pt->elem;
			return;
		}
		p = p->next;
		pt = pt->next;
	}
	words.add(elem);
	num.add(1);
	return;
}

void WordsStatistics::sort()
{
	LNode<int> *pt = num.head->next;
	LNode<CharString> *p = words.head->next;

	int n = 0;
	while (p) {
		++n;
		p = p->next;
	}
	p = words.head->next;

	for(int i = 0; i < n; ++i){			
		LNode<int> *temppt = pt;
		LNode<CharString> *tempp = p;
		for (int j = 0; j < n - i - 1; ++j) {
			if (temppt->elem < temppt->next->elem) {
				int temp = temppt->elem;
				temppt->elem = temppt->next->elem;
				temppt->next->elem = temp;
				CharString temps = tempp->elem;
				tempp->elem = tempp->next->elem;
				tempp->next->elem = temps;
			}
			tempp = tempp->next;
			temppt = temppt->next;
		}
	}
}

void WordsStatistics::output()
{

	std::wofstream wresultfile("output/WordsStatistics.csv");
	wresultfile << "\"·Ö´Ê\",\"ÊýÁ¿\"\n";
	LNode<CharString> *p = words.head->next;
	LNode<int> *pt = num.head->next;
	while (p) {
		wresultfile << "\"";
		for (int i = 0; i < p->elem.len; ++i)
			wresultfile << p->elem.s[i];
		wresultfile << "\",";
		wresultfile << pt->elem << std::endl;
		p = p->next;
		pt = pt->next;
	}
	wresultfile.close();
}