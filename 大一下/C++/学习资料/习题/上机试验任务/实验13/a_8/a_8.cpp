#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct Student
{
	string number;
	string name;
	int score[8];
	int average;
};

istringstream& operator>>(istringstream& in, Student& s)
{
	in >> s.number;
	in >> s.name;
	for (int i = 0; i < 8; i++)
		in >> s.score[i];
	int sum = 0;
	for (int i = 0; i < 8; i++)
		sum += s.score[i];
	s.average = sum / 8;

	return in;
}

ofstream& operator<<(ofstream& out, Student& s)
{
	out << s.number<<" ";
	out << s.name << " ";
	out << s.average << endl;

	return out;
}

bool aver_rank(Student&s1, Student &s2)
{
	return s1.average >= s2.average;
}

int main()
{
	ifstream in_file("in.txt", ios::in);
	ofstream out_file("out.txt", ios::out|ios::app);
	vector<Student> v_stu;
	Student stu;
	string line;
	int i = 0;

	while (!in_file.eof())
	{
		getline(in_file, line);
		istringstream iss(line);
		iss >> stu;
		
		v_stu.push_back(stu);
	}

	sort(v_stu.begin(), v_stu.end(), aver_rank);

	for (i=0;i<(int)v_stu.size();i++)
		out_file << v_stu[i];

	in_file.close();
	out_file.close();
	return 0;
}