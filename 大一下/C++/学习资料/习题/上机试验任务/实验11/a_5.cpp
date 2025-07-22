#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void quick_sort(vector<int>::iterator first, vector<int>::iterator last, int pivot)
{
	if (first >= last)return;

	vector<int>::iterator it;

	it = partition(first, last, [pivot](int a) {return pivot < a; });
	quick_sort(first, it - 1, *first);
	quick_sort(it + 1, last, *it);


}

int main()
{
	vector<int> vec;

	int n;//¼ÇÂ¼¸öÊý
	cout << "cin the total number:" << endl;
	cin >> n;

	int x;
	cout << "cin every index:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		vec.push_back(x);
	}

	quick_sort(vec.begin(), vec.end(), vec.at(0));

	cout << "ranked:" << endl;
	vector<int>::iterator it=vec.begin();
	for (int i = 0; i < n; i++,it++)
	{
		cout << *it << " ";
	}

}