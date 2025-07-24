#include <stdio.h> 
int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	int x,y,z,sum;
	int month[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
	while(scanf("%d %d %d",&x,&y,&z)==3){
		sum=month[y]+z;
		if(x % 400 == 0 || (x % 4 == 0 && x % 100 != 0)){
			if(y>2){
				sum++;
			}
		}
		printf("%d\n",sum);
	}
	return 0;
}
