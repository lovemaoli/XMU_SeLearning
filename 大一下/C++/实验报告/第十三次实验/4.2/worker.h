#ifndef WORKER_H
#define WORKER_H
#include <string>
using namespace std;
class Teacher {
	public:
		Teacher(string n, int a, char s, string ad, int t, string ti);
		void display();
	protected:
		string name;
		int age;
		char sex;
		string addr;
		int tel;
		string title;
};
class Cadre {
	public:
		Cadre(string, int, char, string, int, string);
		void display1();
	protected:
		string name;
		int age;
		char sex;
		string addr;
		int tel;
		string post;
};
class Teacher_Cadre: public Teacher, public Cadre {
	public:
		Teacher_Cadre(string nam, int a, char s, string ad, int te, string tit, string po, double w):
			Teacher(nam, a, s, ad, te, tit), Cadre(nam, a, s, ad, te, po), wage(w) {}
		void show();
	private:
		double wage;
};
#endif
