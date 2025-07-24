#include <iostream>
using namespace std;

class A
{
public:
	virtual A* create() {
		return new A;
	}
};

class B :public A
{
public:
	A* create() {
		return new B;
	}
};

int main()
{
	A* p;
	if (1)p = new A;
	else p = new B;
	A* q;
	q = p->create();//使用动态绑定，定义为A类的指针，可以指向A的派生类B，采用动态绑定
}