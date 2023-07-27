#include <iostream>
using namespace std;
int f(int *p) {
	int y;
	y=(*p)*2;
	(*p)++;
	return y;
}
int main( ) {
	int x;
	x=10;
	cout<<x+f(&x)<<endl;
	cout<<x<<endl; 
	return 0;
}

