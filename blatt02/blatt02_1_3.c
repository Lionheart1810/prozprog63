#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PRINT_ROW(y) {              \
    for (u8 i = 0; i < n-y; i++)    \
        printf(" ");                \
    for (u8 x = 1; x <= y; x++)     \
        printf("%d", x);            \
    for (u8 x = y-1; x > 0; x--)    \
        printf("%d", x);            \
    printf("\n"); }

typedef uint16_t u16;
typedef unsigned char u8; 

int main(int argc, char **argv) {
    printf("\n\nblatt02_1_3 - Aufgabe 1.3\n\n");
    u16 n = (argc == 2) ? atoi(argv[1]) : 9;
    if (n > 0 && n < 10)
    {
        for (u8 y = 1; y <= n; y++)
            PRINT_ROW(y);
        for (u8 y = n-1; y >= 1; y--)
            PRINT_ROW(y);
    }
    return 0;
}