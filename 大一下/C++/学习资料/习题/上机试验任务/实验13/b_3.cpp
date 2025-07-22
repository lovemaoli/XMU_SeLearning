#include <iostream>
using namespace std;

double product1(double a, double b)
{
	if (b == 0)throw 1;
	else return a / b;
}

double product2(double a, double b)
{
	if (b == 0)throw 1.0;
	else return a / b;
}

void func()
{
	cout << "catch";
}

int main()
{
	double x, y,p;		//用除法进行验证
	cout << "比较数据类型:" << endl;
	cout << "请输入做除法的两个数字：" << endl;
	cin >> x >> y;

	try 
	{
		product1(x, y);
	}
	catch (int)
	{
		func();
	}

	try
	{
		product2(x, y);
	}
	catch (int)
	{
		func();
	}

	return 0;
}