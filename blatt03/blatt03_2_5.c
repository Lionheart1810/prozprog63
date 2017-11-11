#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned long int u32;

u32 zf[4] = { 1, 12, 123, 123456789 };

int main()
{
    printf("\n\nblatt03_2_5 - Aufgabe 2.5\n\n");
	for(u8 i = 0, sz = sizeof(zf) / sizeof(u32); i < sz; i++)
		printf("(%d * 9) + (%d %% 10) + 1 = %d\n", zf[i], zf[i], (zf[i] * 9) + (zf[i] % 10) + 1);
	return 0;
}