#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;
typedef unsigned long long u64;

int main(int argc, char **argv)
{
    printf("\n\nblatt03_2_2 - Aufgabe 2.2\n\n");
	u32 var = (argc == 2) ? atoi(argv[1]) : 2;
	u64 fak = 1;
	if (var > 0)
		for (u32 i = 1; i <= var; fak *= i++);
	printf("%lld", fak);
	return 0;
}