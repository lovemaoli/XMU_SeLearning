#include <iostream>
using namespace std;
int digit(int x, int y)
{
	int i=0;
	int m=0;//´¢´æÔËËãÎ»Êı
	int n;
	int result;
	if (x == 0||y==0)result = 0;
	else
	{
		for (i = 1; i <y; i++)
		{
			x /= 10;
		}
		result = x % 10;
	}
	return result;
}
int main()
{
	int a, b,c;
	cin >> a;
	cin >> b;
	c = digit(a, b);
	cout << c;
	return 0;
}