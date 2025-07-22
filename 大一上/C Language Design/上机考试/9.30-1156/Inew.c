#include <stdio.h>
void inner(long long int a, long long int b, long long int c) {
	int is_first = 1;
	c++;
	while(c>0){
		long double x = 1;
		long long int q = 0;
		if(c < 12 && x == 1) {
			int i;
			for (i = 0; i< c-1;i++)
				x *= 10;
			q=(a+b*0.5/x)/b;
		}
		else
			q=a/b;
		printf("%lld", q);
		c--;
		if (is_first) {
			is_first = 0;
			if(c>0)
				printf(".");
		}
		a -= q * b;
		a = a * 10;
	}
	printf("\n");
}
int main(){
    long long int A,B,C;
    while(scanf("%lld %lld %lld", &A, &B, &C)!=EOF){
    	inner(A,B,C);
    }
    return 0;
}
