#include <stdio.h>

char* rever(char *s)
{
	
	
		/* h指向s的头部 */
		char* h = s;
		char* t = s;
		char ch;

		/* t指向s的尾部 */
		while (*t++) {};
		t--;    /* 与t++抵消 */
		t--;    /* 回跳过结束符'\0' */

				/* 当h和t未重合时，交换它们所指向的字符 */
		while (h != t)
		{
			ch = *h;
			*h++ = *t;    /* h向尾部移动 */
			*t-- = ch;    /* t向头部移动 */
		}

		return(s);
	
}

void main()
{
	char *s = "hello";
	rever(s);

	printf("%s", s);
	return 0;
}