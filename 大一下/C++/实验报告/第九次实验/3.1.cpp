#include <bits/stdc++.h> 
using namespace std;

class MyString {
	private:
		char* text;
	public:
		MyString(const char* str = NULL);//普通建构函式
		~MyString();//解构函式
		MyString(const MyString& other);//拷贝建构函式
		MyString& operator=(const MyString& other); //赋值函式

	public:
		void print(); //打印出私有变数text;

};

MyString::MyString(const char* str) {
	cout<< "MyString(const char* str)" <<endl;
	if (str == NULL) {
		text = new char[1];
		*text = '\0';
	} else {
		int len = strlen(str);
		text = new char[len+1];
		strcpy(text, str);
	}
}

MyString::~MyString() {
	cout << "~MyString()"<< endl;
	delete []text;
	text = NULL;
}

MyString::MyString(const MyString& other) {
	cout<< "MyString(const MyString& other)"<<endl;
	int len = strlen(other.text);
	text = new char[len + 1];
	strcpy(text, other.text);

}

MyString& MyString::operator=(const MyString& other) {
	cout << "MyString& operator=(continue MyString& other)" << endl;
	if (&other == this) {
		return *this;
	}

	else {
		delete []text;
		text = NULL;
		int len = strlen(other.text);
		text = new char[len + 1];
		strcpy(text, other.text);
		return *this;
	}
}

void MyString::print() {
	cout << "text="<< text << "  "<< strlen(text) << endl;
}

int main() {

	MyString mystr("this is mystring"); //普通构造函数 

	MyString str1(mystr); //赋值构造函数 
	MyString str2 = mystr; //赋值构造函数 

	MyString str3;
	str3 = str2;

	str3.print();

	return 0;



}
