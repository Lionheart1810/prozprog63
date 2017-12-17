#include "blatt08_1.h"

void (*funcs[5])() = { array_size, read_keys, random_numbers, bubblesort, mergesort };
u16 *arr = NULL;
size_t size = 0;

void array_size()
{
	if (arr != NULL)
		free(arr);
	printf("Array size: ");
	scanf("%u", &size);
	arr = (u16 *) malloc(size * sizeof(u16));
}

void read_keys()
{
	if (arr != NULL)
	{
		for (size_t i = 0; i < size; i++)
		{
			do
			{
				printf("arr[%d]: ", i);
				scanf("%u", &arr[i]);
			}
			while (arr[i] < 1 || arr[i] > 1000);
		}
		print_array();
	}
}

void random_numbers()
{
	if (arr != NULL)
	{
		srand(time(NULL));
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = ((u16)rand() % 1000) + 1;
		}
		print_array();
	}
}

void bubblesort()
{
	if (arr == NULL)
		printf("Array not defined yet!\n");
	else
		_bubblesort(arr, size);
	print_array();
}

void mergesort()
{
	if (arr == NULL)
		printf("Array not defined yet!\n");
	else
		_mergesort(arr, size);
	print_array();
}

void print_array()
{
	for (size_t i = 0; i < size; i++)
		printf("%d, ", arr[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	int in = 0;
	if (argc == 2)
		in = atoi(argv[1]);
	do
	{
		do in = getchar()-'0'; while (in < 1 || in > 6);
		if (in < 6)
			(*funcs[in-1])();
	}
	while (in != 6);
	return 0;
}