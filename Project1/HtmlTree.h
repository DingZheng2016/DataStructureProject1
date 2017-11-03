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

	TreeNode* findNodeWithClass(CharString&);//在该节点的子孙中寻找包含特定class的一个节点
	TreeNode* findNodeWithTag(CharString&);//在该节点的子孙中包含特定tag的一个节点
	TreeNode* findChildWithTag(CharString& tagName, int n = 0);//在该节点的儿子中寻找第一个包含特定tag的节点

private:
	TreeNode* pFindNodeWithClass(TreeNode*, CharString&);//递归寻找
	TreeNode* pFindNodeWithTag(TreeNode*, CharString&);//递归寻找
	void del();
};

#endif