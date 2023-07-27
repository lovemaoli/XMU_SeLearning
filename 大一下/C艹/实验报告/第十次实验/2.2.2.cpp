#include <iostream>
using namespace std;

class Complex {
	private:
		double real;
		double im;
	public:
		Complex(){}
		Complex(double r, double i) {
			real=r;
			im=i;
		}
		Complex(Complex &t) {
			real=t.real;
			im=t.im;
			cout<<"HAHA    ";
		}
		Complex Add(Complex &a) { //要求完善代码，实现复数的加
			Complex tmp(a.real+real,a.im+im);
			return tmp;
		}
		friend Complex Add2(Complex &a,Complex &b);
		void display()	 {
			cout<<real<<":"<<im;
		}
};

Complex Add2(Complex &a,Complex &b) { //要求完善代码，实现复数的加
	Complex tmp(a.real+b.real,a.im+b.im);
	return tmp;
}

int main() {
	Complex p1(11,12),p2(13,14);
	Complex c1,c2;
	c1=p1.Add(p2);
	c2=Add2(p1,p2);
	c1.display();
	c2.display();
	return 1;
}

