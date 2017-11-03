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
	TreeNode* findNodeWithClass(CharString&); //在整个html中寻找包含特定class的一个节点
	TreeNode* findNodeWithTag(CharString&); //在整个html中寻找包含特定tag的一个节点
	void extractInfo(CharString&);
};

#endif
