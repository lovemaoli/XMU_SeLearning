#ifndef DATE_H 
#define DATE_H
class Date {
	private:
		int year,month,day;
	public:
		void display1();
		void display2();
		void display3();
		int setdate(int y=2010,int m=12,int d=25);
};
#endif
