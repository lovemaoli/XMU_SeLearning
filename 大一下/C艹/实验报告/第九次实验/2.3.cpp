#include <bits/stdc++.h>
using namespace std;
class Person {
	private:
		char* pName;
	public:
		Person(char *pN="noName") {
			cout<<"构造中  "<<pN<<"\n";
			pName=new char[strlen(pN)+1];
			if (pName) strcpy(pName,pN);
		}
		Person(Person &a) {
			cout<<"拷贝构造中  "<<a.pName<<"\n";
			pName=new char[strlen(a.pName)+1];
			if (pName) strcpy(pName,a.pName);
		}
		~Person(){
			cout<<"析构函数运行  "<<pName<<"\n";
			delete pName;
		}
};

int main() {
	Person * hx, *cyb;
	hx = new Person("帅哥");
	cyb = new Person(*hx);
	delete cyb;
	return 0;
}
