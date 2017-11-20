#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned long int u32;

double arctan(double x)
{
    double current = 2, prev = 0, q = 1, sq = x*x;
    u32 i = 1;
    do
    {
        prev = current;
        current = current - ((q *= sq) / (i + .5)) + ((q *= sq) / (i + 1.5));
        i += 2;
    }
    while (current != prev);
    return current*(x/2.0);
}

int main(int argc, char **argv)
{
    printf("%.32f", arctan((argc == 2) ? atoi(argv[1]) : 1));
	return 0;
}
