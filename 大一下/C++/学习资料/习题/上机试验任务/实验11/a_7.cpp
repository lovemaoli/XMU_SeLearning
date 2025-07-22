#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;
int n = 0;
int x = 3;

void add_bigger_than_3(int a) {
	if (a > 3)n += a;
}

int main()
{
	vector<int> vec;

	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(1);

	for_each(vec.begin(), vec.end(), add_bigger_than_3);

	cout << n;
}