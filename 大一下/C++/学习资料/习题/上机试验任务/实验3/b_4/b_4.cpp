#include <iostream>
#include <cstdlib>
using namespace std;

struct Node 
{
	int data;
	Node* next;
};

void remove_last(Node*& h, int& a)
{
	Node* p;
	p = h;
	int i = 1;
	int j = 0;//j表示i的上一个节点
	while (p->next != NULL)
	{
		p = p->next;
		i++;
		j++;
	}

	a = p->data;
	delete p;//将删除的值储存在a中，删除节点

	p = h;//重置p，将h赋给p
	i = 1;

	while (i < j)
		p = p->next;
	p->next = NULL;
}