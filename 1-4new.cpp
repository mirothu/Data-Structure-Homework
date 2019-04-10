#include<iostream>
#include<cstring>
using namespace std;
long long int line_x[200001];
long long int line_y[200001];//记录红外线的x、y值 
class point
{
	public:
		long long int x ;
		long long int y ;
		point():x(0),y(0){
		}//初始化默认点的坐标为(0,0) 
		~point(){
		}
		bool position (long long int line_x ,long long int line_y)  //判断点与直线的位置关系，true即为在线上或在右侧，false代表在线的左侧 
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
		void set (long long int a ,long long int b )//设置点的坐标 
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
	memset(line_x,0,sizeof(line_x));//初始化为0 
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
	for ( int i = 0 ;  i < dot_num ; i++ )//二分查找 
	{
		int left = 0;
		int right = line_num-1;
		if ( !dot[i].position(line_x[0],line_y[0]) )//若在第一条线左侧则直接输出0 
		{
			cout << 0 << endl;
		}
		else if ( dot [ i ].position(line_x[right],line_y[right]))//若在最后一条线右侧则输出n 
		{
			cout << right +1 <<endl;
		}
		else
		{
			while ( left <= right )
			{
				int mid = (left+right)>>1 ;
				if ( dot[i].position(line_x[mid+1],line_y[mid+1])) //在mid+1右侧时，让left=mid+1 
				{
					left = mid + 1 ;
				}
				else if ( !dot[i].position(line_x[mid],line_y[mid])) //在mid左侧时，让right=mid 
				{
					right = mid ;
				}
				else if ( dot[i].position(line_x[mid],line_y[mid]) && !dot[i].position(line_x[mid+1],line_y[mid+1])) // 在mid右侧，mid+1左侧时输出结果并跳出循环 
				{
					cout << mid + 1 << endl;
					break;
				}
			}
		}
	}
	return 0;
}
