#include<iostream>
#include<cstring>
using namespace std;
long long int line_x[200001];
long long int line_y[200001];//��¼�����ߵ�x��yֵ 
class point
{
	public:
		long long int x ;
		long long int y ;
		point():x(0),y(0){
		}//��ʼ��Ĭ�ϵ������Ϊ(0,0) 
		~point(){
		}
		bool position (long long int line_x ,long long int line_y)  //�жϵ���ֱ�ߵ�λ�ù�ϵ��true��Ϊ�����ϻ����Ҳ࣬false�������ߵ���� 
		{
			//long long int t = line_y * x + line_x * y - line_x * line_y ;
			//long long int m = line_x * y - (line_x-x) * line_y;
			long long int a = line_x;
			long long int b = line_y;
			long long int n = (x-a)*(y-b)-y*x;
			if ( n > 0 )
				return false;
			else
				return true;
		}
		void set (long long int a ,long long int b )//���õ������ 
		{
			x = a;
			y = b;
		}
};

point dot[200001];
int main()
{
	int line_num=0,dot_num=0;
	scanf("%d",&line_num);
	scanf("%d",&dot_num);
	memset(line_x,0,sizeof(line_x));//��ʼ��Ϊ0 
	memset(line_y,0,sizeof(line_y));
	for ( int i = 0 ; i < line_num ; i++ )
	{
		scanf ("%lld",&line_x[i]);
		scanf ("%lld",&line_y[i]);
	}
	for ( int i = 0 ; i < dot_num ; i++ )
	{
		long long int a , b;
		scanf("%lld",&a);
		scanf("%lld",&b);
		dot[i].set(a,b);
	}
	for ( int i = 0 ;  i < dot_num ; i++ )//���ֲ��� 
	{
		int left = 0;
		int right = line_num-1;
		if ( !dot[i].position(line_x[0],line_y[0]) )//���ڵ�һ���������ֱ�����0 
		{
			cout << 0 << endl;
		}
		else if ( dot [ i ].position(line_x[right],line_y[right]))//�������һ�����Ҳ������n 
		{
			cout << right +1 <<endl;
		}
		else
		{
			while ( left <= right )
			{
				int mid = (left+right)>>1 ;
				if ( dot[i].position(line_x[mid+1],line_y[mid+1])) //��mid+1�Ҳ�ʱ����left=mid+1 
				{
					left = mid + 1 ;
				}
				else if ( !dot[i].position(line_x[mid],line_y[mid])) //��mid���ʱ����right=mid 
				{
					right = mid ;
				}
				else if ( dot[i].position(line_x[mid],line_y[mid]) && !dot[i].position(line_x[mid+1],line_y[mid+1])) // ��mid�Ҳ࣬mid+1���ʱ������������ѭ�� 
				{
					cout << mid + 1 << endl;
					break;
				}
			}
		}
	}
	return 0;
}
