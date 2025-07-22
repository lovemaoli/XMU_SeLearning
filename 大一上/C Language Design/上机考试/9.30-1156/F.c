#include <stdio.h> 
#include <math.h>
#define pi 3.1415926536
#define DEC (pi/180)
int main(){
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	long double a,b,c;
	while(scanf("%Lf %Lf %Lf",&a,&b,&c)==3){
		long double x = a * sinl(b*DEC) * cosl(c*DEC);
		long double y = a * sinl(b*DEC) * sinl(c*DEC);
		long double z = a * cosl(b*DEC);
		printf("x = %.10Lf y = %.10Lf z = %.10Lf\n",x,y,z);
	}
	return 0;
}
