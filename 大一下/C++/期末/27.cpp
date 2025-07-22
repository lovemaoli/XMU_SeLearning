#include <iostream>
#include <string>
using namespace std;
class Geometry{
	string name;
	public:
		virtual double getVolume()=0;
} ;
class Ball:public Geometry{
	double r;
	public:
		double getVolume(){
			return 4.0/3*3.14*r*r*r;
		}
		void setr(double R){
			r=R;
		}
};
class Rectangle:public Geometry{
	double a,b,h;
	public:
		double getVolume(){
			return a*b*h;
		}
		void set(double A,double B,double H){
			a=A;b=B;h=H;
		}
};
class YuanZhuZhu:public Geometry{
	double r,h;
	public:
		double getVolume(){
			return 3.14*r*r*h;
		}
		void set(double R,double H){
			r=R;h=H;
		}
} ;
int main(){
	Ball hx;
	Rectangle cyb;
	YuanZhuZhu hyx;
	Geometry* tmp[3];//基类指针数组 
	hx.setr(1.0);
	cyb.set(1,1,1);
	hyx.set(1,1);
	tmp[0]=&hx;tmp[1]=&cyb;tmp[2]=&hyx;
	for(int i=0;i<=2;i++){
		cout << tmp[i]->getVolume() << endl;
	} 
}
