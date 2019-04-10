#include<iostream>
#include<cstring> 
using namespace std;
int A[500001],B[500001],C[500001];//记录每个教练选择的顺序 
struct Player 
{
	int num ;//队员的编号 
	string coach;//ABC所属教练，N代表暂无教练 
};
Player pl [ 500001 ] ;
int main()
{
	int Num=0;//球员总数 
	scanf("%d",&Num);	
	for ( int i = 0 ; i < Num ; i++)//初始化球员pl[i] 读入教练A[i] 
	{
		pl [ i ].num = i + 1 ;
		pl [ i ].coach = "N" ;
		scanf("%d",&A[i]) ;
	}
	for ( int i = 0 ; i < Num ; i++)//读入教练B[i] 
	{
		scanf("%d",&B[i]) ;
	}
	for ( int i = 0 ; i < Num ; i++)//读入教练C[i] 
	{
		scanf("%d",&C[i]) ;
	}
	int select_k = 0 ;
	scanf("%d",&select_k) ;//待求的k号球员 
	int Aset = 0 ;
	int Cset = 0 ;
	int Bset = 0 ;//代表每位教练最喜欢的前n-1名球员已被挑选 
	for ( int i = 0 ; i < Num ; i++) //第i次挑选球员 
	{
		int selected = 0;//记录是否选到了k号球员，1代表是，0代表否 
		if ( i % 3 == 0 )  //A选择球员 
		{
			for ( int j = Aset ; j < Num ; j++ )
			{
				if ( A [ j ] == select_k )//若恰好选到了k号球员，则直接输出并结束循环 
				{
					cout<<"A"<<endl;
					selected = 1;
					pl [ A [ j ] - 1 ].coach = "A";
					break;
				}
				if ( pl [ A [ j ] - 1 ].coach =="N" )//若A[j]号球员未被选择，则将其设置为被A选择并跳出该循环 
				{
					pl [ A [ j ] - 1 ].coach = "A";
					Aset = j;
					break;
				}//其他情况继续循环 
			}
		}
		if ( i % 3 == 1 )  //B选择球员 
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
		if ( i % 3 == 2 )  //C选择球员 
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
		if (selected == 1)//k号球员被选择，跳出循环 
			break;
	}
	return 0; 
}
