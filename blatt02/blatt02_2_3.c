#include <stdio.h>
#include <stdint.h>

int main()
{
	int a,b,c;
	a=453;
	b=111;
	c=-45;
	
	int zahl1, zahl2, zahl3;
	
	if(a<b)
		{
		zahl1 = a;
		zahl2 = b;
		}
	else
		{
		zahl1 = b;
		zahl2 = a;
		}

	if(zahl2<c)
		{
		zahl3 = c;
		}
	else if(c<zahl1)
		{		
		zahl3 = zahl2;
		zahl2 = zahl1;
		zahl1 = c;
		}
	else
		{
		zahl3 = zahl2;
		zahl2 = c;
		}
	
	printf("%d,%d,%d", zahl1, zahl2, zahl3);
}
