#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;

int main()
{
    printf("\n\nblatt03_2_1 - Aufgabe 2.1\n\n");
	for (u8 i = 1; i <= 100; i++)
		if (i % 3 == 0)
			printf("%d, ", i);
	return 0;
}