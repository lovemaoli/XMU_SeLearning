#include <stdio.h>
typedef long long ll;
const int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 6, 5, 3, 5, 5, 4};//定义每种火柴棍 
int get(ll x) {//计算答案所需的火柴棍 
	int ans = 0;
	if (!x) ans = c[x]; 
	while (x) ans += c[x % 16], x /= 16;
	return ans;
}
int ans;
void dfs(int n, ll a, ll b, char flag) {//深搜 
	if (b > a) return;//得数为负舍去
	if (n < 2) return;//没有可以摆放的火柴棍了 
	if (!flag) {
		if (n < 4) return;//被减数肯定不足以再放了 
		int i; 
		for(i=0;i<16;++i)if(n>c[i])if(a||i)dfs(n - c[i], a * 16 + i, b, 0);//被减数增位 
		if (!a) dfs(n - c[0], a, b, 1);//被减数放完 开始放减数（a为0时） 
		else dfs(n, a, b, 1);//a为1时 
	} else {
	if(b&&n==get(a-b))++ans;//检查答案 b为正 
	if(!b&&n==get(a-b)+c[0])++ans;//b为0 
	int i;
	for(i=0;i<16;++i)if(n>c[i])if(b||i)dfs(n - c[i], a, b * 16 + i, 1);//减数增位 
	}
}
int main() {
	int n;
	while (scanf("%d", &n)!=EOF) {
		ans = 0;
		dfs(n - 3, 0, 0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
