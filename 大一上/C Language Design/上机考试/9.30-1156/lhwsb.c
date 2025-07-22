#include <stdio.h>
#include <string.h>

int main() {
//	freopen("J.in","r",stdin);
//	freopen("J.out","w",stdout);
    int a,b,c;
    while(scanf("%d %d %d", &a, &b, &c)!=EOF){
    	printf("%d",a/b);
    	a %= b; 
    	if(c == 0){
    		printf("\n");
    		continue;
		}else printf(".");
    	c--;
		while(c){
			if(a==0){
				printf("0");
				c--;
				continue;
			}
    		a *= 10;
    		printf("%d",a/b);
    		a %= b; 
    		c--;
		}
			if(a==0){
				printf("0");
			}
    		a *= 10;
    		int lastt=a/b;
    		a %= b;
    		a *= 10;
    		if(a/b >= 5){
    			printf("%d",lastt+1);
			}else printf("%d",lastt);
    	printf("\n");
    }
    return 0;
}
