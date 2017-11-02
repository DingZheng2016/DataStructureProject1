#ifndef HTMLTREE_H
#define HTMLTREE_H

#include "CharString.h"
#include "LLink.h"

struct attr {
	CharString name;
	CharString value;
};

class TreeNode {
public:
	CharString *tag;
	LList<TreeNode*> *children;
	LList<attr> *attrlist;
	CharString *content;

public:
	TreeNode(CharString);
	~TreeNode();
	void addAttr(attr&);
	void addContent(CharString&);
	void addChild(TreeNode*);

	TreeNode* findNodeWithClass(CharString&);
	TreeNode* findNodeWithTag(CharString&);
	TreeNode* findChildWithTag(CharString& tagName, int n = 0);

private:
	TreeNode* pFindNodeWithClass(TreeNode*, CharString&);
	TreeNode* pFindNodeWithTag(TreeNode*, CharString&);
	void del();
};

#endif