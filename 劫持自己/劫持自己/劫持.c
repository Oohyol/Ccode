#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"detours.h"
#pragma comment (lib,"detours.lib")//������
int(*poldsystem)(const char*_command) = system;
void newsystem(const char*_command)
{
	char *p = strstr(_command, "mspaint");
	if (p == NULL)
	{
		printf("����\n");
		poldsystem(_command);
	}
	else
	{
		printf("����\n");
	}


}
	

void hook()
{
	DetourRestoreAfterWith();//�ָ�֮ǰ״̬�����ⷴ���ٳ�
	DetourTransactionBegin();//��ʼ�ٳ�
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
	DetourAttach((void**)&poldsystem, newsystem);//�ٳ�
	DetourTransactionCommit();//������Ч

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