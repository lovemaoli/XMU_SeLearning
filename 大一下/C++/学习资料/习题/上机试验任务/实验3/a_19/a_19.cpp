#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
	int data;
	Node* next;
};
bool insert(Node*& h, int a, int pos)
{
	Node* p1,*p2;
	Node *p0 = new Node;//开辟一个新的节点

	p0->data = a;
	bool x=true;
	
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
			if (i < pos - 1 && p1->next == NULL)
				x = false;   //在完成指针移动之前就指向了末尾，则操作失败
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
	return x;
}