#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long a,m,ans,n;
    cin >> n;
    a=n/3;
    m=n%3;
    if(m==1)
    {
        ans=a*7-3;
    }
    else if(m==2)
    {
        ans=a*7+1;
    }
    else if(m==0)
    {
        ans=a*7;
    }
    cout << ans;
}

