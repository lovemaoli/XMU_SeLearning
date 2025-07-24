#ifndef WORKER_CPP
#define WORKER_CPP
#include <iostream>
#include <string>
#include "worker.h"
using namespace std;
Teacher::Teacher(string n, int a, char s, string ad, int t, string ti) {
	name=n;
	age=a;
	sex=s;
	addr=ad;
	tel=t;
	title=ti;
}
void Teacher::display() {
	cout<<"name: "<<Teacher::name<<endl;
	cout<<"age: "<<Teacher::age<<endl;
	cout<<"sex: "<<Teacher::sex<<endl;
	cout<<"title: "<<Teacher::title<<endl;
	cout<<"address: "<<Teacher::addr<<endl;
	cout<<"tel: "<<Teacher::tel<<endl;
}
Cadre::Cadre(string nam, int a, char s, string ad, int te, string po) {
	name=nam;
	age=a;
	sex=s;
	addr=ad;
	tel=te;
	post=po;
}
void Cadre::display1() {
	cout<<"name: "<<name<<endl;
	cout<<"age: "<<age<<endl;
	cout<<"sex: "<<sex<<endl;
	cout<<"address: "<<addr<<endl;
	cout<<"tel: "<<tel<<endl;
	cout<<"post: "<<post<<endl;
}
void Teacher_Cadre::show() {
	Teacher::display();
	cout<<"post: "<<Cadre::post<<endl;
	cout<<"wage: "<<wage<<endl;
}
#endif
