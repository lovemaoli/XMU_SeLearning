#include <cstdio>
#include <iostream>
#include <string>
#include <strstream>
#include <fstream>
using namespace std;

int main()
{
	ifstream in_file("file1.txt", ios::in);
	ofstream out_file("file2.txt", ios::out);
	string str;

	if (!in_file)
	{
		cerr << "打开文件失败" << endl;
		return -1;
	}


	cout << "read from file:";

	while (!in_file.eof())
	{
		getline(in_file,str);
		cout << str;
	}
	
	out_file << str;

	

	out_file.close();
	in_file.close();

	return 0;
}