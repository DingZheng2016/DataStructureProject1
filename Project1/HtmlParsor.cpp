#include "HtmlParsor.h"
#include "Stack.h"

HtmlParsor::HtmlParsor(CharString &str)
{
	int i = 0;
	Stack<TreeNode*> nodest;
	CharString tagname;
	root = NULL;
	while (i < str.len)
	{
		if (str.s[i] == '<')
		{
			++i;
			if (str.s[i] == '!')
				while(i < str.len && str.s[i++] != '>');
			else if (str.s[i] == '/') {
				int k = ++i;
				while (i < str.len && str.s[i] != ' ' && str.s[i] != '>')++i;
				CharString tagname = str.substring(k, i);
				while (!nodest.empty()) {
					if (nodest.top()->tag->equal(tagname)) {
						nodest.pop();
						break;
					}
					nodest.pop();
				} 
				++i;
			}
			else {
				int k = i;
				while (str.s[i] != ' ' && str.s[i] != '>')++i;
				tagname = str.substring(k, i);
				//tagname.output();
				TreeNode* node = new TreeNode(tagname);
				if (root == NULL)
					root = node;
				if (!nodest.empty()) {
					TreeNode *p = nodest.top();
					p->addChild(node);
				}
				nodest.push(node);

				attr att;
				while (str.s[i] == ' ')++i;
				while (str.s[i] != '>') {
					if (str.s[i] == '/' && str.s[i + 1] == '>') {
						++i;
						nodest.pop();
						break;
					}
					else{
						int k = i;
						while (str.s[i] != ' ' && str.s[i] != '=')++i;
						att.name = str.substring(k, i);
						while (str.s[i] != '"')++i;
						k = i;
						while (str.s[++i] != '"');
						att.value = str.substring(k + 1, i);
						++i;
						//att.name.output();
						//att.value.output();
						node->addAttr(att);
					}
					while (str.s[i] == ' ')++i;
				}

				//getchar();

				++i;
			}
		}
		else {
			if (!nodest.empty()) {
				int k = i;
				while (i < str.len && str.s[i] != '<')++i;
				nodest.top()->addContent(str.substring(k, i));
			}
			else
				++i;
		}
	}
}

HtmlParsor::~HtmlParsor()
{
	delete root;
}

TreeNode* HtmlParsor::findNodeWithClass(CharString& className)
{
	return root->findNodeWithClass(className);
}

TreeNode* HtmlParsor::findNodeWithTag(CharString& tagName)
{
	return root->findNodeWithClass(tagName);
}


//Test
void HtmlParsor::output()
{
	printf("****HTML Parsor Test****\n");

	LNode<TreeNode*> *p = root->children->head->next->next->elem->children->head->next;

	while (p != NULL) {
		p->elem->tag->output();
		p = p->next;
	}
	
	printf("************************\n");
}