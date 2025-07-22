#include "stdio.h"
#include <math.h>

int f1(unsigned n)
{
    int sum=1,power=1;
    for(unsigned i=0; i<=n-1; i++)
    {
         power *= 2;
         sum += power;
    }
    return sum;
}

float f2(unsigned n)
{
    float sum=1,power=1;
    for(unsigned i=0; i<=n-1; i++)
    {
         power *= 2;
         sum += power;
    }
    return sum;
}

int f3(int n)
{
    int sum=1,power=1;
    for(int i=0; i<=n-1; i++)
    {
         power *= 2;
         sum += power;
    }
    return sum;
}

int main()
{
    unsigned n;  
    int n1;

//    n=0;
//    printf("f1(%d)=%d\n",n,f1(n));

//    n=0;
//    printf("f2(%d)=%d\n",n,f2(n));

    n1=0;
    printf("f3(%d)=%d\n",n1,f3(n1));

    n=23;
    printf("f1(%d)=%d    f2(%d)=%f\n",n,f1(n),n,f2(n));

    n=24;
    printf("f1(%d)=%d    f2(%d)=%f\n",n,f1(n),n,f2(n));

    long long int f31=pow(2,32)-1;
    n=31;
    printf("f(31)=%lld   f1(%d)=%d\n",f31,n,f1(n));

    long long int f30=pow(2,31)-1;
    n=30;
    printf("f(30)=%lld   f1(%d)=%d\n",f30,n,f1(n));

    n=127;
    printf("f2(%d)=%f\n",n,f2(n));

    n=126;
    printf("f2(%d)=%f\n",n,f2(n));
}

