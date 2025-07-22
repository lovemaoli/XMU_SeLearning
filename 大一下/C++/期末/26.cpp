#include <iostream>
#include <string.h>
using namespace std;
class String {
	public:
		String(const char *str=NULL); // 普通构造函数
		String(const String &other); // 拷贝构造函数
		~String(); // 析构函数
		String& operator=(const String &other); // 赋值函数
		void show() {
			cout<<m_data<<endl;
		}
		friend ostream& operator<<(ostream&out,String &ob);//本题不要求 仅作测试！友元函数重载<<的友元声明
		friend istream& operator>>(istream&in,String &ob);//本题不要求 仅作测试！友元函数重载>>的友元声明
	private:
		char *m_data; // 用于保存字符串
};
//under this is my answer
#define SIZE 50
String::String(const char *str){
	m_data = new char [SIZE];
} 
String::String(const String &other){
	m_data = new char [strlen(other.m_data)+1];
	for(int i=0;i<=strlen(other.m_data);i++){
		m_data[i] = other.m_data[i];
	}
}
String::~String(){
	delete [] m_data; 
}
String& String::operator=(const String &other){ //利用this指针 
	if(strlen(other.m_data)>=50){
		delete []m_data;
		m_data = new char [strlen(other.m_data)+1];
	}
	for(int i=0;i<=strlen(other.m_data);i++){
		m_data[i] = other.m_data[i];
	}
}
ostream& operator<<(ostream&out,String &ob) {//本题不要求 仅作测试！
	out<<ob.m_data;
	return out;
}

istream &operator>>(istream &in, String &ob) {//本题不要求 仅作测试！
	//记得将原有数据擦除
	if(ob.m_data!=NULL) {
		delete ob.m_data;
		ob.m_data=NULL;
	}
	char buf[SIZE]="";//临时buf
	in.getline(buf,SIZE);//先得到键盘输入的数据 然后根据buf的实际大小开辟空间，最多读1023最后一位补\0
	ob.m_data=new char [strlen(buf)+1];
	strcpy(ob.m_data,buf);
	return in;
}
int main(){
	String a;
	cin >> a;
	String b=a;
	String* d = new String;
	cout << a << endl;//本题不要求 仅作测试！
	cout << b << endl;//本题不要求 仅作测试！
	delete d;
}
// 也调试了好几个bug才改对...考试的时候写出大概框架即可 老师看不出来 （逃 
