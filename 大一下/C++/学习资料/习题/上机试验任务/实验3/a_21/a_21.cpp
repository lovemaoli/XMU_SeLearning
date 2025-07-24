#include <iostream>
#include <cstdlib>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct Node
{
	int data;
	Node *next;
};
//规定输入-1为表示链表结束
Node* Create()
{
	Node *h = NULL;
	Node* p1=NULL, * p2=NULL;	//p1总是用来创建新的节点
	p1 = new Node;
	h = p1;
	int x;
	cin >> x;	//输入第一个数字
	while (x != -1)
	{
		p2 = p1;
		p2->data = x;
		p1 = p2->next;
		p1 = new Node;

		cin >> x;
	}
	p2->next = NULL;//如果输入-1,上个节点就是结束点，-1不计入链表
	delete p1;
	return h;
}

void insert(Node* h, int a)
{
	Node* p1 = NULL, * p2 = NULL;
	if (h == NULL)
	{
		h = new Node;
		h->data = a;
		h->next = NULL;
	}
	else
	{
		p1 = h;
		while (p1->next != NULL)
			p1 = p1->next;

		p2 = new Node;//创建新节点
		p1->next = p2;
		p2->data = a;//将要输入的值输入节点中
		p2->next = NULL;
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

int main()
{
	Node* h1=NULL, * h2=NULL;
	Node* h3 = NULL, * h4 = NULL,*h5=NULL;
	Node* Create();
	void insert(Node * h, int a);
	void remove(Node * h,  int pos);

	
	h1 = Create();
	cout << endl;	//输入第一个链表
	h2 = Create();
	cout << endl;	//输入第二个链表

	Node* p1 = NULL , * p2=NULL;
	for (p1 = h1; p1->next != NULL; p1 = p1->next)
		insert(h3, p1->data);	//将h1代表的链表赋值给h3;

	for(p1=h1;p1->next!=NULL;p1=p1->next)
		for (p2 = h2; p2->next != NULL; p2 = p2->next)
			if (p1->data != p2->data)insert(h3, p2->data);		//求并集并存储进h1表示的链表

	cout << "并集：";
	for (p1 = h3; p1->next != NULL; p1 = p1->next)
		cout << p1->data << " ";
	cout << endl;		//输出并集


	for (p1 = h1; p1->next != NULL; p1 = p1->next)
		for (p2 = h2; p2->next != NULL; p2 = p2->next)
			if (p1->data == p2->data)insert(h4, p2->data);			//求交集

	cout << "交集：";
	for (p1 = h4; p1->next != NULL; p1 = p1->next)
		cout << p1->data << " ";		
	cout << endl;		//输出交集

	for (p1 = h3; p1->next != NULL; p1 = p1->next)
		insert(h5, p1->data);//将集合3复制给集合5

	int i=1;
	for (p1 = h4; p1->next != NULL; p1 = p1->next)
		for (i = 1, p2 = h3; p2->next != NULL; p2 = p2->next, i++)
			if (p1->data == p2->data)remove(h5, i);		//求差集

	cout << "差集：";
	for (p1 = h5; p1->next != NULL; p1 = p1->next)
		cout << p1->data << " ";
	cout << endl;//输出差集
}