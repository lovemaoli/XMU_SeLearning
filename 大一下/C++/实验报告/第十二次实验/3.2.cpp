
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
};
//////////////////////////////////////////////////////////////////////////
class B :public A      //基类A的派生类B（共有继承）
{
public:
    void funct()
    {
        int b;
        b=privatedateA;   //error：基类中私有成员在派生类中是不可见的
        b=protecteddateA; //ok：基类的保护成员在派生类中为保护成员
        b=publicdateA;    //ok：基类的公共成员在派生类中为公共成员
    }
//    int testfun(int a){ //方法一 
//    	protecteddateA = a;
//	}
	using A::testfun;     //方法二 
};
//////////////////////////////////////////////////////////////////////////
class C :private A  //基类A的派生类C（私有继承）
{
public:
    void funct()
    {
        int c;
        c=privatedateA;    //error：基类中私有成员在派生类中是不可见的
        c=protecteddateA;  //ok：基类的保护成员在派生类中为私有成员
        c=publicdateA;     //ok：基类的公共成员在派生类中为私有成员
    }
};
//////////////////////////////////////////////////////////////////////////
class D :protected A   //基类A的派生类D（保护继承）
{
public:
    void funct()
    {
        int d;
        d=privatedateA;   //error：基类中私有成员在派生类中是不可见的
        d=protecteddateA; //ok：基类的保护成员在派生类中为保护成员
        d=publicdateA;    //ok：基类的公共成员在派生类中为保护成员
    }
};
//////////////////////////////////////////////////////////////////////////
int main()
{
    int a; 
 	A objA;
	a=objA.protecteddateA; //error：基类对象的保护成员对对象不可见
 
    B objB;
    a=objB.privatedateA;   //error：基类中私有成员在派生类中是不可见的,对对象不可见
    a=objB.protecteddateA; //error：基类的保护成员在派生类中为保护成员，对对象不可见
    a=objB.publicdateA;    //ok：基类的公共成员在派生类中为公共成员，对对象可见
 
    C objC;
    a=objC.privatedateA;   //error：基类中私有成员在派生类中是不可见的,对对象不可见
    a=objC.protecteddateA; //error：基类的保护成员在派生类中为私有成员，对对象不可见
    a=objC.publicdateA;    //error：基类的公共成员在派生类中为私有成员，对对象不可见
 
    D objD;
    a=objD.privatedateA;   //error：基类中私有成员在派生类中是不可见的,对对象不可见
    a=objD.protecteddateA; //error：基类的保护成员在派生类中为保护成员，对对象不可见
    a=objD.publicdateA;    //error：基类的公共成员在派生类中为保护成员，对对象不可见
 
    return 0;
}
