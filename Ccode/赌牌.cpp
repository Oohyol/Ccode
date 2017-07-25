#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()

{
	time_t ts;
	
    int unsigned num =time(&ts);
    
    srand(num);
	
	int data=rand()%100;
	
	data>=90?printf("с╝ак"):printf("йДак");
	

	
}
