/*
	算法实验3 - 极限编程
	22920212204392 黄勖 
*/
#include<bits/stdc++.h>
using namespace std;
int dp[1000][1000][3];
int main(){
	string s;
	cin >> s;
	if(s.length()==1){
		// 先判断只有一个字符情况 
		if(s=="a"){
			cout << 1;
			return 0;
		}else{
			cout << 0;
			return 0;
		}
	} 
	for(int i=0;i<s.length();i++){
		// 只给自己加括号的情况 
		dp[i][i][s[i]-'a']=1;
	}
	for(int l=1;l<s.length();l++) // 枚举长度 
    {
        for(int i=0;i<s.length()-l;i++) // 枚举起始字符 
        {
            int j=i+l; //本轮括号终止字符 
            for(int p=i;p<j;p++) // 每个地方加括号 
            {
                dp[i][j][0]+=dp[i][p][2]*dp[p+1][j][0]+(dp[i][p][0]+dp[i][p][1])*dp[p+1][j][2]; //a 
                dp[i][j][1]+=dp[i][p][0]*(dp[p+1][j][0]+dp[p+1][j][1])+dp[i][p][1]*dp[p+1][j][1]; //b 
                dp[i][j][2]+=dp[i][p][1]*dp[p+1][j][0]+dp[i][p][2]*(dp[p+1][j][1]+dp[p+1][j][2]); //c 
            }
        }
    }
    cout<<dp[0][s.length()-1][0]<<endl;
    return 0; 
} 
