#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
using namespace std;

struct point
{
	 long long x;
	 long long y;
	point (  long long a,  long long b):x(a),y(b){
	}
	point(){
	}
};

struct node
{
	long long x;
	long long y;
	int num;
	node * pred;
	node * succ;
	node ( long long a ,  long long b ):x(a),y(b),pred(NULL),succ(NULL),num(-1){
	}
	node ():x(0),y(0),pred(NULL),succ(NULL),num(-1){
	}
};

class queue
{
	private:
		node header;//头节点 
		node trailer;//尾节点 
		long long _size;//队列规模 
	public:
		queue():_size(0)//默认构造函数 
		{
			header.succ=&trailer;
			trailer.pred = &header;
			header.pred=NULL;
			trailer.succ=NULL;
		}
		~queue()//析构函数 
		{
		}
		node * getfirst()//返回首节点 
		{
			return header.succ;
		}
		node * getlast()//返回末节点 
		{
			return trailer.pred;
		}
		void push (  long long a,  long long b ,int n)//入队，n代表加入的点的序号 
		{
			node * m=new node( a,b ) ;
			m->num=n;
			m->succ = &trailer;
			m->pred = trailer.pred;
			m->pred->succ = m ;
			trailer.pred = m ;
			_size++;
		}
		node* pop()//从队首出队 
		{
			node* m = header.succ;
			header.succ = header.succ->succ;
			header.succ->pred = &header;
			_size--;
			return m;
		}
		node* popback()//弹出最后一个节点 
		{
			node* m = trailer.pred;
			trailer.pred=trailer.pred->pred;
			trailer.pred->succ = &trailer;
			_size--;
			return m;
		}
		node* popbacksecond()//弹出倒数第二个节点 
		{
			node* m = trailer.pred->pred;
			trailer.pred->pred=trailer.pred->pred->pred;
			trailer.pred->pred->succ = trailer.pred;
			_size--;
			return m;
		}
		bool empty()//判断是否为空队列 
		{
			if( _size==0)
				return true;
			else
				return false;
		}
		int getsize()//返回_size 
		{
			return _size;
		}
};

bool cmp ( point a, point b)//a在b前为true 
{
	if ( a.y < b.y || (a.y==b.y&&a.x<b.x))
		return true;
	else
		return false;
}

void quicksort ( point pt[] , int low , int high )//快排  参考http://www.cnblogs.com/asiacao/archive/2012/12/17/2822090.html
{
	if ( low>=high )//这组点中只有一个或零个元素结束递归 
		return;
	point standard (pt[low].x,pt[low].y);//选择第一个点为基准 
	int i = low;
	for ( int j = low + 1 ; j <= high ; j++ )
	{
		if ( cmp ( pt[j] , standard ))//比较第j个点与基准点 
		{
			i++;
			if ( i != j )
			{
				//交换第i和第j个点 
				point tmp1 (pt[i].x,pt[i].y);
				pt[i].x=pt[j].x;
				pt[i].y=pt[j].y;
				pt[j].x=tmp1.x;
				pt[j].y=tmp1.y;
			}
		}
	}
	point tmp1 (pt[i].x,pt[i].y);
				pt[i].x=pt[low].x;
				pt[i].y=pt[low].y;
				pt[low].x=tmp1.x;
				pt[low].y=tmp1.y;//交换基准点与第i个点 
	quicksort(pt,low,i-1);//递归 
	quicksort(pt,i+1,high);//递归 
}

bool onright_oronline ( point a, point b , point c )//c点在ab右边或在ab延长线上为true 
{
	long long tmp = a.x*b.y-a.y*b.x+b.x*c.y-b.y*c.x+c.x*a.y-c.y*a.x;//右边小于0；
	if ( tmp < 0 ) 
		return true;
	else if ( tmp==0 && ((b.x-a.x)*(c.x-a.x)>0||(b.y-a.y)*(c.y-a.y)>0)&&(abs(c.x-a.x)>abs(b.x-a.x)||abs(c.y-a.y)>abs(b.x-a.x)))//ac与ab重合且ac更长
		return true;
	else
		return false; 
}

int main()
{
	int n = 0;//记录点的个数
//	cin >> n;
	fread(&n, sizeof(int), 1, stdin);
	point * dot = new point[n];
	queue que; //记录在凸包上的点
	for ( int i = 0 ; i < n ; i++ )
	{
		fread(&dot[i].x, sizeof(int), 1, stdin);
		fread(&dot[i].y, sizeof(int), 1, stdin);
//		cin>> dot[i].x>>dot[i].y;
	}
	quicksort(dot,0,n-1);//排序 
	point * unique_dot = new point[n];//记录去重后的有序点 
	int unique_j = 0;
	
	for ( int i = 0 ; i < n - 1 ; i++ )
	{
		if  ( dot[i].x != dot[i+1].x || dot[i].y!=dot[i+1].y )
		{
			unique_dot[unique_j].x=dot[i].x;
			unique_dot[unique_j].y=dot[i].y;
			unique_j++;
		}
		else if ( n>2&&i == n-2 && (dot[i].x != dot[i-1].x || dot[i].y!=dot[i-1].y))
		{
			unique_dot[unique_j].x=dot[i].x;
			unique_dot[unique_j].y=dot[i].y;
			unique_j++;
		}
	}
	if ( n >= 2 && (dot[n-2].x!=dot[n-1].x||dot[n-2].y!=dot[n-1].y))
	{
		unique_dot[unique_j].x=dot[n-1].x;
		unique_dot[unique_j].y=dot[n-1].y;
		unique_j++;
	}
	if ( dot[0].x==dot[n-1].x&&dot[0].y==dot[n-1].y )
	{
		unique_dot[unique_j].x=dot[0].x;
		unique_dot[unique_j].y=dot[0].y;
		unique_j++;
	}
	//完成去重，之后在unique_dot中进行凸包运算
	bool visit[unique_j];//记录每个点是否进入了队列 
	memset(visit,false,sizeof(bool));
	if ( unique_j <= 2 )
	{
		for ( int i = 0 ; i< unique_j ;i++ )
		{
			que.push(unique_dot[i].x,unique_dot[i].y,i);
			visit[i]=true;
		}
	}//去重后点个数小于等于2时直接按顺序进入队列 
	else
	{
		for ( int i = 0 ; i< 2 ;i++ )//前两个点进入队列 
		{
			que.push(unique_dot[i].x,unique_dot[i].y,i);
			visit[i]=true;
		}
		visit[0]=false;//将记录第一个点是否进入队列的指示器重置为false，便于后续检验是否构成凸包 
		for ( int i = 2 ; i < unique_j ; i++ )
		{
			que.push(unique_dot[i].x,unique_dot[i].y,i);//第i个点进入队列 
			visit[i]=true;
			while ( true )
			{
				if ( que.getsize() < 3 )//队列中点不足三个结束循环 
					break;
		 		node * tmp= que.getlast();
				point tmpc (tmp->x,tmp->y);
				tmp = tmp->pred;
				point tmpb (tmp->x,tmp->y);
				tmp = tmp->pred;
				point tmpa (tmp->x,tmp->y);
				if(onright_oronline(tmpa,tmpb,tmpc))//比较队列中最后两条有向边的方向关系，若最后一条边相对倒数第二条右转，则删除倒数第二个点 
				{
					visit[que.getlast()->pred->num]=false;
					que.popbacksecond();
				}
				else
					break;//否则结束循环 
			}
		}
		bool backfirst = false;//记录反向循环时是否加入了第一个点 
		for ( int i = unique_j - 1 ; i >=0 ; i-- ) 
		{
			if ( !visit[i] && !backfirst )//反向循环时加入第一个点 
			{
				que.push(unique_dot[i].x,unique_dot[i].y,i);
				visit[i]=true;
				backfirst = true;
			}
			else if ( !visit[i] )//之后操作同正向 
			{
				que.push(unique_dot[i].x,unique_dot[i].y,i);
				visit[i]=true;
				while ( true )
				{
					if ( que.getsize() < 3)
						break;
		 			node * tmp= que.getlast();
					point tmpc (tmp->x,tmp->y);
					tmp = tmp->pred;
					point tmpb (tmp->x,tmp->y);
					tmp = tmp->pred;
					point tmpa (tmp->x,tmp->y);
					if(onright_oronline(tmpa,tmpb,tmpc))
					{
						visit[que.getlast()->pred->num]=false;
						que.popbacksecond();
					}
					else
						break;
				}
			}
		}
		que.popback();
	}
	while ( !que.empty() )//顺序出队并输出 
	{
		long long x = que.getfirst()->x;
		long long y = que.getfirst()->y;
		que.pop();
		cout << x <<" " << y << endl;
	}
	return 0;
}
