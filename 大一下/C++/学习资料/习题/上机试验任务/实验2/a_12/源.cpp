int path(int n)
{
	int res;
	if (n == 1)res = 1;
	if (n == 2)res = 1;
	if (n == 3)res = 2;
	else
	{
		if (n % 2 == 0)res = path(n - 1) + path(n - 2) + path(n - 3);
		else res = path(n - 1) + path(n - 2);
	}
	return res;
}