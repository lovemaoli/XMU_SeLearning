/*
	算法实验3 - 贪心策略删数问题
	22920212204392 黄勖 
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin >> s;
	int m;
	cin >> m;
	while(m--){
		int pos=0;
		for(int i=1;i<s.length();i++){
			//找最大的数 
			if(s[i]>s[pos]){
				pos=i;
			}
		}
		//贪心每次取最大数字删除 
		s.erase(pos,1);
	} 
	cout << s << endl; 
    return 0; 
} 
