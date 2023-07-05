#include<stdio.h> 
int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	double x,y,z;
	while(scanf("%lf %lf %lf",&x,&y,&z)==3){
		printf("%.3lf\n",(x+y+z)/3.0) ;
	}
	return 0;
}
