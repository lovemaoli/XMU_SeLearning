#include <stdio.h>
#include <string.h>

int main() {
//	freopen("G.in","r",stdin);
//	freopen("G.out","w",stdout);
    double A;
    while(scanf("%lf", &A)!=EOF){
    	if(A==100.0)A-=0.0000000001;
    	printf("%.10lf\n",A+0.0000000001);
    }
    return 0;
}
