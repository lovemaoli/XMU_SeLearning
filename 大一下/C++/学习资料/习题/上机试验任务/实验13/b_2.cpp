#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

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
	vector<double> vec_s;
	string file_name;

	double a, b, c, s,no;
	cout << "输入序号(输入0结束输入):" << endl;
	cin >> no;
	
	while (no != 0)		//规定第一个输入0的时候表示结束
	{
		cout << "输入三个边长:";
		cin >> a >> b >> c;
		try
		{
			s = cul_s(a, b, c);
			cout << endl << "面积为:" << s;
			vec_s.push_back(s);
		}
		catch (int)
		{
			cout << "不能组成三角形,请重新输入三个边长:";
			cin >> a >> b >> c;
			s = cul_s(a, b, c);
			cout << endl << "面积为:" << s;
			vec_s.push_back(s);
		}

		cout<<  "输入序号(输入0结束输入):" << endl;
		cin >> no;
	}

	cout << "请输入想要打开的文件名:";
	cin >> file_name;

	out_file.open(file_name, ios::out|ios::app);
	for (int i = 0; i < vec_s.size(); i++)
		out_file << vec_s[i] << endl;
	
	out_file.close();
	return 0;
}