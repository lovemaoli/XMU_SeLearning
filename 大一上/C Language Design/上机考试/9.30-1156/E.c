#include<stdio.h> 
int main(){
//	freopen("E.in","r",stdin);
//	freopen("E.out","w",stdout);
	int ch;
	while(scanf("%d",&ch)==1){
		if(ch<=25){
		int ans=1;
		int i;
		for(i=1;i<=ch;i++){
			ans = ans * (i%1000000);
			ans %= 1000000;
		}
		printf("%06d\n",ans);
		}else{
			printf("000000\n");
		} 
	}
	return 0;
}
