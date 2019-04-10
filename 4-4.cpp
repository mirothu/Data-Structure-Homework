#include<iostream>
#include<cstring>
using namespace std;

int half ( int a )//返回a的1/2（向上取整） 
{
	if ( a%2 == 0 )
		return a/2;
	else
		return a/2+1;
}

char input[17100000];
char check[34200000];
int main()
{
	setvbuf(stdin,new char[1<<20],_IOFBF,1<<20);
	scanf("%s",&input);
	int size = strlen(input);
	memset(check,'#',sizeof(char)*(2*size+3));//开始预处理字符串 
	check[0]='$';//首尾为了区分设置为不同的字符 
	for ( int i= 0 ; i < strlen(input) ; i++ )
	{
		check[i*2+2]=input[i];//拷贝原字符 
	}
	check[strlen(input)*2+2]='^';
	int nsize = strlen(check);
	long long count = 0 ;//存储回文串总数 
	int C = 0, R = 0 ;//C、R分别存储当前中心字符的位置和最右字符的位置 
	int *S = new int [nsize];//存储每个字符为中心时的回文串最大长度 
	for ( int i = 1 ; i < nsize - 1 ; i++ )//从第一个#开始 
	{
		S[i]=0;
		int i_mir = 2*C - i ;//i_mir存储当前i以C为中心对称的下标 
		if ( R > i )//当前最右字符下标大于i时 
		{
			S[i]=min(R-i,S[i_mir]);//取其对称位置的计数与R-i的最小值 
		}
		else
		{
			S[i]=0;//否则先设置为0 
		}
		while ( check[i+1+S[i]]==check[i-1-S[i]])//此时开始逐一判断其两侧字符直至不相同为止 
		{
			S[i]++;//相同则加1 
		}
		if ( i+S[i]>R )//更新C和R 
		{
			C = i;
			R = i + S[i];
		}
		count += half(S[i]) ;//将最大长度取半并向上取整并加到count上 
	}
	cout << count << endl;//最终输出count即可 
	return 0;
}
