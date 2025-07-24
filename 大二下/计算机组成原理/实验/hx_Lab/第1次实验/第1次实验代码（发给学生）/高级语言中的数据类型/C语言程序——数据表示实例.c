#include "stdio.h"

union
{
	int i;  unsigned int ui; float f;
	short s; unsigned short us;
	char c; unsigned char uc;
}t;

void hex_out(char a)
{
	const char HEX[]="0123456789ABCDEF";
	printf("%c%c",HEX[(a&0xF0)>>4],HEX[a&0xF]);
}

void out_1byte(char *addr)
{
	hex_out (*(addr +0));
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

main()
{
	t.i=0xC77FFFFF;

	out_4byte(&t.i);
	printf(" = %d \n",t.i);

	out_4byte(&t.ui);
	printf(" = %u \n",t.ui);

	out_4byte(&t.f);
	printf(" = %f \n",t.f);

	out_2byte(&t.s);
	printf(" = %d \n",t.s);

	out_2byte(&t.us);
	printf(" = %u \n",t.us);

	out_1byte(&t.c);
	printf(" = %d \n",t.c);

	out_1byte(&t.uc);
	printf(" = %d \n",t.uc);
}




