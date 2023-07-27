//备注，函数返回值为普通类型和返回值为引用他们之间的差别
#include <iostream>
using namespace std;
float temp;
float fn1(float r) {
	temp = r*r*3.14;
	return temp;
}
float& fn2(float r) {
	temp = r*r*3.14;
	return temp;
}
int main() {
	float a=fn1(5.0); //1 单独变量存储 fn1(5.0);
	const float& b=fn1(5.0); //2 fn1(5.0)返回的局部变量temp不能被c++接受为引用（局部变量不能被main修改） 故用const 
	float c=fn2(5.0); //3 申请变量c存储temp的当前值 
	float& d=fn2(5.0); //4 d为对temp的引用 
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
	cout << temp << endl;
	cout << "----------" << endl; 
	d=1.0;
	cout << temp << endl; 
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
}

