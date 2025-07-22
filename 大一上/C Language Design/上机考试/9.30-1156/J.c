#include <stdio.h>
#include <string.h>

int main() {
//	freopen("J.in","r",stdin);
//	freopen("J.out","w",stdout);
    char numberA[501], numberB[501];
    while(scanf("%s %s", numberA, numberB)!=EOF){
    	int n = strlen(numberA), m = strlen(numberB);
    	int a[n], b[m];
    	int i, j;
    	for (i = 0, j = n - 1; i < n; i++, j--) {
    	    a[i] = numberA[j] - '0';
    	}
    	for (i = 0, j = m - 1; i < m; i++, j--) {
    	    b[i] = numberB[j] - '0';
    	}
    	int c[1001];
    	for (i = 0; i < 1001; i++) {
    	    c[i] = 0;
    	}
    	for (i = 0; i < n; i++) {
    	    for (j = 0; j < m; j++) {
    	        c[i + j] += a[i] * b[j];
    	    }
    	}   
    	for (i = 0; i < n + m; i++) {
    	    if (c[i] >= 10) {
    	        c[i + 1] += c[i] / 10;
    	        c[i] %= 10;
    	    }
    	}
    	for (j = 1000; j > 0; j--) {
    	    if (c[j] != 0)
    	    break;
    	}
    	for (i = j; i >= 0; i--) {
    	printf("%d", c[i]);
    	}
    	printf("\n");
    }
    return 0;
}
