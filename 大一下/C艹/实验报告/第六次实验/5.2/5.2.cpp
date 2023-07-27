#include <bits/stdc++.h>
#include "date.h"
//#include "date.cpp" 
using namespace std;
int main() {
	Date d;
	d.setdate(); 
	while(1) {
		cout<<"-----------------------\n";
		cout<<"-----日期设定系统------\n";
		cout<<"-----------------------\n";
		cout<<"--------[1]设定--------\n";
		cout<<"--------[2]输出--------\n";
		cout<<"------[Ctrl+C]退出-----\n";
		cout<<"-----------------------\n";
		int a;
		cin >> a;
		if(a==1) {
			cout<<"请输入：(默认为2010 12 25) 空格分隔"<<endl;
			int y,m,da;
			cin >> y >> m >> da;
			d.setdate(y,m,da);
		}
		if(a==2) {
			cout<<"请输入输出模式：（1-3）"<<endl;
			int mod;
			cin >> mod;
			if(mod == 1){
				d.display1();
			}
			if(mod == 2){
				d.display2();
			}
			if(mod == 3){
				d.display3();
			}
		}
	}
	return 0;
}
