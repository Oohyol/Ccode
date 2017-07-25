#include<stdio.h>
#include<Windows.h>
_declspec(dllexport) void go()
{
	MessageBoxA(0, "hello", "world", 0);
}
_declspec(dllexport)void add(int a,int b)
{
	return a + b;
}