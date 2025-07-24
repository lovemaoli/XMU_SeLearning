#include <iostream>
using namespace std;
class Time
{
	public:
		Time(int y,int m,int d):year(y),month(m),day(d){
			cout << "Time created.\n";
		}
	private:
		int year;
		int month;
		int day;
};
class Student
{
	public:
		Student(int n,int y,int m,int d):time(y,m,d){
			num = n;
			cout << "Student created.\n";
		}
	private:
		Time time;
		int num;
} ;
int main()
{
	while(1){
		int n1,y1,m1,d1;
		cin >> n1 >> y1 >> m1 >> d1;
		new Student(n1,y1,m1,d1);
	}
}
