#include <iostream>
using namespace std;

	int add(int x,int y,int z)
	{
		int sum;
		sum=x+y+z;
		return sum;
	}
	double add(int x,int y)
	{
       double sum;
	   sum=x+y;
	   return sum;
	}
	int main(){
		int add(int x=1,int y=2,int z=3);
		double add(int x,int y);
		int sum;double sum2;
		sum=add(10,20); // add函数均被定义为int参数，二者会冲突，编译器无法分辨调用的是哪一个函数，故不能运行。
		cout<<sum;
		return 1;
	}

