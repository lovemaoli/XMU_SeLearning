#include<iostream>
using namespace std;
class Complex {
	private:
		double real;
		double im;
	public:
		Complex() {}
		Complex(double r, double i) {
			real=r;
			im=i;
		}
		Complex(const Complex &t) {
			real=t.real;
			im=t.im;
			cout<<"HAHA    ";
		}
		double getReal() const {
			return real;
		}
		Complex& operator+(Complex& other);//要求写函数，实现复数的加，对"+"进行重载
		friend istream& operator>>(istream &input,Complex &in) { ///要求写函数，实现对Complex对象的>>和<<操作
			input >> in.real >> in.im ;
			return input;
		}
		friend ostream& operator<<(ostream &output,Complex &out) {
			output << "(" << out.real << "+" << out.im << "i)" << endl;
			return output;
		}
//		friend ostream& operator<<(ostream &output,Complex out) { //为了适配返回值为对象的cout 
//			output << "(" << out.real << "+" << out.im << "i)" << endl;
//			return output;
//		}
		Complex& operator++();
		Complex& operator+=(Complex oth);
};
Complex tmp;
Complex& Complex::operator+(Complex& other) { //要求写函数，实现复数的加，对"+"进行重载
	tmp.real = real+other.real;
	tmp.im = im+other.im;
	return tmp;
}
Complex& Complex::operator++() {
	tmp.real = real;
	tmp.im = im;
	real++;
	return tmp;
}
Complex& Complex::operator+=(Complex oth){
	real += oth.real;
	im += oth.im;
	return *this;
}
int main() {
	Complex a,b,c;
	cin >> a >> b;
	cout << (b+=a);
	return 0;
}
