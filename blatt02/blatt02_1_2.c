#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint16_t u16;
typedef unsigned char u8; 

int main(int argc, char **argv) {
	printf("\n\nblatt02_1_2 - Aufgabe 1.2\n\n");
	u16 var;
	var = (argc == 2) ? atoi(argv[1]) : 65535;
	for (u8 i = 0; i < 16; i++)
		printf("%d", (var >> (15-i)) & 1);
	return 0;
}
