#include<stdio.h>
int main(){
	char a;
	int get=1;
	while(scanf("%c",&a)!=EOF){
		if(a==10){
			get=1;
			printf("\n");
			continue;
		}
		if(get==4||get==6)printf(" ");
		printf("%c",a);
		get++;
	}
	return 0;
} 
