#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
	int data;
	Node* next;
};
void insert(Node*& h, int a, int pos)
{
	Node* p1, * p2;
	Node* p0 = new Node;//开辟一个新的节点

	p0->data = a;

	if (pos == 0)
	{
		p1 = h;
		p0->next = p1;
		h = p0;
	}

	else
	{
		int i = 1;
		p1 = h;
		while (i < pos)
		{
			p1 = p1->next;
			i++;
		}	//使p1指向第pos个节点

		if (p1->next == NULL)
		{
			p1->next = p0;
			p0->next = NULL;
		}

		else
		{
			p2 = p1->next;
			p0->next = p2;
			p1->next = p0;
		}
	}
}
void remove(Node*& h, int pos)
{
	Node* p1, * p2;
	if (pos == 1)
	{
		p1 = h;
		h = h->next;
		delete p1;
	}

	else
	{
		p1 = h;
		p2 = h;
		int i = 1, j = 1;
		while (i < pos)
		{
			p1 = p1->next;
			i++;
		}
		while (j < pos - 1)
		{
			p2 = p2->next;
			j++;
		}

		if (p1->next == NULL)
		{
			p2->next = NULL;
			delete p1;
		}
		else
		{
			p2->next = p1->next;
			delete p1;
		}
	}
}
Node* sort(Node*h_b,Node*h_a)
{
	h_a = NULL;//用于储存新的链表

	Node* p1;
	int i = 1,j=1;
	p1 = h_b;
	insert(h_a, p1->data, 0);
	remove(h_b, 1);


	return h_a;
}