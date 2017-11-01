#include <stdio.h>
#include <stdint.h>

int main()
{
	int i,j;
	
	for(i=0;i<6;i++)
	{
		for(j=i;j<6;j++)
		{
		printf("*");
		}
	printf("\n");	
	}
}