#include <iostream>
#include <cstdlib>
using namespace std;

class Vec
{
private:
	char* p;
public:
	Vec() { p = NULL; }
	Vec(char* str)
	{ 
		for (int i = 0; i < strlen(str); i++)
			p[i] = str[i];
	}
	void set(char* str) { p = str; }
	char& operator[](int i);
};

char& Vec::operator[](int i)
{
	try
	{
		if (i > strlen(p) || i < 0)
		{
			throw i;
		}
	}

	catch (int)
	{
		cout << "数组越界!" << endl;
		exit(-1);
	}

	return p[i];
}

int main()
{
	Vec vec;
	char str[10] = "asdfg";
	vec.set(str);
	vec[8];
	return 0;
}