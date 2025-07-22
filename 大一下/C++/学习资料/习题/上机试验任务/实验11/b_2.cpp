#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	string str("abcdeeeff");
	map<char, int> m;
	map<char, int>::iterator it;

	for (int i = 0; i < str.length(); i++)
	{
		if (m.find(str[i]) == m.end())
			m[str[i]] = 1;

		else
			m[str[i]] += 1;
	}

	for (it = m.begin(); it != m.end(); it++)
		cout << it->first << ":" << it->second << endl;
}