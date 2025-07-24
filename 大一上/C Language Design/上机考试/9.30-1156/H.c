#include <stdio.h>
#include <string.h>

int main() {
//	freopen("H.in","r",stdin);
//	freopen("H.out","w",stdout);
    char numberA[30], numberB[30];
    while(scanf("%s %s", numberA, numberB)!=EOF){
    	int n = strlen(numberA), m = strlen(numberB);
    	int a[30], b[30];
    	int i, j;
    	for (i = 0; i < 30; i++){
    		a[i] = 0; b[i] = 0;
		}
    	for (i = 0, j = n - 1; i < n; i++, j--) {
    	    a[i] = numberA[j] - '0';
    	}
    	for (i = 0, j = m - 1; i < m; i++, j--) {
    	    b[i] = numberB[j] - '0';
    	}
    	int c[30];
    	for (i = 0; i < 30; i++) {
    	    c[i] = 0;
    	}
    	int maxn;
    	if(n > m){
    		maxn = n;
		}else{
			maxn = m;
		}
    	for (i = 0; i < maxn; i++) {
    	    c[i] = a[i] + b[i];
    	}   
    	for (i = 0; i < maxn + 1; i++) {
    	    if (c[i] >= 10) {
    	        c[i + 1] += 1;
    	        c[i] %= 10;
    	    }
    	}
    	for (j = 29; j > 0; j--) {
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
