#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double calc(double a) { //正方形
	return a*a;
}
double calc(double a,double b) { //长方形
	return a*b;
}
double calc(double a,double b,double c) { //三角形
	return 0.5*a*b*sin(c);
}
double calc(double a,double b,double c,double d) { //梯形
	return (a+b)*c*0.5;
}

int main() {
	cout << endl << "输入形状：1正方形 2长方形 3三角形 4梯形 : ";
	int a,ans;
	cin >> a;
	if(a == 1) {
		double b;
		cin >> b;
		ans = calc(b);
	}
	if(a == 2) {
		double b,c;
		cin >> b >> c;
		ans = calc(b,c);
	}
	if(a == 3) {
		double b,c,d;
		cin >> b >> c >> d;
		ans = calc(b,c,d);
	}
	if(a == 4) {
		double b,c,d;
		cin >> b >> c >> d;
		ans = calc(b,c,d,1);
	}
	cout << "面积为：" << ans << endl; 
	return 0;
}

