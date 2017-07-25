#include <stdio.h>

int main ()
{
	char i,j;

for (i = 'A', j = 'Z';i < j;i++, j--)
   {
	printf("%s,%s", i, j);
	}

    getchar();

}