#include <iostream>
#include <string>
using namespace std;

int main()
{
	string* p;
	
	try
	{
		if ((p = new string) == NULL)throw 'e';
	}
	catch (char)
	{
		cout << "无法分配内存！" << endl;
	}

	return 0;
}