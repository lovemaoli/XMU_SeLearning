#include <iostream>
#include <string>
using namespace std;
class vehicle { //汽车类
	protected:
		string* name;
		string* color;
	public:
		vehicle();
		~vehicle() {
			delete name;
			delete color;
		}
		virtual istream & operator>>(istream &in) =0;
		virtual ostream & operator<<(ostream &out) =0;
};
vehicle::vehicle() {
	name = new string;
	color = new string;
}
class car:public vehicle { //小汽车类
		int passenger;//载人数
	public:
		virtual istream & operator>>(istream &in){
			in >> *name >> *color >> passenger;
			return in;
		}
		virtual ostream & operator<<(ostream &out){
			out << "小车名：" << *name << endl << "颜色：" << *color << endl << "载人数：" << passenger <<endl;
			return out; 
		}
};

class truck:public vehicle { //卡车类
		int payload;//载重量
	public:
		virtual istream & operator>>(istream &in){
			in >> *name >> *color >> payload;
			return in;
		}
		virtual ostream & operator<<(ostream &out){
			out << "卡车名：" << *name << endl << "颜色：" << *color << endl << "载重量：" << payload <<endl;
			return out;
		}

};

int main() {
	car a;
	truck b;
	a.operator>>(cin);
	b.operator>>(cin);
	a.operator<<(cout);
	b.operator>>(cin);
	system("pause");
	return 0;
}


