#include <stdio.h>

int main (void)

{
	int a[3][4][5];
	
	for(int i=0; i<60; i++)
	
	{
		printf("%d\n",a[i/20][i%20/5][i%20%5]=i); 
	}
	
	
}
