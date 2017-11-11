#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("\n\nblatt03_1_1 - Aufgabe 1.1\n\n");
	float eps_f = 1.0f;
	double eps_d = 1.0;
	do; while((float) (1.0f + ((eps_f /= 2.0f) / 2.0f)) != 1.0f);
	do; while((double) (1.0 + ((eps_d /= 2.0) / 2.0)) != 1.0);
	printf("float: %e\ndouble: %e", eps_f, eps_d);
}