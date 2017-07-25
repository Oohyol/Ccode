#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int a[10] = { 0,9,8,1,2,4,3,6,5,7 };

	int *p[10];

	for (int i = 0;i < 9;i++)
	{
		p[i] = a + i;
	}
	for (int i = 0;i < 10 - 1;i++)
	{
		for (int j = 0;j < 10 - 1 - i;j++)
		{
			if (*p[j] > *p[j + 1])
			{
				int *temp = p[j+1];
				*p[j + 1] = *p[j];
				*p[j] = *temp;
			}
		}


	}

	for (int i = 0;i < 10;i++)
	{
		printf("%3d%d\n",a[i], *p[i]);
	}

           getchar();
}

