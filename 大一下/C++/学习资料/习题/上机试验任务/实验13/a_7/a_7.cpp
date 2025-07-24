#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream in_file;
	in_file.open("strings.txt", ios::in);
	
	if (!in_file.is_open())
	{
		cerr << "can't open the file";
		exit(-1);
	}

	string str;			//用于储存想要查找的字符串

	cout << "please input the string to find:" << endl;
	cin >> str;

	string file_line;	//从文件中读取行之后读取到的字符串
	int pos=0;
	int i = 0;

	getline(in_file, file_line);

	cout << "the position is: ";
	while ((pos=file_line.find(str,pos))!=string::npos)
	{
		cout << pos << " ";
		pos++;		//如果查找到了，pos会被赋值为第一个出现的位置，自增之后再次查找，直到无法找到
		i++;
	}

	cout << endl << "总的出现次数:" << i << endl;

	in_file.close();
	return 0;
}