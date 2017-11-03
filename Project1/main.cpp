#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include "CharString.h"
#include "Stack.h"
#include "GetHTML.h"
#include "CSVReader.h"
#include "HtmlParsor.h"
#include "HashTable.h"

#define FILE_SIZE 1024 * 1024

using namespace std;

CharString s[300000];

int main()
{
	CSVReader csvReader("input/url.csv");
	char* url;
	
	wofstream wresultfile("output/result.csv");

	wresultfile << "\"序号\",\"网址\",\"发帖大类\",\"发帖小类\",\"发帖标题\",\"发帖内容\",\"发帖人\",\"发帖日期\",\"发帖类型\",\"分词结果\"\n";

	
	wifstream in("config/dict");
	int dict_len = 0;
	wchar_t dwch;

	printf("**********Start Reading Dict File**********\n");
	/*
	while (in.read(&dwch, 1)) {
		if (dwch != '\n') {
			s[dict_len].concat(dwch);
		}
		else {
			//s[dict_len].output(); printf(" ");
			++dict_len;
		}
	}*/
	
	wchar_t dwcht[100];
	while (in.getline(dwcht, 256)) {
		s[dict_len++] = CharString(dwcht);
	}
	in.close();
	printf("**********End Reading Dict File**********\n\n");
	
	printf("**********Start Building Hash Table**********\n");
	HashTable *hTable = new HashTable(s, dict_len);
	printf("**********End Building Hash Table**********\n\n");
	


	for (int i = 1; i <= 100; ++i) {

		//++++++Get And Save HTML++++++
		printf("%d Start...", i);
		url = csvReader.getUrl();
		wresultfile << i << ",\"" << url << "\",";
		if (url == NULL)
			continue;
		char* domain = new char[100];
		char* request = new char[100];
		int mid = 0;
		while (url[++mid] != '/');
		for (int i = 0; i < mid; ++i)
			domain[i] = url[i];
		domain[mid] = '\0';
		for (int i = mid; i < strlen(url); ++i)
			request[i - mid] = url[i];
		request[strlen(url) - mid] = '\0';
		GetHTML::getIns()->generate(domain, request);
		//GetHTML::getIns()->generate("bbs.cehome.com", "thread-615254-1-1.html");
		delete domain;
		delete request;
		//------Get And Save HTML------

		wofstream tempfile("temp/temp.txt");

		wchar_t wch;
		CharString html;
		wifstream infs16("temp/temp.html");
		//int len = 0;
		while (infs16.read(&wch, 1))html.concat(wch);
		HtmlParsor dom(html);
		TreeNode* p = dom.findNodeWithClass(CharString(L"z"));
		if (p != NULL) {
			TreeNode *p1 = p->findChildWithTag(CharString(L"a"), 2);
			if (p1) {
				wresultfile << "\"";
				for (int j = 0; j < p1->content->len; ++j)
					wresultfile << p1->content->s[j];
				wresultfile << "\",";
			}
			else
				wresultfile << "NA,";
			p1 = p->findChildWithTag(CharString(L"a"), 3);
			if (p1) {
				wresultfile << "\"";
				for (int j = 0; j < p1->content->len; ++j)
					wresultfile << p1->content->s[j];
				wresultfile << "\",";
			}
			else
				wresultfile << "NA,";
			p1 = p->findChildWithTag(CharString(L"a"), 4);
			if (p1) {
				wresultfile << "\"";
				for (int j = 0; j < p1->content->len; ++j)
					wresultfile << p1->content->s[j];
				wresultfile << "\",";
				for (int j = 0; j < p1->content->len; ++j)
					tempfile << p1->content->s[j];
				tempfile << "\n";
			}
			else
				wresultfile << "NA,";
		}
		else {
			wresultfile << "NA,NA,NA,";
		}
			
		//++++++thread content++++++
		p = dom.findNodeWithClass(CharString(L"t_fsz"));
		if (p) {
			TreeNode *q = p->findChildWithTag(CharString(L"table"))->findChildWithTag(CharString(L"tr"))->findChildWithTag(CharString(L"td"));
			TreeNode *t = q->findChildWithTag(CharString(L"p"));
			wresultfile << "\"";
			if (t) {
				int j = 0;
				CharString *content = t->content;
				wresultfile.imbue(locale("chs"));
				tempfile.imbue(locale("chs"));
				while (j + 7 < content->len) {
					if (content->s[j] == '&' && content->s[j + 1] == '#' && content->s[j + 7] == ';') {
						CharString sNumToBeDeocded = content->substring(j + 2, j + 7);
						int num = sNumToBeDeocded.toInt();
						wchar_t wcht = static_cast<wchar_t>(num);
						wresultfile << wcht;
						tempfile << wcht;
						j += 7;
					}
					++j;
				}
				wresultfile.imbue(locale::classic());
			}
			else {
				for (int j = 0; j < q->content->len; ++j)
					if(q->content->s[j] != ' ' && q->content->s[j] != '\n')
						wresultfile << q->content->s[j];
			}
			wresultfile << "\",";
		}
		else {
			wresultfile << "NA,";
		}
		//------thread content------

		//author
		p = dom.findNodeWithClass(CharString(L"xw1"));
		if (!p)
			wresultfile << "NA,";
		else {
			wresultfile << "\"";
			wresultfile.imbue(locale::classic());
			for (int j = 0; j < p->content->len; ++j)
				wresultfile << p->content->s[j];
			wresultfile << "\",";
		}
		//------

		//date
		p = dom.findNodeWithClass(CharString(L"pti"));
		if (p) {
			TreeNode *p1 = p->findChildWithTag(CharString(L"div"), 1)->findChildWithTag(CharString(L"em"));
			CharString date = p1->content->substring(7, 15);
			wresultfile << "\"";
			for (int j = 0; j < date.len; ++j)
				wresultfile << date.s[j];
			wresultfile << "\",";
		}
		else
			wresultfile << "NA,";
		//p->content->output();
		
		//

		//type
		p = dom.findNodeWithClass(CharString(L"ts z h1"));
		if (p) {
			TreeNode* p1 = p->findChildWithTag(CharString(L"a"));
			CharString type = p1->content->substring(1, p1->content->len - 1);
			wresultfile << "\"";
			for (int j = 0; j < type.len; ++j)
				wresultfile << type.s[j];
			wresultfile << "\",";
		}
		else
			wresultfile << "NA,";
		

		tempfile.close();

		wifstream intemp("temp/temp.txt");
		CharString tempstr;
		while (intemp.read(&dwch, 1))
			tempstr.concat(dwch);

		int max_len = 10;
		int tk = 0;
		int current;
		LList<CharString> lsegre;
		while (tk < tempstr.len)
		{
			current = max_len;
			while (current >= 2) {
				CharString mstr = tempstr.substring(tk, tk + current);
				if (hTable->exist(mstr))
				{
					LNode<CharString> *pN = lsegre.head->next;
					bool existed = false;
					while (!existed && pN) {
						if (pN->elem.equal(mstr))
							existed = true;
						pN = pN->next;
					}
					if(!existed)
						lsegre.add(mstr);
					break;
				}
				else
					;//printf("no");
				--current;
			}
			tk += current;
		}
		LNode<CharString> *pN = lsegre.head->next;
		if (pN == NULL)
			wresultfile << "NA";
		else {
			wresultfile << "\"";
			while (pN) {
				for (int j = 0; j < pN->elem.len; ++j)
					wresultfile << pN->elem.s[j];
				wresultfile << " ";
				pN = pN->next;
			}
			wresultfile << "\"";
		}
		wresultfile << "\n";
		printf("->result.csv\n");
	}
	wresultfile.close();
	//system("pause");
	return 0;
}
