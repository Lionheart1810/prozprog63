#include <stdio.h>
#include <stdlib.h>

#define MOD(a, b) (a - ((a / b) * b))

typedef unsigned long int u32;

int main(int argc, char **argv)
{
    printf("\n\nblatt03_1_3c - Aufgabe 1.3 c\n\n");
    u32 a = (argc >= 2) ? atoi(argv[1]) : 10,
        b = (argc == 3) ? atoi(argv[2]) : 11,
		c;
    while(b != 0)
    {
		c = MOD(a, b);
        a = b;
		b = c;
    }
    printf("%d", a);
}