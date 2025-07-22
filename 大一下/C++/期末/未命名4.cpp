#include <iostream>
using namespace std;
class A {
	public:
		A() {
			f();
			cout << "A::A()" << endl;
		}
		virtual ~A() {
			cout << "~A"<< endl;
		}
		virtual void f() {
			cout << "A::f"<< endl;
		}
		void g() {
			cout << "A::g"<< endl;
		}
		void h() {
			f();
			g();
		}
};
class B: public A {
	public:
		B(){
			cout << "B::B()" << endl;
		}
		~B(){
				cout << "~B"<< endl;
			};
		void f() {
			cout << "B::f"<< endl;
		};
		void g() {
			cout << "B::g"<< endl;
		};
};
int main() {
	B b; //调用 B::B(), A::A()和 A::f
//	A a;
	A *p;
	p=&b;
	delete p; //调用_____(3)___
	cout << endl;
}
