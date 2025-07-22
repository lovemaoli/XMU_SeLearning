#include <iostream>
using namespace std;

struct node
{
	int data;
	node* next;
};

class Queue
{
	node* head;
public:
	Queue()
	{
		head = NULL;
	}
	Queue(const Queue& s)
	{
		node* p1,*p2;
		head = NULL;	//÷ÿ÷√head
		p1 = s.head;
		for (int i = 0; i < s.length(); i++,p1=p1->next)
		{
			insert(p1->data);
		}
	}
	~Queue()
	{
		node* p;
		p = head;
		head = NULL;
		if (p != NULL)
			delete[]p;
	}
	bool insert(int x);
	bool remove();
	int length()const;
};
int Queue::length()const
{
	int size = 1;
	for (node* p = head; p->next != NULL; p = p->next, size++);
	return size;
}

bool Queue::insert(int x)
{
	node* p1, * p2;
	int pos = length();
	p2 = new node;
	p2->data = x;
	p2->next = NULL;
	for (int i = 0; i < pos - 1; i++, p1 = p1->next);
	p1->next = p2;
}

bool Queue::remove()
{
	node* p1, * p2;
	p1 = head;
	p2 = p1->next;
	delete p1;
	head = p2;
}