#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"detours.h"
#pragma comment (lib,"detours.lib")//库连接
int(*poldsystem)(const char*_command) = system;
void newsystem(const char*_command)
{
	char *p = strstr(_command, "mspaint");
	if (p == NULL)
	{
		printf("良民\n");
		poldsystem(_command);
	}
	else
	{
		printf("刁民\n");
	}


}
	

void hook()
{
	DetourRestoreAfterWith();//恢复之前状态，避免反复劫持
	DetourTransactionBegin();//开始劫持
	DetourUpdateThread(GetCurrentThread());//刷新当前线程
	DetourAttach((void**)&poldsystem, newsystem);//劫持
	DetourTransactionCommit();//立刻生效

}


void main()
{
	system("notepad");

	hook();
	system("notepad");
	system("mspaint");
	system("tasklist");






	system("pause");
	getchar();
}