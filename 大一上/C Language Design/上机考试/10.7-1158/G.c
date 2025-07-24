#include <stdio.h>
#include <string.h>
#include <math.h>
int main(void)
{
//	freopen("test.txt","r",stdin);
	printf("        #1 MT Takeaway\n\n");
	char a[30];
	scanf("%[^\n]",&a);
	int i;
	double total=4.0;
	if(strlen(a)%2==1){
		for(i=1;i<=(28-strlen(a))/2;i++){
			printf("-");
		} 
		printf(" %s ",a);
		for(i=1;i<=(28-strlen(a))/2+1;i++){
			printf("-");
		} 
		printf("\n");
	}else{
		for(i=1;i<=(28-strlen(a))/2;i++){
			printf("-");
		} 
		printf(" %s ",a);
		for(i=1;i<=(28-strlen(a))/2;i++){
			printf("-");
		} 
		printf("\n");
	}
	int first=1,remain=0,pau=0;double price=0;
	while(scanf("%s",&a)!=EOF){
		if(first){
			first=0;
			if(strcmp(a, "Dried") == 0){
				remain=2;
				price=3;
				pau=4;
			}
			if(strcmp(a, "Lotus") == 0){
				remain=2;
				price=4;
				pau=4;
			}
			if(strcmp(a, "Fried") == 0){
				remain=2;
				price=7;
				pau=2;
			}
			if(strcmp(a, "Potato") == 0){
				price=2.5;
				pau=13;
			}
			if(strcmp(a, "Sauteed") == 0){
				remain=1;
				price=2.5;
				pau=4;
			}
			if(strcmp(a, "Rice") == 0){
				price=1;
				pau=15;
			}
			printf("%s ",a);
			continue;
		}
		if(remain){
			printf("%s ",a);
			remain--;
			continue;
		} 
		while(pau){
			printf(" ");
			pau--;
		}
		printf("x");
		int shuliang=0;
		int i,cheng=pow(10,strlen(a)-1);
		for(i=0;i<strlen(a);i++){
			shuliang=shuliang + (a[i]-'0')*cheng;
			cheng/=10;
		}
		printf("%s",a);
		for(i=1;i<3-strlen(a);i++){
			printf(" ");
		}
		printf("%5.1lf",price*shuliang);
		total+=price*shuliang;
		printf("\n");
		pau=0;first=1;
	}
	printf("Delivery fees: 4\n------------------------------\n                Total:%6.1lf",total);
	
	return 0;
}
