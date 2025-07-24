#include <iostream>
#include <cmath>
using namespace std;

class Point
{
	double r();
	double theta();
	double distance(const Point& p);
	Point relative(const Point& p);
	bool is_above_left(const Point& p);
	double x;
	double y;
	double xp;
	double yp;
};

double Point::r()
{
	double r;
	r = sqrt(x * x + y * y);
	return r;
}

double Point::theta()
{
	double theta1;
	theta1 = acos(x / r());
	return theta1;
}

double Point::distance(const Point& p)
{
	double d;
	d = sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	return d;
}
Point Point::relative(const Point& p)
{
	xp = x - p.x;
	yp = y - p.y;
}
bool Point::is_above_left(const Point& p)
{
	if (x<p.x && y>p.y)return true;
	else return false;
}