#include <stdio.h> 
int main(){
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	int x;
	while(scanf("%d",&x)==1){
		if(x%400==0){
			printf("Leap year\n");	
		} else if(x%100==0){
			printf("Not leap year\n");
		} else if(x%4==0){
			printf("Leap year\n");
		}else printf("Not leap year\n");
	}
	return 0;
}
