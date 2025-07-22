#include <iostream>
#include <string>
#define _crt_secure_no_warnings

using namespace std;

int main()
{
	string str1;
	string str2("\0");
	getline(cin, str1);
	for (int i = 0; i < str1.size(); i++)
	{
		str2 += str1[i];
		str2[i] += 8;
	}
	string str0;
	getline(cin, str0);
	if (str1 == str0)
		cout << str0;
	else cout << "½âÃÜÊ§°Ü";
	return 0;
}