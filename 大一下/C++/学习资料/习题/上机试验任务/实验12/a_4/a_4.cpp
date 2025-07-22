#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

struct Date 
{
	int year;
	int month;
	int day;
};
class Student
{
private:
	string id;
	string name;
	string sex;
	Date birth_date;
	string birth_place;
	string major;
	bool init;
public:
	Student()
	{
		id = "\0";
		name = "\0";
		sex = "\0";
		birth_date.year = birth_date.month = birth_date.day = 0;
		birth_place = "\0";
		major = "\0";
		init = true;
	}
	bool is_data_ok() { return init; }
	friend ofstream& operator<<(ofstream& out, Student& s);
	friend istream& operator>>(istream& in, Student& s);

};

ofstream& operator<<(ofstream& out, Student& s)
{
	out <<  s.id << " ";
	out <<  s.name << " ";
	out <<  s.sex << " ";
	out << s.birth_date.year << ".";
	out << s.birth_date.month << ".";
	out << s.birth_date.day << " ";
	out << s.birth_place << " ";
	out << s.major << " ";

	return out;
}

istream& operator>>(istream& in, Student& s)
{
	if (&in == &cin)
		cout << "请输入数据:" << endl;

	in >> s.id;

	if (in.eof() || s.id[0] == 'e')
	{
		s.init = false;
		return in;
	}

	in >> s.name;
	in >> s.sex;
	in >> s.birth_date.year;
	in >> s.birth_date.month;
	in >> s.birth_date.day;
	in >> s.birth_place;
	in >> s.major;

	return in;
}

int main()
{
	ofstream out_file("namebook.txt", ios::out | ios::binary);
	Student s;

	if (!out_file)
	{
		cerr << "无法打开文件";
		return -1;
	}

	cin >> s;
	while (s.is_data_ok())
	{
		out_file << s;
		cin >> s;
	}

	out_file.close();
	return 0;
}