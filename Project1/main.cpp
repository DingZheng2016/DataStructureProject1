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
#include "WordsDivision.h"

#define FILE_SIZE 1024 * 1024

using namespace std;

int main()
{
	CSVReader csvReader("input/url.csv");
	char* url;
	
	wofstream wresultfile("output/result.csv");

	wresultfile << "\"���\",\"��ַ\",\"��������\",\"����С��\",\"��������\",\"��������\",\"������\",\"��������\",\"��������\",\"�ִʽ��\"\n";


	WordsDivision wordsdivision; 
	wordsdivision.initDictionary(string("config/dict"));//�����ֵ��ļ���������ϣ��
	

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

		printf("Getting Html...");
		GetHTML::getIns()->generate(domain, request);
		delete url;
		delete domain;
		delete request;
		//------Get And Save HTML------

		wofstream tempfile("temp/temp.txt"); //�洢���зִʵ��ı�

		wchar_t wch;
		CharString html;
		wifstream infs16("temp/temp.html"); 
		while (infs16.read(&wch, 1))html.concat(wch);

		printf("Parsing Html...");
		HtmlParsor dom;
		dom.extractInfo(html);//��html�ı��ļ�����Ϊ���νṹ

		//++++++�������ࡢ����С�ࡢ��������++++++
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
		//++++++�������ࡢ����С�ࡢ��������++++++
			
		//++++++��������++++++
		p = dom.findNodeWithClass(CharString(L"t_fsz"));
		if (p) {
			TreeNode *q = p->findChildWithTag(CharString(L"table"))->findChildWithTag(CharString(L"tr"))->findChildWithTag(CharString(L"td"));
			TreeNode *t = q->findChildWithTag(CharString(L"p"));
			wresultfile << "\"";
			if (t) { //�󲿷�html�ļ�td�º���p��ǩ����content��Ҫ����HtmlDecode
				int j = 0;
				CharString *content = t->content;
				while (j < content->len) {
					if (j + 7 < content->len && content->s[j] == '&' && content->s[j + 1] == '#' && content->s[j + 7] == ';') {
						CharString sNumToBeDeocded = content->substring(j + 2, j + 7);
						int num = sNumToBeDeocded.toInt();
						wchar_t wcht = static_cast<wchar_t>(num);
						wresultfile.imbue(locale("chs"));
						tempfile.imbue(locale("chs"));
						wresultfile << wcht;
						tempfile << wcht;
						j += 8;
					}
					else if (j + 4 < content->len && content->s[j] == '&' && content->s[j + 1] == '#' && content->s[j + 4] == ';') {
						CharString sNumToBeDeocded = content->substring(j + 2, j + 4);
						int num = sNumToBeDeocded.toInt();
						wchar_t wcht = static_cast<wchar_t>(num);
						wresultfile.imbue(locale("chs"));
						tempfile.imbue(locale("chs"));
						wresultfile << wcht;
						tempfile << wcht;
						j += 5;
					}
					else if (j + 6 < content->len && content->s[j] == '&' && content->s[j + 1] == '#' && content->s[j + 6] == ';') {
						CharString sNumToBeDeocded = content->substring(j + 2, j + 6);
						int num = sNumToBeDeocded.toInt();
						wchar_t wcht = static_cast<wchar_t>(num);
						wresultfile.imbue(locale("chs"));
						tempfile.imbue(locale("chs"));
						wresultfile << wcht;
						tempfile << wcht;
						j += 7;
					}
					else if (j + 5 < content->len && content->s[j] == '&' && content->s[j + 1] == 'n' && content->s[j + 2] == 'b'
								&& content->s[j + 3] == 's' && content->s[j + 4] == 'p' && content->s[j + 5] == ';' ) {
						wresultfile.imbue(locale::classic());
						tempfile.imbue(locale::classic());
						wresultfile << " ";
						tempfile << " ";
						j += 6;
					}
					else {
						wresultfile.imbue(locale::classic());
						tempfile.imbue(locale::classic());
						wresultfile << content->s[j];
						tempfile << content->s[j];
						++j;
					}
				}
				wresultfile.imbue(locale::classic());
			}
			else { //�ٲ���html�ļ�td��ǩֱ�Ӱ��������������������HtmlDecode
				int j = 0;
				while (j < q->content->len) {
					if (j + 5 < q->content->len && q->content->s[j] == '&' && q->content->s[j + 1] == 'n' && q->content->s[j + 2] == 'b'
						&& q->content->s[j + 3] == 's' && q->content->s[j + 4] == 'p' && q->content->s[j + 5] == ';') {
						wresultfile << " ";
						tempfile << " ";
						j += 6;
					}
					else if (q->content->s[j] != ' ' && q->content->s[j] != '\n') {
						wresultfile << q->content->s[j];
						tempfile << q->content->s[j];
						++j;
					}
					else
						++j;
				}
			}
			wresultfile << "\",";
		}
		else {
			wresultfile << "NA,";
		}
		//------��������------

		//++++++������++++++
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
		//------������------

		//++++++��������++++++
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
		//------��������------

		//++++++��������++++++
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
		//------��������------

		tempfile.close();

		//++++++�ִʽ��++++++
		wifstream intemp("temp/temp.txt");
		CharString tempstr;
		wchar_t dwch;
		while (intemp.read(&dwch, 1))
			tempstr.concat(dwch);

		LList<CharString> lsegre = wordsdivision.divideWords(tempstr); //���طִʽ������
		
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
		//------�ִʽ��------

		wresultfile << "\n";
		printf("->result.csv\n");
	}
	wresultfile.close();
	return 0;
}
