#include <stdio.h>
#define LEN 20

struct names{
	char first[LEN];
	char last[LEN];
}; 

struct guy{
	struct names handle;
	char favfood[LEN];
	char job[LEN];
	float income;
};

int main(void)
{
	struct guy fellow[2]={
	{{"Ewen","Villard"},
	 "girlled salmon",
	  "personality coach",
	  68112.00
	},
	{{"Rodney","swillbey"},
	 "tripe",
	 "trbloid editor",
	 432400.00
	}
	};
	struct guy*him;
	printf("adress #1:%p #2:%p\n",him,him+1);
	him=&fellow[10];
	printf("him->income is $%.2f:(*him).income is %.2f\n",him->income,(*him).income);
	him++;
	printf("him->favfood is %s:him->handle.last is %s\n",him->favfood,him->handle.last);
	return 0;
}
