#include <iostream>
using namespace std; 
template <class T>
T minn(T a,T b) {
	if (a<b)
		return a;
	else
		return b;
}
template <class T,class P>
T minn(T a,P b) {
	if (a<b)
		return a;
	else
		return b;
}
int main()  {
	int i1=10,i2=20;
	double d1=3.5,d2=1.2;
	char c1='b',c2='x';
	cout<<minn(i1,i2)<<endl;
	cout<<minn(d1,d2)<<endl;
	cout<<minn(c1,c2)<<endl;
	cout<<minn(i1,c2)<<endl;
	cout<<minn(i1,d2)<<endl;
}

