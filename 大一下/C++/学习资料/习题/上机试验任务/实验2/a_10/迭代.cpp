#include <iostream>
using namespace std;
double hm2(int n, double x)
{
	int i;
	double res, res1,res2;
	if (n == 0)res = 1;
	if (n == 1)res = 2 * x;
	else
	{
		res1 = 1;
		res2 = 2 * x;
		for (i = 2; i <= n; i++)
		{
			res = 2 * x * res2 - 2 * (i - 1) * res1;
			res1 = res2;
			res2 = res;
		}
	}
	return res;
}