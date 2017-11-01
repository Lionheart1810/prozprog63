#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define f(x) x*x

typedef uint16_t u16;
typedef unsigned char u8;

int main() {
	printf("\n\nblatt02_2_2 - Aufgabe 2.2\n\n");
	printf("x : f(x) = x*x\n");
	for (float x = -5.0f; x <= 5.0f; x+=.125f)
		printf("%f : %f\n", x, f(x));
	return 0;
}
