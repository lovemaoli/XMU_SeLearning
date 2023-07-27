#include <iostream>
using namespace std;
class Sample{
	private:
		int x;
	public:
		Sample( ) {} //考虑为何要写这个
		Sample(int a) {
			x=a;
		}
		void disp( ) {
			cout<<"x="<<x<<endl;
		}
		void operator=(Sample s);
};
void Sample::operator=(Sample s){
	x=s.x;
}
int main( ){
	Sample obj1(10),obj3(30);
	Sample obj2;
//	obj1=obj2=obj3;
	(obj1=obj2)=obj3;
	obj1.disp();
	obj2.disp();
}

