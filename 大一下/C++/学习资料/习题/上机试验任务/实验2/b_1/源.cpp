#include <iostream>
#include <string>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int main()
{
	string str1, str2("\0");
	cin >> str1;
	int i;
	for (i = 0; i < str1.size();i++)
	{
		if (!ispunct(str1[i]))
			str2 += str1[i];
	}
	cout << str2 << endl;
	return 0;
}