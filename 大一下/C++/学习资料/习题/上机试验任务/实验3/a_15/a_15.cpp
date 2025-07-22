#include <iostream>
#include <cstring>
#define _crt_secure_no_warnings
using namespace std;

int find_replace_str(char str[],
					const char find_str[],
					const char replace_str[])
{
	int count=0;
	string str0, find_str0, replace_str0;
	for (int i = 0; i < strlen(str); i++)
		str0 += str[i];
	for (int i = 0; i < strlen(find_str) ; i++)
		find_str0 += find_str[i];
	for (int i = 0; i <strlen(replace_str) ; i++)
		replace_str0 += replace_str[i];

	int index;
	while ((index=str0.find(find_str0, 0)) != -1)
	{
		str0.replace(index, find_str0.size(), replace_str0);
		count++;
	}
	
	for (int i = 0; i < strlen(str); i++)
		str[i] = '\0';
	for (int i = 0; i < str0.size(); i++)
		str[i] = str0[i];
		
	return count;
}
