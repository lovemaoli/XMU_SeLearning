#include <stdio.h>
int main(void)
{
	int c;
    while(scanf("%d",&c)!=EOF){ 
    	if(c<10){
    		printf("%d",c);
		}else{
			if(c<100){
				if(c%10==0)printf("%d",c/10);
				else{
					printf("%d%d",c%10,c/10);
				}
			}else{
				if(c%10==0){
					if(c%100==0){
						printf("%d",c/100);
					}else{
						printf("%d%d",(c-c/100*100)/10,c/100);
					}
				}else{
					printf("%d%d%d",c%10,(c%100-c%10)/10,c/100);
				}
			}
		}
		printf("\n");
	} 
	return 0;
}
