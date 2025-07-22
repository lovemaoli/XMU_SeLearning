#include <stdio.h>
#include <math.h>
int mon[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int pingfang(int a){
	return a == (int)sqrt(a) * (int)sqrt(a);
}
int main(void)
{
	int c;
    while(scanf("%d",&c)!=EOF){ 
    	int a,b;
    	if(c % 4 != 0){
    		printf("no leap day\n");
    		continue;
		}
		if(c % 100 == 0 && c % 400 != 0){
    		printf("no leap day\n");
    		continue;
		}
		int flag = 0;
    	for(a = 1;a <= 12;a++){
    		for(b = 1;b <= mon[a];b++){
    			if(pingfang(c + a*31 + b)){
    				printf("%d %d %d\n",c,a,b);
    				flag = 1;
    				break;
				}
			}
			if(flag){
				break;
			}
		}
		if(flag == 0)printf("no leap day\n");
	} 
	return 0;
}
