#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned long int u32;

u32 zf[4] = { 9, 98, 987, 98765432 };

int main()
{
    printf("\n\nblatt03_2_6 - Aufgabe 2.6\n\n");
	for(u8 i = 0, sz = sizeof(zf) / sizeof(u32); i < sz; i++)
		printf("(%d * 9) + (%d %% 10) - 2 = %d\n", zf[i], zf[i], (zf[i] * 9) + (zf[i] % 10) - 2);
	return 0;
}