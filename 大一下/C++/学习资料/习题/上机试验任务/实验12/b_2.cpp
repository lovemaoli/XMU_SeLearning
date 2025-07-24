#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main() 
{
	map<string, int> words;
	ifstream in_file("in.txt", ios::in);
	string str;
	map<string, int>::iterator it;

	while (!in_file.eof())
	{
		in_file >> str;		//strÊäÈëÊ±Óöµ½¿Õ°×·ûºÅ¾ÍÍ£Ö¹
		it = words.find(str);

		for (int i = 0; i < str.size(); i++) 
		{
			if (ispunct(str[i]))
				str.erase(str[i]);
		}

		if (words.size() == 0)
			words.insert(pair<string, int>(str, 1));

		else
		{
			if (it == words.end())
				words.insert(pair<string, int>(str, 1));

			else
				it->second++;
		}
	}
}