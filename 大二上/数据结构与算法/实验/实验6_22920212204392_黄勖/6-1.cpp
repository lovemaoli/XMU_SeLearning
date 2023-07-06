/*
6-1 荷兰国旗问题 
输入： 
10
RBWWRBBRWB
输出：
R R R W W W B B B B 
*/ 
#include<stdio.h>
#include<stdlib.h>
#define maxsize 100
typedef struct {
	char r[maxsize];
	int length;
} SqList;

void solve(SqList &L) {
	int i,j,k;
	char temp;
	i=k=0;
	j=L.length-1;
	while(i<j) {
		while(i<j&&L.r[i]=='W') i++;
		if(L.r[i]=='R') {
			temp=L.r[i];
			L.r[i]=L.r[k];
			L.r[k]=temp;
			i++;
			k++;
		} else if(L.r[i]=='B') {
			while(i<j&&L.r[j]=='B') j--;
			temp=L.r[j];
			L.r[j]=L.r[i];
			L.r[i]=temp;
			j--;
		}
	}

}

int main() {
	SqList L;
	int i;
	scanf("%d",&L.length);
	getchar();
	for(i=0; i<L.length; i++) {
		scanf("%c",&L.r[i]);
	}
	solve(L);
	for(i=0; i<L.length; i++) {
		printf("%c ",L.r[i]);
	}
	return 0;

}


