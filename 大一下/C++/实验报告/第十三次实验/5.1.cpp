#include <iostream>
using namespace std; 
class root1 {
	public:
		root1() {
			cout<<"执行root1类的构造函数"<<endl;
		}
};
class root2 {
	public:
		root2() {
			cout<<"执行root2类的构造函数"<<endl;
		}
};
class mid:public root1,virtual public root2 {
	public:
		mid() {
			cout<<"执行mid类的构造函数"<<endl;
		}
};
class top:public mid {
	public:
		top() {
			cout<<"执行top类的构造函数"<<endl;
		}
};
int main() {
	top t;
}

