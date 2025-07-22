#include <fstream>
#include <iostream>
#include <string>
#include <strstream>
#include <cstdio>
using namespace std;

int main()
{
	string str;
	ifstream in_file("in.txt", ios::in);
	int line=0;

	while (!in_file)
	{
		cerr << "can not open the file!" << endl;
		return -1;
	}

	while (!in_file.eof()) 
	{
		getline(in_file, str);
		line++;
	}

	cout << line << endl;

	in_file.close();
	return 0;

}
