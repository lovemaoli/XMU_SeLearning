#include <iostream>
using namespace std;

struct node
{
	int data;
	node* next;
};

void reverse(node* head)
{
	node* p, * q, * t;
	p = head->next;
	q = q->next;
	t = NULL;
	while (q != NULL)
	{
		t = q->next;
		q->next = p;
		p = q;
		q = t;
	}
	head->next = p;
}