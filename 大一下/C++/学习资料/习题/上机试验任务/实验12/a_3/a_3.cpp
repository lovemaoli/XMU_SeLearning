#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <cstdio>
using namespace std;

class name_book
{
	bool init;
	int no;
	string name;
	string unit;
	string tele;
public:
	name_book()
	{ 
		init = false;
		no = 0;
		name = "\0";
		unit = "\0";
		tele = "\0";
	}
	int get_no() { return no; }
	string get_name() { return name; }
	string get_unit() { return unit; }
	string get_tele() { return tele; }
	bool is_data_ok() { return init; }

	friend ostream& operator<<(ostream& out, name_book& x);
	friend istream& operator>>(istream& in, name_book& x);
};

ostream& operator<<(ostream& out, name_book& x) 
{
	out << x.get_no() << " ";
	out << x.get_name() << " ";
	out << x.get_unit() << " ";
	out << x.get_tele() << " \n";

	return out;
}

istream& operator>>(istream& in, name_book& x)
{
	if (&in == &cin)
		cout << "cin the number, name, unit and telephone:" << endl;
	in >> x.no;

	if (in.eof() || x.no == -1)			//规定输入序号为-1时表示输入结束
	{
		x.init = false;
		return in;
	}
	
	

	in >> x.name;
	in >> x.unit;
	in >> x.tele;

	x.init = true;

	return in;
}

int main()
{
	ofstream out_file("namebook.txt", ios::app);
	name_book n;

	cin >> n;
	while (n.is_data_ok())
	{
		out_file << n << endl;
		cin >> n;
	}

	out_file.close();
	return 0;

}