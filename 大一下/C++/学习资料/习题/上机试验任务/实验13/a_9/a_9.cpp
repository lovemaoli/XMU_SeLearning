#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool b_rank(string& str1, string& str2)
{
	return str1.compare(str2)<0;
}


int main()
{
	fstream in_file;
	in_file.open("words.txt", ios::in);
	vector<string> vec;
	string str;

	while (!in_file.eof())
	{
		in_file >> str;
		vec.push_back(str);
	}
	in_file.close();

	sort(vec.begin(), vec.end(), b_rank);

	ofstream out_file;
	out_file.open("words.txt", ios::out);
	
	for (size_t i = 0; i < vec.size(); i++)
		out_file << vec[i]<<endl;

	out_file.close();
	return 0;
}