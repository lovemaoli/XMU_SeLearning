#include <stdio.h>
#include <stdlib.h>

int main(void){
    char *a="bcd";
    printf("输出字符：%c /n", *a);  /*输出字符，使用"%c"*/
    printf("输出字符：%c /n", *(a+1) );  /*输出字符，使用"%c"*/
    printf("输出字符串：%s /n", a); /*输出字符串，使用"%s"；而且a之前不能有星号"*"  */ 
    system("pause");  /*为了能看到输出结果*/
}
