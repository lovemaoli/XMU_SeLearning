#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

struct figure
{
	double a;
	double b;
	double c;
};

double cul_s(double x, double y, double z)
{
	double p = (x + y + z) / 2;
	if (x <= 0 || y <= 0 || z <= 0) throw 0;
	if (x + y > z && x + z > y && y + z > x)
		return sqrt(p * (p - x) * (p - y) * (p - z));
	else throw 0;
}

int main()
{
	ofstream out_file;
	out_file.open("out.txt", ios::app);

	double a, b, c, s;
	try
	{
		cout << "输入三个边长:";
		cin >> a >> b >> c;
		s = cul_s(a, b, c);
		cout << endl << "面积为:" << s;
		out_file << s << endl;
	}
	catch (int)
	{
		cout << "不能组成三角形,请重新输入三个边长:";
		cin >> a >> b >> c;
	}

	

	
	out_file.close();
	return 0;
}