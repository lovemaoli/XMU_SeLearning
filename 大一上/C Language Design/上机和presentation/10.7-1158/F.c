#include <stdio.h>
int main(void)
{
	int c;
    while(scanf("%d",&c)!=EOF){ 
    	if(c>100)printf("Score is error!\n");
    	if(c>=90&&c<=100)printf("A\n");
    	if(c>=80&&c<90)printf("B\n");
    	if(c>=70&&c<80)printf("C\n");
    	if(c>=60&&c<70)printf("D\n");
    	if(c>=0&&c<60)printf("E\n");
    	if(c<0)printf("Score is error!\n");
	} 
	return 0;
}
