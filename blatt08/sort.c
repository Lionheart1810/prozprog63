#include "sort.h"

void swap(u16 *a, u16 *b)
{
	u16 c = *a;
	*a = *b;
	*b = c;
}

void _bubblesort(u16 *arr, size_t size)
{
	for (size_t x = size; x > 1; x--)
	{
		for (size_t y = 0; y < x - 1; y++)
		{
			if (arr[y] > arr[y + 1])
				swap(arr + y, arr + y + 1);
		}
	}
}

void _mergesort(u16 *arr, size_t size)
{
	if (size > 1)
	{
		size_t i = (size / 2), k = ((size + 1) / 2);
		u16 *arr1 = (u16 *) malloc(sizeof(u16) * i);
		u16 *arr2 = (u16 *) malloc(sizeof(u16) * k);
		memcpy(arr1, arr, i * sizeof(u16));
		memcpy(arr2, arr + i, k * sizeof(u16));
		_mergesort(arr1, i);
		_mergesort(arr2, k);
		for (u16 *end = (u16 *)(arr + size), 
			*end1 = (u16 *)(arr1 + i), 
			*end2 = (u16 *)(arr2 + k); arr < end; arr++)
		{
			if (arr1 == end1)
			{
				for (; arr2 < end2; arr2++, arr++)
					*arr = *arr2;
				break;
			}
			if (arr2 == end2)
			{
				for (; arr1 < end1; arr1++, arr++)
					*arr = *arr1;
				break;
			}
			if (*arr1 < *arr2)
			{
				*arr = *arr1;
				arr1++;
			}
			else
			{
				*arr = *arr2;
				arr2++;
			}
		}
	}
}