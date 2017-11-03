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

	TreeNode* findNodeWithClass(CharString&);//�ڸýڵ��������Ѱ�Ұ����ض�class��һ���ڵ�
	TreeNode* findNodeWithTag(CharString&);//�ڸýڵ�������а����ض�tag��һ���ڵ�
	TreeNode* findChildWithTag(CharString& tagName, int n = 0);//�ڸýڵ�Ķ�����Ѱ�ҵ�һ�������ض�tag�Ľڵ�

private:
	TreeNode* pFindNodeWithClass(TreeNode*, CharString&);//�ݹ�Ѱ��
	TreeNode* pFindNodeWithTag(TreeNode*, CharString&);//�ݹ�Ѱ��
	void del();
};

#endif