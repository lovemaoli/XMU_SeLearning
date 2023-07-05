#include <stdio.h> 
int main(){
//	freopen("D.in","r",stdin);
//	freopen("D.out","w",stdout);
	char ch;
	while(scanf("%c",&ch)==1){
		if(ch>='a'&&ch<='z'){
			printf("%c\n",ch-32);
		}else{
			if(ch>='A'&&ch<='z'){
				printf("%c\n",ch+32);
			}else{
				if(ch>='0'&&ch<='8'){
					printf("%d\n",ch-'0'+1);
				}else{
					if(ch=='9'){
						printf("0\n");
					}else{
						if(ch!=10){
							printf("%d\n",ch);
						}
					}
				}

			}
		}
	}
	return 0;
}
