#include <iostream>
using namespace std;
class Student
{
	public:
		Student(int g=3):gpa(g)
		{
			cout<<"construct student.\n";
			semeshours=100;
		}
	protected:
		int semeshours;
		float gpa;
};
class Teacher
{
	public:
		Teacher()
		{
			cout<<"construct Teacher.\n";
		}

};
class Tourpair
{
	public:
		Tourpair():student(4)
		{
			cout<<"construct tourpair.\n";
			nomeeting=0;
		}
	protected:
		Student student;
		Teacher teacher;
		int nomeeting;
};

int main()
{
	Tourpair tp;
	cout<<"back in main.\n";
}
