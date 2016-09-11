#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include<iterator>
#include<list>
#include<string.h>
#include<stdio.h>
#include<string>
using namespace std;

#define MAXNUM 10000

static int data[MAXNUM] = {0};
struct mem
{
	int start;
	int end;
}mem[MAXNUM];
static int handle = 1;
int CmdNew(int size,int max)
{
	//cout<<"cmdnew  "<<size<<endl;
	int flag = 0;
	if(size > max)
		return -1;
	for(int i = 1; i <= max - size;i++)
	{
		flag = i;
		while(data[flag] == 0 && i + size <= max)
		{
			flag++;
			if(flag - i == size)
				break;
		}
		if(flag - i == size)
		{
			mem[handle].start = i;
			mem[handle].end = i + size;
			
			for(int j = i;j < i + size;j++)
				data[j] = handle; //设置一下标志位
			handle++;
			return handle - 1;
		}
		else //=i时候没有找到
		{
			if(flag > i)
				i = i + flag - 1;
			flag = 0;
		}
	}
	return -1;
}
int CmdDel(int size,int max)
{
	//cout<<"cmddel  "<<size<<endl;
	if(handle < size)
		return -1;
	if(mem[size].start != 0 && mem[size].end != 0)
	{
		for(int i = mem[size].start;i < mem[size].end;i++)
		{
			data[i] = 0;
		}
		mem[size].start = 0 ;
	    mem[size].end =0;
	}
	else
		return -1;
	
	return 0;
}
void CmdDef(int max)
{
	//cout<<"cmddef"<<endl;
	int flag = 0;
	int num = 0;//数据大小
	int i =1;
	int end = 0;
	int start = 0;
	while(i <= max)
	{
		flag = i;
		while(data[flag] == 0 && flag <= max)
			flag++;
		if(flag >max)
			break;
		//找到已存数据转移到前面为0的地方
		if(flag != i)
		{
			end = mem[data[flag]].end;
			start =mem[data[flag]].start;
			num = end - start ;
			for(int x = start;x < end;x++)
			{
				data[i] = data[x];
				data[x] = 0;
				i++;
			}
			mem[data[i-1]].end = i -1;
			mem[data[i-1]].start = i - num;
		}
		else
			i++;
	}
}
int main(void)
{
	int T,MaxMem;
	cin>>T>>MaxMem;
	char cmd[4];
	int ret = -1;
	int tmp; //存储后面的数字
	for(int i = 0;i < T;i++)
	{
		cin>>cmd;
		if(strcmp(cmd,"new") == 0)
		{
			cin>>tmp;			
			ret = CmdNew(tmp,MaxMem);
			if(ret == -1)
				cout<<"NULL"<<endl;
			else
				cout<<ret<<endl;
		}
		else if(strcmp(cmd,"del") == 0)
		{
			 cin>>tmp;
			 ret = CmdDel(tmp,MaxMem);
			 if(ret == -1)
				 cout<<"ILLEGAL_OPERATION"<<endl;
		}
		else if(strcmp(cmd,"def") == 0)
		{
			CmdDef(MaxMem);
		}
	}
	system("pause");
	return 0;

}