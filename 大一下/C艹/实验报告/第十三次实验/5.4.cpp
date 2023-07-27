#include <iostream>
using namespace std;
class Base {
	public:
		virtual void disp() {
			cout<<"Base class"<<endl;
		}
};
class Derive1:public Base {
	public:
		void disp() {
			cout<<"Derive1 class"<<endl;
		}
};
class Derive2:public Base {
	public:
		void disp() {
			cout<<"Derive2 class"<<endl;
		}
};
void show(Base *p)  {
	p->disp();
}
int main()  {
	Base a;
	Derive1 b;
	Derive2 c;
	show(&a);
	show(&b);
	show(&c);
}

