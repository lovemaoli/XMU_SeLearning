#include<iostream>
#include<cstring>
using namespace std;
class MyString {
		friend ostream& operator<<(ostream&out,MyString &ob);//友元函数重载<<的友元声明
		friend istream& operator>>(istream&in,MyString &ob);//友元函数重载>>的友元声明
	private:
		char *str;
		int size;//字符串长度
	public:
		MyString();//无参构造
		MyString(const char *str);//有参构造函数
		MyString(const MyString &ob);//拷贝构造
		~MyString();//析构函数
		int Size(void);//返回字符串长度
		char& operator[](int i);//成员函数重载[]
		MyString& operator =(const MyString &ob);//成员函数重载= 实现深赋值 ob1=ob2;
		MyString& operator+(const MyString &ob);//成员函数重载+ 实现ob1+ob2
		MyString& operator+(const char *str);//成员函数重载+ 实现ob1+"abc"
		MyString& operator+=(const MyString &ob);//成员函数重载+= 实现ob1+=ob2
		bool operator==(const MyString&ob);//成员函数重载== 判断ob1==ob2
		bool operator==(const char *str);//成员函数重载== 判断ob1=="abc"
};
MyString::MyString() {
	this->str=NULL;
	this->size=0;
	cout<<"无参构造"<<endl;
}

MyString::MyString(const char *str) {
	cout<<"char * 构造函数"<<endl;
	this->str=new char [strlen(str)+1];
	strcpy(this->str,str);
	this->size=strlen(str);
}
MyString::MyString(const MyString &ob) {
	cout<<"拷贝构造函数"<<endl;
	this->str=new char[strlen(ob.str)+1];
	strcpy(this->str,ob.str);
	this->size=ob.size;
}

MyString::~MyString() {

	if(this->str!=NULL) {
		delete str;
		this->str=NULL;
	}
	cout<<"析构函数"<<endl;
}

int MyString::Size() {
	return this->size;
}

char& MyString::operator[](int i) {
	if(i>=0&&i<this->size)
		return (this->str)[i];
	else
		cout<<"下标无效"<<endl;
}

MyString &MyString::operator =(const MyString &ob) {
	//先将this->str的旧空间释放掉
	if(this->str!=NULL) {
		delete str;
		this->str=NULL;
	}
	this->str=new char[strlen(ob.str)+1];
	strcpy(this->str,ob.str);
	this->size=strlen(ob.str);
	cout<<"=号赋值"<<endl;
	return *this;
}

MyString& MyString::operator+(const MyString &ob) {
	/*
	int tmp_size=strlen(this->str)+strlen(ob.str)+1;
	char *tmp=new char[tmp_size];
	strcpy(tmp,this->str);
	strcat(tmp,ob.str);

	MyString s (tmp);
	if(tmp!=NULL)
	{
	    delete tmp;
	    tmp=NULL;
	}
	return s; //这种写法不能实现cout<<str1+str2<<endl;
			 //只能实现MyString s1=str1+str2;
			 //        cout<<s1<<endl;是因为c++编译器规定临时变量不能作为非const引用
	*/
	int tmp_size=strlen(this->str)+strlen(ob.str)+1;
	char *tmp=new char[tmp_size];
	strcpy(tmp,this->str);
	strcat(tmp,ob.str);
	static MyString s(tmp);//static变量s只会实例化一个对象并且不会因为这句话的tmp改变值
	if(strcmp(s.str,tmp)!=0)//更新s变量中的值
		strcpy(s.str,tmp);
	if(tmp!=NULL) { //及时释放堆区申请的空间
		delete tmp;
		tmp=NULL;
	}
	return s;
}

MyString& MyString::operator+=(const MyString &ob) {
	int tmp_size=strlen(this->str)+strlen(ob.str)+1;
	char *tmp=new char[tmp_size];
	strcpy(tmp,this->str);
	strcat(tmp,ob.str);
	this->str=tmp;
	return *this;
}

MyString& MyString::operator+(const char *str) {
	int tmp_size=strlen(this->str)+strlen(str)+1;
	char *tmp=new char[tmp_size];
	strcpy(tmp,this->str);
	strcat(tmp,str);
	static MyString s (tmp);
	if(strcmp(s.str,tmp)!=0)
		strcpy(s.str,tmp);
	if(tmp!=NULL) {
		delete tmp;
		tmp=NULL;
	}
	return s;
}
bool MyString::operator==(const MyString &ob) {
	if((strcmp(this->str,ob.str)==0)&&(this->size==ob.size))
		return true;
	else
		return false;
}

bool MyString::operator==(const char *str) {
	if((strcmp(this->str,str) == 0)&&(this->size==strlen(str)))
		return true;
	else
		return false;
}

ostream& operator<<(ostream&out,MyString &ob) {
	out<<ob.str;
	return out;
}

istream &operator>>(istream &in, MyString &ob) {
	//记得将原有数据擦除
	if(ob.str!=NULL) {
		delete ob.str;
		ob.str=NULL;
	}
	char buf[1024]="";//临时buf
	in.getline(buf,1024);//先得到键盘输入的数据 然后根据buf的实际大小开辟空间，最多读1023最后一位补\0
	ob.str=new char [strlen(buf)+1];
	strcpy(ob.str,buf);
	ob.size=strlen(buf);
	return in;
}
int main(){
	MyString a("hx is handsone,"),b("while cyb is stupid.");
	a+=b;
	cout << a;
	return 0;
} 
