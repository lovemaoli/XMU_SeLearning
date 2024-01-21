#include<stdio.h>
#include<string.h>
const int N =26;
const int LEN=7;
char str[LEN];
int c[N+1][N+1]; //c[i][j]记录组合数

//使用杨辉三角计算n以内的c[i][j]  c[i][j]=c[i-1][j-1]+c[i-1][j];
void Get_C(int n,int c[][N+1]) {
	int i,left,right;
	c[0][0]=1;
	for(i=1; i<=n; i++) {
		c[i][0]=1;
		c[i][i]=1;
		left=1;
		right=i-1;
		while(left<=right) { //组合数性质：c[i][j]=c[i][i-j];
			c[i][left] = c[i-1][left-1]+c[i-1][left];
			c[i][right--]=c[i][left++];
		}
	}
}

//统计长度小于len的合法串
int Get_smaller(int len) {
	int i,curans=0;
	for(i=1; i<len; i++)
		curans+=c[N][i];//统计长度为i的字符串种类
	return curans;
}

//从左到右逐个统计相同前缀下的字符串个数
int Get_prefix(int len,char*str) {
	int i,j,curans=0;
	int pre=-1;   //记录前一字符
	for(i=0; i<len; i++) { //统计前缀为i-1位时，可出现的合法情形
		int cur=str[i]-'a';    //当前字符
		for(j=pre+1; j<cur; j++) { //枚举摆放于当前前缀后的第一个字符，统计其合法串个数。
			curans+=c[N-j-1][len-i-1];
		}
		pre=cur; //保留当前字符，作为情形的前一字符使用
	}

	return curans;

}

//判断输入是否非法
bool Is_legal(int len,char*str) {
	int i;
	for(i=1; i<len; i++)
		if(str[i]<=str[i-1]) {
			return false;
		}
	return true;
}


int main() {
	Get_C(N,c);   // 使用杨辉三角计算26以内的所有组合数c[i][j]
	int tests;
	while(scanf("%d",&tests)!=EOF) {
		while(tests--) {
			scanf("%s",str);
			int len=strlen(str);
			int ans;
			bool flag=Is_legal(len,str);//判断输入串本身是否非法

			if(flag==false) { //输入字符串本身非法直接输出0
				printf("0\n");
				continue;
			}

			ans =0;
			ans+=Get_smaller(len); //统计长度小于len的合法串

			ans+=Get_prefix(len,str); //从左到右逐个统计相同前缀下的字符串个数

			ans+=1;    //加入其本身值
			printf("%d\n",ans);
		}
	}
	return 0;

}
