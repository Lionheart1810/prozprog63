#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned short int u16;

int main()
{
    printf("\n\nblatt03_2_3 - Aufgabe 2.3\n\n");
	u16 value = 0;
	printf("    |");
	for(u8 i = 1; i <= 20; i++)
		printf(((i < 10) ? "   %d" : "  %d"), i);
	printf("\n----+");
	for(u8 i = 0; i < 80; i++)
		printf("-");
	printf("\n");
	for (u8 y = 1; y <= 20; y++)
	{
		printf(((y < 10) ? "  %d |" : " %d |"), y);
		for(u8 x = 1; x <= 20; x++)
		{
			value = x*y;
			printf(((value < 100) ? ((value < 10) ? "   %d" : "  %d") : " %d"), value);
		}
		printf("\n");
	}
	return 0;
}