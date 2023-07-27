#include <string>

int main(){
	int a;
	scanf("%d",&a);
	int *b;
	b=&a;
	printf("%d",*b);
	a=3;
	printf("%d",*b);
}







