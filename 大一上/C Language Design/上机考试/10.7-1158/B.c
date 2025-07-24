#include <stdio.h>
int main(void)
{
	char a;int flag;//a是输入的字符 flag是判断是不是已经有空格了 
    while(scanf("%c",&a)!=EOF){//读入字符 
    	if(a==' '){
    		if(flag==1)continue;//跳过输出重复空格 
    		else {
    			flag=1;//标记已经有空格了 
    			printf(" ");
			}
		}else{
			printf("%c",a);//正常输出字符 
			flag=0;
		} 
	} 
	printf("\n");
	return 0;
}
