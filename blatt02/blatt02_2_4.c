#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint16_t u16;
typedef unsigned char u8;
typedef unsigned long long u64;

int main(int argc, char **argv) {
	printf("\n\nblatt02_2_4 - Aufgabe 2.4\n\n");
	u64 var = (argc == 2) ? atoi(argv[1]) : 12;
	for (u64 i = 1; i < var; i++)
	{
		if (var % i == 0)
			printf("%d, ", i);
	}
	return 0;
}
