#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define TRUE 1
#define FALSE 0

typedef unsigned char u8;
typedef unsigned short u16;

int main(int argc, char **argv);
void array_size();
void read_keys();
void random_numbers();

void (*funcs[5])(void) = { array_size, read_keys, random_numbers, bubblesort, mergesort };
u16 *arr = NULL;

void array_size()
{
	size_t sz = 0;
	if (arr != NULL)
		free(arr);
	printf("Array size: ");
	scanf("%u", &sz);
	arr = malloc(sz * sizeof(u16));
}

void read_keys()
{
	if (arr != NULL)
	{
		u16 n = 0;
		for (size_t i = 0, sz = sizeof(arr)/sizeof(u16); i < sz; i++)
		{
			do
			{
				printf("arr[%d]: ", i);
				scanf("%u", &n);
			}
			while (n < 1 || n > 1000);
			arr[i] = n;
		}
	}
}

void random_numbers()
{
	if (arr != NULL)
	{
		srand(time(NULL));
		for (size_t i = 0, sz = sizeof(arr)/sizeof(u16); i < sz; i++)
		{
			arr[i] = (u16)rand() % 1001;
		}
	}
}

int main(int argc, char **argv)
{
	int in = 0;
	if (argc == 2)
		in = atoi(argv[2][0]);
	do
	{
		do in = getchar()-48; while (in < 1 || in > 6);
		funcs[in]();
	}
	while (in != 6);
	return 0;
}