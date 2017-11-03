#include "HtmlTree.h"

TreeNode::TreeNode(CharString tagname)
{
	children = new LList<TreeNode*>;
	content = new CharString;
	attrlist = new LList<attr>;
	tag = new CharString(tagname);
}

TreeNode::~TreeNode()
{
	delete content;
	delete tag;
	delete attrlist;
	del();
	delete children;
}

void TreeNode::del()
{
	LNode<TreeNode*> *p = children->head->next;
	LNode<TreeNode*> *q;
	while (p != NULL) {
		q = p->next;
		delete p->elem;
		p = q;
	}
}

void TreeNode::addAttr(attr& at)
{
	attrlist->add(at);
}

void TreeNode::addContent(CharString& str)
{
	content->concat(str);
}

void TreeNode::addChild(TreeNode* tn)
{
	children->add(tn);
}

TreeNode* TreeNode::findNodeWithClass(CharString& className)
{
	return pFindNodeWithClass(this, className);
}

TreeNode* TreeNode::pFindNodeWithClass(TreeNode* p, CharString &className)
{
	LNode<attr> *pAttr = p->attrlist->head->next;
	while (pAttr != NULL) {
		if (pAttr->elem.name.equal(CharString(L"class")))
			if (pAttr->elem.value.equal(className))
				return p;
		pAttr = pAttr->next;
	}
	LNode<TreeNode*> *pNode = p->children->head->next;
	while (pNode != NULL) {
		TreeNode *temp = pFindNodeWithClass(pNode->elem, className);
		if (temp != NULL)
			return temp;
		pNode = pNode->next;
	}
	return NULL;
}

TreeNode* TreeNode::findNodeWithTag(CharString& tagName)
{
	return pFindNodeWithTag(this, tagName);
}

TreeNode* TreeNode::pFindNodeWithTag(TreeNode* p, CharString &tagName)
{
	if (p->tag->equal(CharString(L"class")))
		return p;
	LNode<TreeNode*> *pNode = p->children->head->next;
	while (pNode != NULL) {
		TreeNode *temp = pFindNodeWithTag(pNode->elem, tagName);
		if (temp != NULL)
			return temp;
		pNode = pNode->next;
	}
	return NULL;
}

TreeNode* TreeNode::findChildWithTag(CharString& tagName, int n)
{
	LNode<TreeNode*> *pNode = this->children->head->next;
	int k = 0;
	while (pNode != NULL) {
		if (pNode->elem->tag->equal(tagName)) {
			if (k == n)
				return pNode->elem;
			++k;
		}
		pNode = pNode->next;
	}
	return NULL;
}