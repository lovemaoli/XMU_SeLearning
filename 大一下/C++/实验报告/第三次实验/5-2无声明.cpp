#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double max(double a=0,double b=0,double c=0) {
	if(a>=b && a>=c)return a;
	if(b>=a && b>=c)return b;
	return c;
}

int main() {
	cout << endl << "输入三个正整数:";
	double a,b,c;
	cin >> a >> b >> c;
	cout << "最大数为：" << max(a,b,c) << endl; 
	return 0;
}


