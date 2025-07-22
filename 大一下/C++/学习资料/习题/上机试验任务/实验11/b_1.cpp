#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool small(int& x,int &y)
{
	return x > y;
}
int main()
{

	bool small(int& x, int& y);
	int a[10] = { 1,3,5,7,9,2,4,6,8,10 };
	sort(&a[0],&a[9]);

	vector<int> b;
	for (int i = 0; i < 10; i++)
		b.push_back(a[i]);

	sort(b.begin(), b.end(), small);

	for (int i = 0; i < 11; i++)
		cout << b[i] << " ";

	


	cout << b.capacity();
}

