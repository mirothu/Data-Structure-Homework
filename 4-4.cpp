#include<iostream>
#include<cstring>
using namespace std;

int half ( int a )//����a��1/2������ȡ���� 
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
	memset(check,'#',sizeof(char)*(2*size+3));//��ʼԤ�����ַ��� 
	check[0]='$';//��βΪ����������Ϊ��ͬ���ַ� 
	for ( int i= 0 ; i < strlen(input) ; i++ )
	{
		check[i*2+2]=input[i];//����ԭ�ַ� 
	}
	check[strlen(input)*2+2]='^';
	int nsize = strlen(check);
	long long count = 0 ;//�洢���Ĵ����� 
	int C = 0, R = 0 ;//C��R�ֱ�洢��ǰ�����ַ���λ�ú������ַ���λ�� 
	int *S = new int [nsize];//�洢ÿ���ַ�Ϊ����ʱ�Ļ��Ĵ���󳤶� 
	for ( int i = 1 ; i < nsize - 1 ; i++ )//�ӵ�һ��#��ʼ 
	{
		S[i]=0;
		int i_mir = 2*C - i ;//i_mir�洢��ǰi��CΪ���ĶԳƵ��±� 
		if ( R > i )//��ǰ�����ַ��±����iʱ 
		{
			S[i]=min(R-i,S[i_mir]);//ȡ��Գ�λ�õļ�����R-i����Сֵ 
		}
		else
		{
			S[i]=0;//����������Ϊ0 
		}
		while ( check[i+1+S[i]]==check[i-1-S[i]])//��ʱ��ʼ��һ�ж��������ַ�ֱ������ͬΪֹ 
		{
			S[i]++;//��ͬ���1 
		}
		if ( i+S[i]>R )//����C��R 
		{
			C = i;
			R = i + S[i];
		}
		count += half(S[i]) ;//����󳤶�ȡ�벢����ȡ�����ӵ�count�� 
	}
	cout << count << endl;//�������count���� 
	return 0;
}
