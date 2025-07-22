#include <iostream>
#include <cstring>
using namespace std;

const int N = 8;
int solution;
int *arr;//用于储存各列的皇后的行位置
//规定左下角为坐标原点

bool IsPlaceOk(int t)
{
	for (int i = 1; i < t; i++)
		if (abs(arr[i] - arr[t]) == abs(i - t) ||  arr[i] == arr[t])
			return false;
	return true;
}//检验下一列的位置t是否可以

void backtrack(int t)
{
	if (t <= N)
	{
		for (int i = 1; i <= N; i++)
		{
			arr[t] = i;//让第t列的皇后取到所有位置
			if (IsPlaceOk(t))
				backtrack(t + 1);//如果某一个位置目前可以，进入下一行的判定
		}
	}//取尽所有列位置，如果所有位置判定合理，solution+1

	else solution++;
}

void main()
{
	solution = 0;
	arr = new int[N + 1];
	for (int n = 1; n <= N; n++)
		arr[n] = 0;
	backtrack(1);
	cout << solution;
	delete []arr;
}