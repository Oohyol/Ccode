#include <stdio.h>
#include <stdlib.h>

 
 int getdata (int i,int n)
{
	if(i==1)
	{
		return n;
	}

	else
    {
    	return getdata(i-1,n)*10+n;
    }	
	
}

int getall (int i, int n)
{
	if (i==1)
	{
		return n;
	}
	else
	{
		return getdata(i,n)+getall(i-1,n);
	}
}

int main ()
{
	int i,j;
	
	printf("%d",getall(scanf("%d",&i),scanf("%d",&j)));
	
	getchar();
		
 } 

