#include<iostream>
using namespace std;
class A {
		int x;
	public:
		A(int i) {
			cout << "A"; 
			x=i;
		}
};
class B: virtual public A {
		int y;
	public:
		B(int i): A(1) {
			cout << "B"; 
			y=i;
		}
};
class C: virtual public A {
		int z;
	public:
		C(int i): A(2) {
			cout << "C"; 
			z=i;
		}
};
class D: public B, public C {
		int m;
	public:
		D(int i, int j, int k): C(j), B(i), A(3) {
			cout << "D"; 
			m=k;
		}
};

int main() {
	D d(1,2,3);
}
