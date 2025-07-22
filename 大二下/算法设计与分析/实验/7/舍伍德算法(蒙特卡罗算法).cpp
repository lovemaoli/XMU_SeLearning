#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
int n,k;

bool Majority(int *T, int len, int &num)
{
    int m = rand()%n;
    num = T[m];
    int cnt = 0;
    for(int i=0; i<len; i++)
    {
        if(T[i] <= num)
            cnt++;
    }
    return (cnt==k);
}

bool MajorityMC(int *T, int len, double e, int &num)
{
    int k = ceil(log(1/e)/log((float)2));
    for(int i=0; i<k; i++)
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

