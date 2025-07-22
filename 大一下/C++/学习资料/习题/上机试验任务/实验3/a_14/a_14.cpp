#include <iostream>
#include <string>
using namespace std;

int squeeze(char s1[], const char s2[])
{
	string str("\0");
	int n=0;
	for (int i = 0; i < sizeof(s1); i++)
	{
		int flag = 0;
		for (int j = 0; j < sizeof(s2); j++)
			if (s1[i] == s2[j])
			{
				flag = 1;
				break;
			}
		if (flag == 0)
		{
			str += s1[i];
			n++;
		}
	}
	memset(s1, '\0', sizeof(s1));
	for (int k = 0; k < str.size(); k++)
	{
		s1[k] = str[k];
	}
	return n;
}