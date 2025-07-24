#include <iostream>
using namespace std;

class Date
{
	void increment();
	int year;
	int month;
	int day;
};

void Date::increment()
{
	int days_of_month1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//·ÇÈòÄê
	int days_of_month2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };//ÈòÄê

	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
	{
		if (day + 1 > days_of_month2[day]) 
		{
			day = 1;
			month++;
			if (month > 12)
			{
				year++;
				month = 1;
			}
		}
	}
	else
	{
		if (day + 1 > days_of_month1[day])
		{
			day = 1;
			month++;
			if (month > 12)
			{
				year++;
				month = 1;
			}
		}
	}
}