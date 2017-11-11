#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;
typedef unsigned long long u64;

int main()
{
	double e = 1.0, prev = 0.0;
	u64 fak = 1;
	for (u32 i = 2; e != prev; fak *= i++)
	{
		prev = e;
		e += (1.0 / fak);
		printf("i: %d, fak: %lld, prev: %e, e: %e\n", i, fak, prev, e);
	}
	printf("%e", e);
	return 0;
}