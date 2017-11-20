#include <stdio.h>

typedef unsigned char u8;
typedef unsigned long int u32;



double sin(double x)
{
    double current = 1, prev = 0, q = 1, sq = x*x, fak = 1;
    u32 i = 0, ifak = 1;
    do
    {
        prev = current;
        current -= ((q *= sq) / ((ifak)*(ifak+=1)*(ifak+=1))) + ((q *= sq) / ((ifak)*(ifak+=1)*(ifak+=1)));
        i += 2;
        printf("i: %d, sin: %.32f\n", 1, current*x);
    }
    while (current != prev);
    return current*(x);
}

int main()
{
    printf("%.32f\n", sin(0.5));
	return 0;
}
