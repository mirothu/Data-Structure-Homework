#include<iostream>
#include<cstring>
using namespace std;
int working[1000000];   //存储已登陆员工编号 
	
struct member
{
	int code=-1;
	bool login=false;
};

member member[10000001];    //记录员工 
int main()
{
	int Num=0; //员工总数n 
	int Times=0; //操作次数m 
	long long int answer = 0;
	scanf("%d",&Num);
	scanf("%d",&Times);	
	int working_t=0; //记录登陆员工数的计数器 
	char A = 0;//记录命令的字符 
	for ( int i = 0 ; i < Times ; i++)
	{
		scanf("%s",&A);
		if ( A == 'I')
		{
			int t = 0;
			scanf("%d",&t);
			scanf("%d",&member[t].code);	//直接读取新code并存储 
			if ( member[t].login == false)
			{
				member[t].login=true;	  //改变登录状态 
				working[working_t]=t;     //记录登陆的员工的编号； 
				working_t++;
			}
		}
		if ( A == 'O')
		{
			int t = 0;
			scanf ("%d",&t);
			if ( member[t].login == true )
			{
				for ( int i = 0 ; i < working_t;i++) //从已登陆员工中删除 
				{
					if (t == working[i])
					{
						working[i]=working[working_t-1];//将最后一个登陆的员工的编号移动至注销的员工的位置，保证后续读取人数方便 
						working[t-1]=0;
						working_t--;
						break;
					}
				}	                 //删除注销的员工的编号；并把最后一个编号挪到该位置 
			}
			member[t].login=false;
			member[t].code=-1;
		}
		if ( A == 'C')
		{
			for ( int i = 0 ; i < working_t;i++)//注销所有已登陆员工 
			{
				member[working[i]].code=-1;
				member[working[i]].login=false;
				working[i]=0;
			}
			working_t=0;
		}
		if ( A == 'N')
		{
			answer += working_t;
		}
		if ( A == 'Q')
		{
			int t =0;
			scanf("%d",&t);
			answer += member[t].code;
		}
	}
	cout << answer << endl;
	return 0;
}
