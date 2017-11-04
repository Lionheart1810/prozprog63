#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define U32_MAX 4294967295

typedef unsigned long int u32;

int main(int argc, char **argv) {
	printf("\n\nblatt02_2_6 - Aufgabe 2.6\n\n");
	u32 var = (argc == 2) ? atoi(argv[1]) : 4294967290;
	for (u32 i = 1; i < U32_MAX-var+1; i++)
		printf("%d, ", i);
	return 0;
}
