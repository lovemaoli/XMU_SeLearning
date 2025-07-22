#include <iostream>
using namespace std;
class stack
{
	stack() { top = NULL; };
	bool push(int i);
	bool pop(int& i);
	struct Node
	{
		int data;
		Node* next;
	}*top;
};

bool stack::push(int i)
{
	Node* p = new Node;
	if (p == NULL)return false;
	else
	{
		p->data = i;
		p->next = top;
		top = p;
		return true;	
	}
}

bool stack::pop(int& i)
{
	if (top == NULL)return false;
	else
	{
		Node* p = top;
		top = top->next;
		i = p->data;
		delete p;
		return true;
	}
}