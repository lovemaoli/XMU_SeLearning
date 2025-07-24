#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a[10]= {0},b[10]= {0},n,m,i=1,k=0,j,h,p,sum;
    cin >> n;
    while(n!=0)
    {
        m=n%10;
        a[i]=m;
        n/=10;
        k++;
        i++;
    }
    h=k;
    for(j=0; j<h-1; j++)
    {

        for(p=0; p<10; p++)
            b[p]=b[p]+a[k]*(k-1)*pow(10,k-2);
        for(p=0; p<a[k]; p++)
            b[p]+=pow(10,k-1);
        sum=1;
        for(p=1; p<k; p++)
            sum+=a[p]*pow(10,p-1);
        b[a[k]]=sum+b[a[k]];
        k--;
    }
    for(j=0; j<h; j++)
        b[0]-=pow(10,j);
    for(j=0; j<=a[1]; j++)
        b[j]=b[j]+1;
    for(p=0; p<10; p++)
    	cout << b[p] << endl;
    return 0;
}

