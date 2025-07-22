#include <iostream>
#include <string>
#define _crt_secure_no_warnings
#define trans 1
using namespace std;

int main()
{
	char c='\0';
	string str;
	getline(cin, str);
	for (int i = 0; i < str.size(); i++)
	{
		c = str[i];
#ifdef trans
		if (c >= 'a' && c <= 'z') c -= 32;
#endif
		cout << c;
	}
	return 0;
}