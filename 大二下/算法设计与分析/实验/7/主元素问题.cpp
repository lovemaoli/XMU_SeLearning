#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
int n;

// 检查随机选取的元素是否是主元素
bool Majority(int *T, int len, int &num)
{
    int m = rand()%n; // 随机选取一个元素
    num = T[m]; // 记录该元素
    int cnt = 0; // 计数器
    for(int i=0; i<len; i++) // 遍历数组
    {
        if(T[i] == num) // 如果该元素出现
            cnt++;
    }
    return (cnt>len/2); // 如果该元素出现次数超过一半，返回true
}

bool MajorityMC(int *T, int len, double e, int &num) // 蒙特卡洛算法
{
    int k = ceil(log(1/e)/log((float)2)); // 计算k
    for(int i=0; i<k; i++) // 重复k次
    {
        if(Majority(T, len, num))
            return true;
    }
    return false;
}

int main()
{
    int num=999999999; 
    float e = 0.001;
    int T[201];
    cin>>n;
	for(int i=0; i<n; i++)
	{
		cin>>T[i];
	}
    if(MajorityMC(T,n,e,num))
        cout<<num<< endl;
    else
        cout<<"null"<<endl;
    return 0;
}

