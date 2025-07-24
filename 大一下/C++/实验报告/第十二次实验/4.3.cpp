#include<iostream>
using namespace std; 
class A{	//定义基类
private:
	int a ;
public:
    A(int x) { a = x ;cout<<"A's constructor called."<<endl ; }
    void show( ) { cout<<a<<endl;}
};
class B{	//定义另一个类，将作为类成员
private:
	int b ;
public:
    B(int x) { b = x ;cout<<"B's constructor called."<<endl ; }
    int get( ) { return b;}
};
class C : public A{		//定义派生类
private:
	int c;
	B obj_b ;
public:
	C( int x ,int y , int z):A(x),obj_b(y)// 派生类构造函数
	{
		c = z ;
		cout<<"C's constructor called."<<endl ;
	}
   	 void show( ) { 
    		A::show( );
		cout<<obj_b.get()<<","<<c<<endl ;
	}
};
int main(){
	C  c1(1,2,5),  c2(3,4,7);
	c1.show( ) ;	
	c2.show( ) ;
}

