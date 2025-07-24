#include <iostream>
using namespace std;

class A{
private:
	A() {};
public:
	static A* getinstance()
	{
		static A* a=nullptr;
		if (a == nullptr)
			a = new A;
		return a;
	}
};