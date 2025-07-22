#include <iostream>
using namespace std;
int add(const int &i, const int & j);
int main() {
	int a=20;
	int b=30;
	cout<<a<<"+"<<b<<"="<<add(a,b)<<endl;
	return 0;
}
int add(const int &i, const int & j)  {
	i=i+30;
	j=j-10;
	return i+j;
}

