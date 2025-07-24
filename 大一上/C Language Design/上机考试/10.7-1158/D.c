#include <stdio.h>
int main(void)
{
	int c;
    while(scanf("%d",&c)!=EOF){ 
    	int cnt=0;
		while(c != 1){
			if(c % 2 == 1){
				c = c * 3 + 1;
			}else{
				c = c /2;
			}
			cnt++;
		} 
		printf("%d\n",cnt);
	} 
	return 0;
}
