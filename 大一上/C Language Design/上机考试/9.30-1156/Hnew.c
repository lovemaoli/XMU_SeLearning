#include <stdio.h>
#include <string.h>
int FinallyPrint[200],tail,point;
void GeiYeXieRu(int du,int flag){
	if(flag == 1){
		point = tail;
		tail++; 
		return;
	}
	if(du > 9){
		GeiYeXieRu(du/10,0);
		FinallyPrint[tail]=du%10;
		tail++;
	}else{
		FinallyPrint[tail]=du;
		tail++;
	}
}
void GeiYeShuChu(int Rush){
	int p;
	if(Rush){
		int testFinal=tail-1,last=1;
		while(testFinal){
			if(FinallyPrint[testFinal]!=9&&testFinal!=point){
				FinallyPrint[testFinal]++;
				last=0;
				break;
			}
			FinallyPrint[testFinal]=0; 
			testFinal--;
		}
		if(last){
			printf("1");
			for(p=1;p<tail;p++){
				if(p==point){
					printf(".");
					continue;
				}
				printf("0");
			}
			printf("\n");
			return;
		}
	}
	for(p=1;p<tail;p++){
		if(p==point){
			printf(".");
			continue;
		}		
		printf("%d",FinallyPrint[p]);
	}
	printf("\n");
}
int main() {
//	freopen("J.in","r",stdin);
//	freopen("J.out","w",stdout);
    int a,b,c;
    while(scanf("%d %d %d", &a, &b, &c)!=EOF){
//    	for(int i=1;i<200;i++)FinallyPrint[i]=0;
		tail = 1;point = -1;
    	GeiYeXieRu(a/b,0);
    	a %= b; 
    	if(c == 0){
			if(a*10/b>5){
				GeiYeShuChu(1);
			}else GeiYeShuChu(0);
    		continue;
		}else GeiYeXieRu(0,1);
		while(c){
			if(a==0){
				GeiYeXieRu(0,0);
				c--;
				continue;
			}
    		a *= 10;
    		GeiYeXieRu(a/b,0);
    		a %= b; 
    		c--;
		}
		a *= 10;
    	if(a/b >= 5){
    		GeiYeShuChu(1);
		}else GeiYeShuChu(0);
    }
    return 0;
}
