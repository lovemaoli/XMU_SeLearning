#include<iostream>
using namespace std;
class Time
{
public:
	Time(int h, int m, int s);
	void set(int h, int m, int s);
	void increment();
	void display();
	bool equal(Time& other_time);
	bool less_than(Time& other_time);

private:
	int hour, mintue, second;
};

class ExtTime :public Time
{
	int area,hour,minute,second;
public:
	ExtTime(int a, int h, int m, int s)	:Time(h,m,s)
	{
		area = a;
		hour = h;
		minute = m;
		second = s;
	}
	void set(int area, int h, int m, int s);
};


void ExtTime::set(int a, int h, int m, int s)
{
	area = a;
	hour = h;
	minute = m;
	second = s;
}

Time::Time(int h, int m, int s)
{
	hour = h;
	mintue = m;
	second = s;
}

void Time::set(int h, int m, int s)
{
	hour = h;
	mintue = m;
	second = s;
}
void Time::increment()
{
	if (second < 60)
		second += 1;
	else
	{
		second = 0;
		mintue += 1;
	}

	if (mintue < 60)
		mintue += 1;
	else
	{
		mintue = 0;
		hour += 1;
	}

}

void Time::display()
{
	cout << "hours:" << hour << endl;
	cout << "mintues:" << mintue << endl;
	cout << "seconds:" << second << endl;
}

bool Time::equal(Time& other_time)
{
	if (other_time.hour == hour && other_time.mintue == mintue && other_time.second == second)
		return true;
	else return false;
}

bool Time::less_than(Time& other_time)
{
	if (hour < other_time.hour)
		return true;
	else if (hour > other_time.hour)
		return false;
	else
	{
		if (mintue < other_time.mintue)
			return true;
		else if (mintue > other_time.mintue)
			return false;
		else
		{
			if (second < other_time.second)
				return true;
			if (second >= other_time.second)
				return false;
		}

	}
}