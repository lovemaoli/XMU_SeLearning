#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
const int NUM = 32;

class A
{
public:
	static void* operator new(size_t size);
	static void operator delete (void* p);
private:
	static A* p_free;
	A* next;
};

A* A::p_free = nullptr;

void* A::operator new(size_t size)
{
	A* p;
	if (p_free == nullptr)
	{
		p_free = (A*)malloc(size * NUM);
		for (p = p_free; p != p_free + NUM - 1; p++)
			p->next = p + 1;
		p->next = nullptr;
	}

	p = p_free;
	p_free = p_free->next;
	memset(p, 0, size);
	return p;
}

void A::operator delete(void* p)
{
	((A*)p)->next = p_free;
	p_free = (A*)p;
}

