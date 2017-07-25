#include<stdio.h>
#include<Windows.h>
void *p();
void main()
{
	HMODULE hmod = LoadLibraryA("dll调用.dll");
	if (hmod == NULL)
	{
		system("errorload");

	}
	void(*p1)() = (void(*)())GetProcAddress(hmod, "go");
	int(*p2)(int a, int b) = (int(*)(int a, int b))GetProcAddress(hmod, "add");
	if (p1 == NULL)
	{
		system("error find");
	}
	else
	{
		p1();
		printf("%d", p2(10, 20));
	}
	FreeLibrary(hmod);
	system("pause");
}