#include <iostream>
using namespace std;
class Date {
	public:
		Date(int y,int m,int d);
		void showDate( );
	private:
		const int year;
		const int month;
		const int day;
};
Date::Date(int y,int m,int d):year(y),month(m),day(d){    } //函数体中为空
void Date::showDate( )  {
	cout<<year<<"."<<month<<"."<<day<<endl;
}
int main() {
	Date date1(2009,10,15);
	date1.showDate(); //非contst成员函数可以访问const的数据成员
	return 0;
}

