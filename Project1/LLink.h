#ifndef LLINK_H
#define LLINK_H


template<class T>
class LNode
{
public:
	T elem;
	LNode<T> *next, *pre;
	~LNode();
};

template<class T>
LNode<T>::~LNode()
{
}

template<class T>
class LList
{
public:
	LNode<T> *head, *tail;

public:
	LList();
	~LList();

	void add(T);
	void remove(LNode<T>*);
	int search(T);
};

template<class T>
LList<T>::LList()
{
	head = new LNode<T>;
	tail = head;
	head->next = NULL;
	head->pre = NULL;
}

template<class T>
LList<T>::~LList()
{
	delete head;
}

template<class T>
void LList<T>::add(T m)
{
	LNode<T> *p = new LNode<T>;
	p->next = NULL;
	p->pre = tail;
	p->elem = m;
	tail->next = p;
	tail = p;
}

template<class T>
void LList<T>::remove(LNode<T>* p)
{
	if (p->next != NULL) {
		p->pre->next = p->next;
		p->next->pre = p->pre;
	}
	else {
		tail = p->pre;
		tail->next = NULL;
	}
	delete p;
}

template<class T>
int LList<T>::search(T m)
{
	int t = 1;
	LNode<T> *p = head->next;
	while (p != NULL) {
		if (p->elem.equal(m))
			return t;
		p = p->next;
	}
	return -1;
}


#endif