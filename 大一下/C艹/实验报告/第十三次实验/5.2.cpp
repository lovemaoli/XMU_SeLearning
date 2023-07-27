#include <iostream>
using namespace std; 
class A {
	public:
		A(char *s) {
			cout<<s<<endl;
		}
};
class B:virtual public A {
	public:
		B(char *s1,char *s2):A(s1) {
			cout<<s2<<endl;
		}
};
class C:virtual public A {
	public:
		C(char *s1,char *s2):A(s1) {
			cout<<s2<<endl;
		}
};
class D:public B,public C {
	public:
		D(char *s1,char *s2,char *s3,char *s4):B(s1,s2),C(s3,s4),A(s1) {
			cout<<s4<<endl;
		}
};
int main()  {
	D d("Class A","class B","class C","class D");
}

