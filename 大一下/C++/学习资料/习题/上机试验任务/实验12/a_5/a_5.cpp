#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <strstream>
using namespace std;

class circle
{
private:
	bool init;
	double r;
public:
	circle(){ r = 0; init = true; }
	bool is_data_ok() { return init; }
	friend ofstream& operator<<(ofstream& out, circle& x);
	friend istream& operator>>(istream& in, circle& x);
};

class rectangle
{
private:
	bool init;
	double length;
	double width;
public:
	rectangle() { length = width = 0; init = true; }
	bool is_data_ok() { return init; }
	friend ofstream& operator<<(ofstream& out, rectangle& x);
	friend istream& operator>>(istream& in, rectangle& x);
};

ofstream& operator<<(ofstream& out, circle& x)
{
	out << "circle:r=";
	out << x.r << endl;
	return out;
}

istream& operator>>(istream& in, circle& x)
{
	if (&cin == &in)
		cout << "ÇëÊäÈë°ë¾¶;";
	in >> x.r;

	if (in.eof() || x.r == 0)
	{
		x.init = false;
		return in;
	}

	return in;
}

ofstream& operator<<(ofstream& out, rectangle& x)
{
	out << "rectangle:length=";
	out << x.length << " ";
	out << "width=";
	out << x.width << " "<<endl;

	return out;
}

istream& operator>>(istream& in, rectangle& x)
{
	if (&cin == &in)
		cout << "ÇëÊäÈë³¤:" << endl;
	in >> x.length;

	if (in.eof() || x.length == 0)
	{
		x.init = false;
		return in;
	}

	cout << "ÇëÊäÈë¿í:" << endl;
	in >> x.width;

	return in;
}

int main()
{
	ofstream out_file("figure.txt", ios::out|ios::app);
	circle cir;
	rectangle rec;
	int figure=1;

	cout << "Ñ¡ÔñÍ¼ÐÎ: 1(circle); 2(rectangle); 3(end)" << endl;
	cin >> figure;

	while (figure!=3)
	{
		if (figure == 1)
		{
			cin >> cir;
			out_file << cir << endl;
		}
		
		else
		{
			cin >> rec;
			out_file << rec << endl;
		}

		cin >> figure;
	}

	out_file.close();
	return 0;
}