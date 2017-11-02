#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include "CharString.h"
#include "Stack.h"
#include "GetHTML.h"
#include "CSVReader.h"
#include "HtmlParsor.h"

#define FILE_SIZE 1024 * 1024

using namespace std;

int main()
{

	CSVReader csvReader("url.csv");
	char* url;
	
	freopen("result.csv", "w", stdout);

	printf("\"序号\",\"网址\",\"发帖大类\",\"发帖小类\",\"发帖标题\",\"发帖内容\",\"发帖人\",\"发帖日期\",\"发帖类型\",\"分词结果\"\n");

	for (int i = 1; i <= 100; ++i) {

		//++++++Get And Save HTML++++++
		url = csvReader.getUrl();
		printf("%d,", i);
		cout << "\"" << url << "\",";
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

		wchar_t wch;
		CharString html;
		wifstream infs16("a.html");
		int len = 0;
		while (infs16.read(&wch, 1))html.concat(wch);
		HtmlParsor dom(html);
		TreeNode* p = dom.findNodeWithClass(CharString(L"z"));
		if (p != NULL) {
			TreeNode *p1 = p->findChildWithTag(CharString(L"a"), 2);
			if (p1) {
				printf("\"");
				p->findChildWithTag(CharString(L"a"), 2)->content->output(); 
				printf("\",");
			}
			else
				printf("NA,");
			p1 = p->findChildWithTag(CharString(L"a"), 3);
			if (p1) {
				printf("\"");
				p1->content->output();
				printf("\",");
			}
			else
				printf("NA,");
			p1 = p->findChildWithTag(CharString(L"a"), 4);
			if (p1) {
				printf("\"");
				p1->content->output(); 
				printf("\",");
			}
			else
				printf("NA,");
		}
		else {
			printf("NA,NA,NA,");
		}
			
		//++++++thread content++++++
		p = dom.findNodeWithClass(CharString(L"t_fsz"));
		if (p) {
			TreeNode *q = p->findChildWithTag(CharString(L"table"))->findChildWithTag(CharString(L"tr"))->findChildWithTag(CharString(L"td"));
			TreeNode *t = q->findChildWithTag(CharString(L"p"));
			printf("\"");
			if (t) {
				int j = 0;
				CharString *content = t->content;
				while (j + 7 < content->len) {
					if (content->s[j] == '&' && content->s[j + 1] == '#' && content->s[j + 7] == ';') {
						CharString sNumToBeDeocded = content->substring(j + 2, j + 7);
						int num = sNumToBeDeocded.toInt();
						wchar_t wcht = static_cast<wchar_t>(num);
						std::wcout.imbue(locale("chs"));
						std::wcout << wcht;
						j += 7;
					}
					++j;
				}
			}
			else {
				q->content->output(false);
			}
			printf("\",");
		}
		else {
			printf("NA,");
		}
		//------thread content------

		//author
		p = dom.findNodeWithClass(CharString(L"xw1"));
		if (!p)
			printf("NA,");
		else {
			printf("\"");
			p->content->output();
			printf("\",");
		}
		//------

		//date
		p = dom.findNodeWithClass(CharString(L"pti"));
		if (p) {
			TreeNode *p1 = p->findChildWithTag(CharString(L"div"), 1)->findChildWithTag(CharString(L"em"));
			CharString date = p1->content->substring(7, 15);
			printf("\"");
			date.output();
			printf("\",");
		}
		else
			printf("NA,");
		//p->content->output();
		
		//

		//type
		p = dom.findNodeWithClass(CharString(L"ts z h1"));
		if (p) {
			TreeNode* p1 = p->findChildWithTag(CharString(L"a"));
			CharString type = p1->content->substring(1, p1->content->len - 1);
			printf("\"");
			type.output();
			printf("\"");
		}
		else
			printf("NA");
		//printf(",");
		//fContent.output();
		//std::wcout.imbue(locale("chs"));
		//std::wcout << test << std::endl;
		printf("\n");
		//break;
	}
	//system("pause");
	return 0;
}
