#include <stdio.h>
#include <string.h>

void reverseString(char *str)
{
	char ch;
	char *temp = str;
	while (*str) {
		str++;
	}
	str--;
	while (temp < str) {
		printf("temp:%u--%c   str:%u--%c\n", temp, *temp, str, *str);
		ch = *temp;
		*temp++ = *str;
		*str-- = ch;
	}
}

int main(void)
{
	char str[] = "hello world";
	reverseString(str);
	printf("\n%s\n", str);

	return 0;
}
