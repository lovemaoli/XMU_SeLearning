#include <stdio.h>
#define N 60000
//from hkk 
const int dp[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int dr[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char ss[30];//存储询问 

char chk(int y) { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }//判断是否是闰年 

char cmp(int y1, int m1, int d1, int y2, int m2, int d2) {//比较年份 主要为后续判断处在哪个年号做准备 
	if (y1 != y2) return y1 > y2;
	if (m1 != m2) return m1 > m2;
	return d1 >= d2;
}
int tr1(char h) {//年号转年份 
	if (h == 'M') return 1868;
	if (h == 'T') return 1912;
	if (h == 'S') return 1926;
	if (h == 'H') return 1989;
	if (h == 'R') return 2019;
}
char tr2(int y, int m, int d) {//年份转年号 
	if (cmp(y, m, d, 2019, 5, 1)) return 'R';
	if (cmp(y, m, d, 1989, 1, 8)) return 'H';
	if (cmp(y, m, d, 1926, 12, 25)) return 'S';
	if (cmp(y, m, d, 1912, 7, 30)) return 'T';
	return 'M';
}

int Y[N], M[N], D[N], P[200][13][32];//提前将至今的每一天所对应的年号日期计算完毕 询问时直接调用 
void init() {//计算子函数 
	int y = 1868, m = 9, s = 8;
	const int *d = chk(y) ? dr : dp;//计算闰年  指针指向对应数组 
	int i; 
	for (i = 1; i < 60000; ++i) {
		Y[i] = y, M[i] = m, D[i] = s;//从第一天开始 
		P[y - 1868][m][s] = i;//把这是第几天存进P中 
		++s;//下一天 
		if (s > d[m]) s -= d[m], ++m;//下一月 
		if (m > 12) m = 1, ++y, d = chk(y) ? dr : dp;//下一年 
	}
}

int main() {
	int n; init();
	while (~scanf("%s%d", ss, &n)) {
		char h;
		int y, m, s;
		sscanf(ss, "%c%d/%d/%d", &h, &y, &m, &s);
		y += tr1(h) - 1;//转真实年 
		int id = P[y - 1868][m][s] + n;//从计算的数据中找出对应的第几天加上 
		char r = tr2(Y[id], M[id], D[id]);//读年号 
		printf("%c%d/%d/%d\n", r, Y[id] - tr1(r) + 1, M[id], D[id]);
	}
	return 0;
}


