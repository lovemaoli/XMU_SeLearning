#include <bits/stdc++.h>
using namespace std;
int n;

bool judge(int *T, int len, int &num) // 检查选择的元素是不是主元素
{
    int m = rand()%n;
    num = T[m]; // 记录元素
    int cnt = 0;
    for(int i=0; i<len; i++)
    {
        if(T[i] == num)
            cnt++;
    }
    return (cnt>len/2); // 出现次数超过一半
}

bool Montekaluo(int *T, int len, double e, int &num) // 蒙特卡洛算法
{
    int k = ceil(log(1/e)/log((float)2));
    for(int i=0; i<k; i++)
    {
        if(judge(T, len, num))
            return true;
    }
    return false;
}

int main()
{
    int num=INT_MAX;
    
    float e = 0.001;
    int T[207];
    cin>>n;
	for(int i=0; i<n; i++)
	{
		cin>>T[i]; // 输入
	}
    if(Montekaluo(T,n,e,num)){
        cout<<num<< endl;
    } else cout<<"null"<<endl;
    return 0;
}

