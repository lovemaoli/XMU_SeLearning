#include "stdio.h"

void main()
{
    short s1=32767,s2=-32768,s;
    unsigned char uc1=128,uc2=255,uc;

    s=s1+1;
    printf(" %d + 1 = %d\n",s1,s);

    s=s2-3;
    printf(" %d - 3 = %d\n",s2,s);

    uc=uc1+uc2;
    printf(" %d + %d = %d\n",uc1,uc2,uc);

    uc=uc1-uc2;
    printf(" %d - %d = %d\n",uc1,uc2,uc);
}



