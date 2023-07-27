#include<iostream>
using namespace std;

class Complex {
	private:
		int a;
		int b;

		//全局函数 重载+运算符
		friend Complex operator+(Complex& c1, Complex& c2);
		//重载 前置++
		friend Complex& operator++(Complex& c1);
		friend Complex operator++(Complex& c1, int);  //通过一个占位符int来说明是后置++

	public:
		Complex(int a = 0, int b = 0) {
			this->a = a;
			this->b = b;
		}

		void printCom() {
			cout << a << " + " << b << "i" << endl;
		}

	public:

		//成员函数法 实现 -运算符
		Complex operator-(Complex& c2) { //当函数重载是成员函数时，并且是双操作数时，左操作数通过this指针隐式传递
			Complex tmp(this->a - c2.a, this->b - c2.b);
			return tmp;
		}

		//前置--, 当单目运算符重载作为成员函数时，操作数通过this指针隐式传递
		Complex& operator--() {
			this->a--;
			this->b--;
			return *this;
		}

		//后置--
		Complex operator--(int) {
			Complex tmp = *this;
			this->a--;
			this->b--;
			return tmp;
		}
};

Complex operator+(Complex& c1, Complex& c2) {
	Complex tmp(c1.a + c2.a, c1.b + c2.b);
	return tmp;
}


//前置++
Complex& operator++(Complex& c1) {
	c1.a++;
	c1.b++;
	return c1;
}

//后置++
Complex operator++(Complex& c1, int) {
	//先使用，再让c1加加
	Complex tmp = c1;
	c1.a++;
	c1.b++;
	return tmp;
}

/*
全局函数、类成员函数方法实现运算符重载步骤
	1）要承认操作符重载是一个函数，写出函数名称
	2）根据操作数，写出函数参数
	3）根据业务，完善函数返回值(看函数是返回引用 还是指针 元素)，及实现函数业务
*/
int main() {
	Complex c1(1, 2), c2(3, 4);


	//1	全局函数法 实现 + 运算符重载
	// Complex operator+(Complex &c1, Complex &c2);
	Complex c3 = c1 + c2;
	c3.printCom();  //输出4 + 6i

	//2 成员函数 法 实现 -运算符重载
	//c1.operator-(c2);
	//Complex operator-(Complex &c2)
	Complex c4 = c1 - c2;
	c4.printCom();  //输出 -2 + -2i

	//前置++操作符 用全局函数实现
	++c1;
	c1.printCom();  //输出 2 + 3i

	//前置--操作符 成员函数方法
	--c1;
	c1.printCom();   //输出 1 + 2i
	//Complex& operator++(Complex &c1)
	//c1.operator--();

	//后置++操作符 用全局函数实现
	c1++;
	c1.printCom();  //输出 2 + 3i

	//后置--操作符 用成员函数实现
	c1--;
	c1.printCom();  //输出 1+ 2i
	//c1.operator--()

	cout << "hello..." << endl;
	system("pause");
	return 0;
}
