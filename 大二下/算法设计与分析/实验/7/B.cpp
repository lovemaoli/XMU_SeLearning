#include <bits/stdc++.h>
using namespace std;

int n,k;

bool Majority(int *T, int len, int &num) //检查选择的元素是不是第k大的元素
{
    int m = rand()%n; // 随机选取一个元素
    num = T[m]; // 记录该元素
    int cnt = 0; // 计数器
    for(int i=0; i<len; i++)  // 遍历数组
    {
        if(T[i] <= num)  
            cnt++; // 计算小于等于num的元素个数
    }
    return (cnt==k);
}

bool MajorityMC(int *T, int len, double e, int &num)
{
    int k = ceil(log(1/e)/log((float)2)); // 计算k: 重复k次
    for(int i=0; i<k; i++)
    {
        if(Majority(T, len, num)) // 检查选择的元素是不是第k大的元素
            return true;
    }
    return false;
}

int main()
{
    int num=INT_MAX;
    float e = 0.001;
    int T[207];
    cin>>n>>k;
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

