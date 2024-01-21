#include <bits/stdc++.h>
using namespace std;
bool zhishu[40000]={0};
int calzhi(){
	for(int i=2;i<=39999;i++){
		int flag=1;
		for(int j=2;j<i;j++){
			if(i%j==0){
				flag=0;
				break;
			}
		}
		if(flag)zhishu[i]=1;
	}
}
int calc(int n){
	if(n==1)return 1;
	int ret=1,dqyu=2;
	while(n!=1){
		if(dqyu>39999)break; 
		int cheng=1;
		while(n%dqyu==0){
			cheng++;
			n/=dqyu;
		}
		dqyu++;
		while(zhishu[dqyu]==0)dqyu++;
		ret*=cheng;
	}
	return ret;
}
int main()
{
    int a,b;
    cin >> a >> b;
    calzhi();
    int maxx=0;
    for(int i=a;i<=b;i++){
    	int ans=calc(i);
    	if(ans>maxx)maxx=ans;
	}
	cout << maxx;
    return 0;
}

