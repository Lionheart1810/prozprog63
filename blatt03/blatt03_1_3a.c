#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;

int main(int argc, char **argv)
{
    printf("\n\nblatt03_1_3a - Aufgabe 1.3 a\n\n");
    u32 a = (argc >= 2) ? atoi(argv[1]) : 10,
        b = (argc == 3) ? atoi(argv[2]) : 11,
        c;
    while(a != 0 && b != 0)
    {
        c = abs(a - b);
        if (a >= b)
            a = c;
        else
            b = c;
    }
    printf("%d", (a != 0) ? a : b);
}