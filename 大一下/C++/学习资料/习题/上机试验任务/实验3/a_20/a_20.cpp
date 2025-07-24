#include <iostream>
#include <cstdlib>
using namespace std;

struct Node 
{
	int data;
	Node* next;
};

bool remove(Node*& h, int& a, int pos)
{
	bool x = true;
	Node* p1, * p2;

	if (pos == 0)x = false;

	else if (pos == 1)
	{
		p1 = h;
		h = h->next;
		a = p1->data;
		delete p1;
	} 

	else
	{
		p1 = h;
		p2 = h;
		int i=1,j=1;
		while (i < pos)
		{
			p1 = p1->next;
			i++;
			if (i < pos - 1 && p1 == NULL)x = false;
		}
		while (j < pos - 1)
		{
			p2 = p2->next;
			j++;
		}

		if (p1->next == NULL)
		{
			p2->next = NULL;
			a = p1->data;
			delete p1;
		}
		else
		{
			p2->next = p1->next;
			a = p1->data;
			delete p1;
		}
	}

	return x;
}