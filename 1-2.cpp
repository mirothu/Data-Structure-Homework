#include<iostream>
#include<cstring>
using namespace std;
int working[1000000];   //�洢�ѵ�½Ա����� 
	
struct member
{
	int code=-1;
	bool login=false;
};

member member[10000001];    //��¼Ա�� 
int main()
{
	int Num=0; //Ա������n 
	int Times=0; //��������m 
	long long int answer = 0;
	scanf("%d",&Num);
	scanf("%d",&Times);	
	int working_t=0; //��¼��½Ա�����ļ����� 
	char A = 0;//��¼������ַ� 
	for ( int i = 0 ; i < Times ; i++)
	{
		scanf("%s",&A);
		if ( A == 'I')
		{
			int t = 0;
			scanf("%d",&t);
			scanf("%d",&member[t].code);	//ֱ�Ӷ�ȡ��code���洢 
			if ( member[t].login == false)
			{
				member[t].login=true;	  //�ı��¼״̬ 
				working[working_t]=t;     //��¼��½��Ա���ı�ţ� 
				working_t++;
			}
		}
		if ( A == 'O')
		{
			int t = 0;
			scanf ("%d",&t);
			if ( member[t].login == true )
			{
				for ( int i = 0 ; i < working_t;i++) //���ѵ�½Ա����ɾ�� 
				{
					if (t == working[i])
					{
						working[i]=working[working_t-1];//�����һ����½��Ա���ı���ƶ���ע����Ա����λ�ã���֤������ȡ�������� 
						working[t-1]=0;
						working_t--;
						break;
					}
				}	                 //ɾ��ע����Ա���ı�ţ��������һ�����Ų����λ�� 
			}
			member[t].login=false;
			member[t].code=-1;
		}
		if ( A == 'C')
		{
			for ( int i = 0 ; i < working_t;i++)//ע�������ѵ�½Ա�� 
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
