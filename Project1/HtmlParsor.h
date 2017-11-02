#ifndef HTMLPARSOR_H
#define HTMLPARSOR_H

#include "CharString.h"
#include "HtmlTree.h"

class HtmlParsor {
public:
	TreeNode* root;

public:
	HtmlParsor(CharString&);
	~HtmlParsor();

	//Interface
	TreeNode* findNodeWithClass(CharString&); //Return a node with the class name
	TreeNode* findNodeWithTag(CharString&); //Return a node with the tag name


	//test
	void output();
};

#endif
