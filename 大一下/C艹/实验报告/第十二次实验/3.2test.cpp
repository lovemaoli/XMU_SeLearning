#include<iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////
class A       //父类
{
private:
    int privatedateA;
protected:
    int protecteddateA;
    int testfun(int a){
    	protecteddateA = a;
	} 
public:
    int publicdateA;
    void check(){
    	cout << protecteddateA << endl;
	}
};
//////////////////////////////////////////////////////////////////////////
class B :public A      //基类A的派生类B（共有继承）
{
public:
    void funct()
    {
        int b;
        b=protecteddateA; //ok：基类的保护成员在派生类中为保护成员
        b=publicdateA;    //ok：基类的公共成员在派生类中为公共成员
    }
	using A::testfun;
};
//////////////////////////////////////////////////////////////////////////
int main()
{
    int a; 
 	A objA;
 
    B objB;
    objB.testfun(3);
    objB.check();
    return 0;
}
