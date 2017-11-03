#ifndef HTMLPARSOR_H
#define HTMLPARSOR_H

#include "CharString.h"
#include "HtmlTree.h"

class HtmlParsor {
public:
	TreeNode* root;

public:
	HtmlParsor(CharString&);
	HtmlParsor();
	~HtmlParsor();

	//Interface
	TreeNode* findNodeWithClass(CharString&); //������html��Ѱ�Ұ����ض�class��һ���ڵ�
	TreeNode* findNodeWithTag(CharString&); //������html��Ѱ�Ұ����ض�tag��һ���ڵ�
	void extractInfo(CharString&);
};

#endif
