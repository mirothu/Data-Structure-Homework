#include<iostream>
#include<cstring> 
using namespace std;
int A[500001],B[500001],C[500001];//��¼ÿ������ѡ���˳�� 
struct Player 
{
	int num ;//��Ա�ı�� 
	string coach;//ABC����������N�������޽��� 
};
Player pl [ 500001 ] ;
int main()
{
	int Num=0;//��Ա���� 
	scanf("%d",&Num);	
	for ( int i = 0 ; i < Num ; i++)//��ʼ����Աpl[i] �������A[i] 
	{
		pl [ i ].num = i + 1 ;
		pl [ i ].coach = "N" ;
		scanf("%d",&A[i]) ;
	}
	for ( int i = 0 ; i < Num ; i++)//�������B[i] 
	{
		scanf("%d",&B[i]) ;
	}
	for ( int i = 0 ; i < Num ; i++)//�������C[i] 
	{
		scanf("%d",&C[i]) ;
	}
	int select_k = 0 ;
	scanf("%d",&select_k) ;//�����k����Ա 
	int Aset = 0 ;
	int Cset = 0 ;
	int Bset = 0 ;//����ÿλ������ϲ����ǰn-1����Ա�ѱ���ѡ 
	for ( int i = 0 ; i < Num ; i++) //��i����ѡ��Ա 
	{
		int selected = 0;//��¼�Ƿ�ѡ����k����Ա��1�����ǣ�0����� 
		if ( i % 3 == 0 )  //Aѡ����Ա 
		{
			for ( int j = Aset ; j < Num ; j++ )
			{
				if ( A [ j ] == select_k )//��ǡ��ѡ����k����Ա����ֱ�����������ѭ�� 
				{
					cout<<"A"<<endl;
					selected = 1;
					pl [ A [ j ] - 1 ].coach = "A";
					break;
				}
				if ( pl [ A [ j ] - 1 ].coach =="N" )//��A[j]����Աδ��ѡ����������Ϊ��Aѡ��������ѭ�� 
				{
					pl [ A [ j ] - 1 ].coach = "A";
					Aset = j;
					break;
				}//�����������ѭ�� 
			}
		}
		if ( i % 3 == 1 )  //Bѡ����Ա 
		{
			for ( int j = Bset ; j < Num ; j++ )
			{
				if ( B [ j ] == select_k )
				{
					cout<<"B"<<endl;
					selected = 1;
					break;
				}
				if ( pl [ B [ j ] - 1 ].coach =="N" )
				{
					pl [ B [ j ] - 1 ].coach = "B";
					Bset = j;
					break;
				}
			}
		}
		if ( i % 3 == 2 )  //Cѡ����Ա 
		{
			for ( int j = Cset ; j < Num ; j++ )
			{
				if ( C [ j ] == select_k )
				{
					cout<<"C"<<endl;
					selected = 1;
					break;
				}
				if ( pl [ C [ j ] - 1 ].coach =="N" )
				{
					pl [ C [ j ] - 1 ].coach = "C";
					Cset = j;
					break;
				}
			}
		}
		if (selected == 1)//k����Ա��ѡ������ѭ�� 
			break;
	}
	return 0; 
}
