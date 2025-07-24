/*
	算法实验3 - 贪心策略可重复最优分解问题
	22920212204392 黄勖 
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n;
	long long ans; 
	cin >> n;
	if(n==1){
		//特殊情况 
		cout << 1;
		return 0;
	}
	if(n%3==0){
		ans = pow(3,n/3);
		//全部分解为3 
	}else if(n%3==1){
		ans = pow(3,n/3-1)*4;
		//分解为两个2和其他全部3 
	}else{
		ans = pow(3,n/3)*2;
		//分解为一个2和其他全部3 
	}
	cout << ans << endl;
    return 0; 
} 
