#include <iostream>
#include "date.h"
using namespace std;
void Date:: display1 () {
	cout << month << "-" << day << "-" << year%100 << endl;
}
void Date:: display2 () {
	string monthchar[12]= {"January","February","March","April","May","June",
	                       "July","August","September","October","November","December"
	                      };
	cout << monthchar[month-1] << " " << day << "," << year << endl;
}
void Date:: display3 () {
	string monthchar[12]= {"January","February","March","April","May","June",
	                       "July","August","September","October","November","December"
	                      };
	cout <<  day << " " << monthchar[month-1] << " " << year << endl;
}
int Date:: setdate (int y,int m,int d) {
	if(d < 1 || d > 31) {
		cout << "day num error" << endl;
		return -1;
	}
	if(m < 1 || m > 12) {
		cout << "month num error" << endl;
	}
	year = y;
	month = m;
	day = d;
}


