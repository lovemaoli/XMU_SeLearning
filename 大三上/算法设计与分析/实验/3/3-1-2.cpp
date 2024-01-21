/*
	算法实验3 - 贪心策略不可重复最优分解问题
	22920212204392 黄勖 
*/
#include<bits/stdc++.h>
using namespace std;
vector<int> mult; 
int main(){
	long long n;
	cin >> n;
	if(n==1){
		cout << 1 << endl;
		return 0;
	}
	long long tmp=n;
	int cnt=2,i=-1;
	while(tmp>=cnt){
		//贪心从小到大分解 
		mult.push_back(cnt);
		tmp-=cnt;
		cnt++;
		i++;
	}
	//对求和剩余数做处理 
	if(tmp==cnt-1){
		mult[i]++;
	}
	for(int j=i;j>=0&&tmp;j--){
		tmp--;
		mult[j]++;
	}
	//计算答案 
	long long ans=1;
	for(auto mul:mult){
		ans*=mul;
	}
	cout << ans << endl;
    return 0; 
} 
