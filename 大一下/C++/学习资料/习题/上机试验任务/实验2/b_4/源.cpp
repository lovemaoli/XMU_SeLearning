#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void trf(int n)
{
	int i;
	i = n / 10;
	if (i)trf(i);
	putchar(n % 10 + '0');
}
int main()
{
	int n;
	cin >> n;
	trf(n);
	return 0;
}