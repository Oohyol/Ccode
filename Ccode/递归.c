#include <stdio.h>
#include <stdlib.h>
int ilist(int a[], int i)
{
	if (i == 1)
		
		return 1;

	else if (i == 2)
		
		return a[1] > a[0];
	
	else
		
		return ilist(a[i], i-1) && a[i - 1] > a[i - 2];

}




int main()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,0 };
	
	int flag=ilist(a, 10);
	
	if (flag)
	{
		printf("µİÔö");
	}
	else
	{
		printf("²»µİÔö");
	}

	getchar();
}
