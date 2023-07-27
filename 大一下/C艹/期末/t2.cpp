#include<iostream>
using namespace std;
class myclass {
		int x;
	public:
		myclass(int i) {
			cout << "A"; 
			x=i;
		}
		myclass(const myclass &i){
			cout << "B";
			x=i.x; 
		}
};


int main() {
	myclass obj=10;
	myclass obj2=obj;
}
