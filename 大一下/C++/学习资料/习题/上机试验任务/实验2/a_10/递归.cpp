double hm1(int n, double x)
{
	double res;
	if (n == 0)
		res = 1;
	if (n == 1)
		res = 2 * x;
	else	
		res = 2 * x * hm1(n - 1, x) - 2 * (n - 1) * hm1(n - 2, x);
	return res;
}