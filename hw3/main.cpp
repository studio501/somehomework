
#include <stdlib.h>

#include <iostream>
#include <fstream>
using namespace std;


#define HW1_MAX_UNDIFF 10000


typedef struct ST
{
	int val;
	int count;
	ST()
		:val(-1)
		,count(0)
	{

	}
	void set(ST* s1,ST* s2)//赋值函数  
	{  
		s1->val = s2->val;  
		s1->count = s2->count;  
	}  
	ST& operator=(const ST& s)//重载运算符  
	{  
		set(this,(ST*)&s);
		return *this;
	}  
	ST(const ST& s)//复制构造函数  
	{  
		*this = s;
	}
	bool operator<(const ST &s)
	{
		return (*this).val < s.val;
	}
}Stats_Number;


bool checkExist(Stats_Number *s,int checkNum,int nowLen,int &findIndex)
{
	bool flag = false;
	for(int i=0;i<nowLen;++i)
	{
		if(s[i].val == checkNum)
		{
			flag = true;
			findIndex = i;
			break;
		}
	}
	return flag;
}

void getOutName(const char *inName,char * newName)
{
	strcpy(newName,"");
	int txtLen = strlen(".txt");
	int i=0;
	for(i=0;i<strlen(inName)- txtLen;++i)
	{
		newName[i] = inName[i];
	}
	newName[i] = '\0';
	strcat(newName,"_out.txt");
}

void printHw1(Stats_Number *saved,int len,const char * fileName)
{
	cout<<"start write to file.\n"<<endl;
	char newName[256];
	getOutName(fileName,newName);
	ofstream out(newName);
	if (out.is_open())
	{
		for (int i=0;i<len;++i)
		{
			out<<saved[i].val<<": "<<saved[i].count<<endl;
		}
	}
	else
	{
		cout<<"open "<<newName<<" failed"<<endl;
	}
}

void bubbleOrder(Stats_Number *saved,int len)
{
	cout<<"start make order.\n"<<endl;
	Stats_Number temp;
	for(int i=0;i<len;++i)
	{
		for(int j=i+1;j<len;++j)
		{
			if(saved[j] < saved[i])
			{
				temp = saved[i];
				saved[i] = saved[j];
				saved[j] = temp;
			}
		}
	}
}

void hw1(const char * fileName = "hw1.txt")
{
	cout<<fileName<<endl;

	char buff[256];
	ifstream inf(fileName);
	if(!inf.is_open())
	{
		cout<<"open file error "<<fileName<<endl;
		exit(1);
	}
	Stats_Number saved[HW1_MAX_UNDIFF];
	int lineNum = 0;
	int nowLen = 0;
	int ct = 0;
	int readIn = -1;
	int findIndex = 0;
	while(!inf.eof())
	{
		inf.getline(buff,256);
		readIn = atoi(buff);
		if(ct==0) 
		{
			lineNum = readIn;
		}else
		{
			if(!checkExist(saved,readIn,nowLen,findIndex))
			{
				saved[nowLen].val = readIn;
				++saved[nowLen].count;
				++nowLen;
			}else
			{
				++saved[findIndex].count;
			}
		}
		++ct;
	}

	bubbleOrder(saved,nowLen);
	printHw1(saved,nowLen,fileName);
}

void main(int argc,char *argv[])
{
	//hw1();
	if (argc == 2)
	{
		int len = strlen(argv[1]);
		int txtLen = strlen(".txt");
		char hwIndex = argv[1][len-1-txtLen];
		switch (hwIndex)
		{
		case '1':
			hw1(argv[1]);
			break;
		default:
			break;
		} 
	}

	system("pause");
}