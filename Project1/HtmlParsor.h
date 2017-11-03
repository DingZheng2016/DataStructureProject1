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
	TreeNode* findNodeWithClass(CharString&); //Return a node with the class name
	TreeNode* findNodeWithTag(CharString&); //Return a node with the tag name
	void extractInfo(CharString&);

	//test
	void output();
};

#endif
