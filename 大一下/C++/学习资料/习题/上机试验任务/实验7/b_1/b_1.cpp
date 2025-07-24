#include <iostream>
using namespace std;


class vector
{
	double x;
	double y;
	double z;

	vector() {
		x = 0;
		y = 0;
		z = 0;
	}

	vector(double x1,double y1,double z1) {
		x = x1;
		y = y1;
		z = z1;
	}

	~vector()
	{
		x = y = z = 0;
	}

	bool operator<(const vector& v);
	bool operator>(const vector& v);
};

bool vector::operator<(const vector& v)
{
	if ((x * x + y * y + z * z) < (v.x * v.x + v.y * v.y + v.z * v.z))
		return true;
	else return false;
}

bool vector::operator>(const vector& v)
{
	if ((x * x + y * y + z * z) > (v.x * v.x + v.y * v.y + v.z * v.z))
		return true;
	else return false;
}