#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char str[10] = "task";

	char newstr[12] = "424list424";
	
	char strall[10];

	sprintf(strall ,"%s%.4s", str, newstr+3);
    
	system(strall);
	
	system("pause");
}

