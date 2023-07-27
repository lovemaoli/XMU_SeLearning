#include <iostream>
using namespace std;
class Time {
	public:
		Time(int,int,int);
		friend void display(Time &t);
		void prin();
	private:
		int hour;
		int minute;
		int sec;
};

Time::Time(int h,int m,int s) {
	hour=h;
	minute=m;
	sec=s;
}

void Time:: prin(){
	cout<<hour<<minute<<sec;
}

void display(Time &t) {
	cout<<t.hour<<":"<<t.minute<<":"<<t.sec<<endl;   //直接输出对象的hour、minute和sec
}

int main() {
	Time t1(10,13,56);
	display(t1);
	t1.prin(); //成员函数的调用
	return 0;
}

