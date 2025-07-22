#include <iostream>
using namespace std;
//问题：在程序中，用户可以直接通过调用基类的函数使width和height不相等,改变部分函数的成员类型即可
class Rectangle
{
	double width;
	double height;
public:
	Rectangle(double w, double h) :width(w), height(h) {}
	void set_width(double w) { width = w; }
	void set_height(double h) { height = h; }
	double get_width() const { return width; }
	double get_height() const { return height; }
	double area()const { return width * height; }
	void print()const { cout << "width:" << width << "  height:" << height << endl; }
};

class Square :protected Rectangle
{
public:
	Square(double s) :Rectangle(s, s) {};

	void set_side(double s)
	{
		set_width(s);
		set_height(s);
	}

	double get_side() const
	{
		return get_width();
	}

	double Rectangle::area;

	void print() {
		cout << "side:" << get_width() << endl;
	}

};

int main()
{
	Square a(1);
	a.set_side(1);
	double b = a.get_side();
	cout << b;
}