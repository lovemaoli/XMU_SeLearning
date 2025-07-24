#include <iostream>
#include <string>
#define _crt_secure_no_warnings

using namespace std;

int main()
{
	string str1,str2("\0");
	cin >> str1;
	for (int i =0;i<str1.size(); i++)
	{
		str2 += str1[str1.size() - i - 1];
	}
	cout << str2 << endl;
	return 0;
}