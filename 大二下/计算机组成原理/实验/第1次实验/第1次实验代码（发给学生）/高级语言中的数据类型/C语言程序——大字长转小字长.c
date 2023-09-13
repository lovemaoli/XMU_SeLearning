#include "stdio.h"


void hex_out(char a)
{
const char HEX[]="0123456789ABCDEF";
printf("%c%c",HEX[(a&0xF0)>>4],HEX[a&0xF]);
}

void out_2byte(char *addr)
{
hex_out (*(addr +1));
hex_out (*(addr +0));
}

void out_4byte(char *addr)
{
hex_out (*(addr +3));
hex_out (*(addr +2));
hex_out (*(addr +1));
hex_out (*(addr +0));
}






int main()
{
    int i=0xFFFF1001;  
    short s; unsigned short us;

    s=i;
    us=i;

    out_4byte(&i);
    printf(" = i = %d \n",i);

    out_2byte(&s);
    printf(" = s = %d \n",s);

    out_2byte(&us);
    printf(" = us = %u \n",us);
}



