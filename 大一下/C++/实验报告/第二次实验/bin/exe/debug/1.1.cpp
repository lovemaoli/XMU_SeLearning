#include <iostream>
using namespace std;
int value=0;
void printvalue() {
	cout<<"Value="<<value;//第二行输出：输出2 
}
int main() {
	int value=0;
	value=1;
	cout<<"Value="<<value<<endl;//第一行输出：输出1 
	::value=2;
	printvalue();
	return 0;
}

