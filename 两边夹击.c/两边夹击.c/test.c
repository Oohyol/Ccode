#include <stdio.h>

char* rever(char *s)
{
	
	
		/* hָ��s��ͷ�� */
		char* h = s;
		char* t = s;
		char ch;

		/* tָ��s��β�� */
		while (*t++) {};
		t--;    /* ��t++���� */
		t--;    /* ������������'\0' */

				/* ��h��tδ�غ�ʱ������������ָ����ַ� */
		while (h != t)
		{
			ch = *h;
			*h++ = *t;    /* h��β���ƶ� */
			*t-- = ch;    /* t��ͷ���ƶ� */
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