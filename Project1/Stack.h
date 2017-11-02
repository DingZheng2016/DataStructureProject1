#ifndef STACK_H
#define STACK_H

#define STACK_SIZE_INIT 2000
#define STACK_SIZE_INCREMENT 1000

template<class T>
class Stack {
private:
	T *data;
	int len;
	int size;

public:
	Stack();
	~Stack();

	//Interface
	void push(T);
	T top();
	void pop();
	bool empty();
};

template <class T>
Stack<T>::Stack()
{
	data = new T[STACK_SIZE_INIT];
	size = STACK_SIZE_INIT;
	len = 0;
}

template <class T>
Stack<T>::~Stack()
{
	delete[] data;
}

template <class T>
void Stack<T>::push(T elem)
{
	if (len + 1 >= size) {
		size += STACK_SIZE_INCREMENT;
		T *temp = new T[size];
		for (int i = 0; i < len; ++i)
			temp[i] = data[i];
		data = temp;
	}
	data[len++] = elem;
}

template <class T>
T Stack<T>::top()
{
	return data[len - 1];
}

template <class T>
void Stack<T>::pop()
{
	--len;
	return;
}

template <class T>
bool Stack<T>::empty()
{
	return len == 0;
}

#endif