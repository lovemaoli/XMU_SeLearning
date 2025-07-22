#include<iostream>
using namespace std;
class X{	
	int x1,x2 ;
public:
	X (int i,int j) {x1 = i ; x2 = j ;}
	void print ( ) { cout<<x1<<","<<x2<<endl ; }
	~X( ) {cout<<"X's destructor called."<<endl; }
};
class Y:public X{
	int y ;		// 派生类Y新增数据成员
public:
	Y( int i , int j , int k) : X(i , j)	{ y = k ;}		//派生类构造函数
	void print( ) {X::print ( ) ;cout<<y<<endl ;}
	~Y( ) { cout<<"Y's destructor called."<<endl ; }
};
int main( )
{
     Y y1(5,6,7) ,
     y2(2,3,4) ; 
     y1.print( ) ;
     y2.print ( ) ;
}

