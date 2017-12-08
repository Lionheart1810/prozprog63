#include <stdio.h>
#include <stdlib.h>

#define ERATOSTHENES_MAX 199

typedef unsigned char u8;
typedef unsigned long int u32;

u8 arr[ERATOSTHENES_MAX];

int main()
{
	for (u8 i = 0; i < ERATOSTHENES_MAX; i++)
		arr[i] = i + 2;
	for (u8 i = 0; i < ERATOSTHENES_MAX; i++)
	{
		if (arr[i] != 0)
		{
			for (u8 j = i+1; j < ERATOSTHENES_MAX; j++)
			{
				if (arr[j] % arr[i] == 0)
				{
					arr[j] = 0;
				}
			}
		}
	}
	for (u8 i = 0; i < ERATOSTHENES_MAX; i++)
		if (arr[i] != 0)
			printf("%d, ", arr[i]);
	return 0;
}