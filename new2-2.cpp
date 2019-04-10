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
		node header;//ͷ�ڵ� 
		node trailer;//β�ڵ� 
		long long _size;//���й�ģ 
	public:
		queue():_size(0)//Ĭ�Ϲ��캯�� 
		{
			header.succ=&trailer;
			trailer.pred = &header;
			header.pred=NULL;
			trailer.succ=NULL;
		}
		~queue()//�������� 
		{
		}
		node * getfirst()//�����׽ڵ� 
		{
			return header.succ;
		}
		node * getlast()//����ĩ�ڵ� 
		{
			return trailer.pred;
		}
		void push (  long long a,  long long b ,int n)//��ӣ�n�������ĵ����� 
		{
			node * m=new node( a,b ) ;
			m->num=n;
			m->succ = &trailer;
			m->pred = trailer.pred;
			m->pred->succ = m ;
			trailer.pred = m ;
			_size++;
		}
		node* pop()//�Ӷ��׳��� 
		{
			node* m = header.succ;
			header.succ = header.succ->succ;
			header.succ->pred = &header;
			_size--;
			return m;
		}
		node* popback()//�������һ���ڵ� 
		{
			node* m = trailer.pred;
			trailer.pred=trailer.pred->pred;
			trailer.pred->succ = &trailer;
			_size--;
			return m;
		}
		node* popbacksecond()//���������ڶ����ڵ� 
		{
			node* m = trailer.pred->pred;
			trailer.pred->pred=trailer.pred->pred->pred;
			trailer.pred->pred->succ = trailer.pred;
			_size--;
			return m;
		}
		bool empty()//�ж��Ƿ�Ϊ�ն��� 
		{
			if( _size==0)
				return true;
			else
				return false;
		}
		int getsize()//����_size 
		{
			return _size;
		}
};

bool cmp ( point a, point b)//a��bǰΪtrue 
{
	if ( a.y < b.y || (a.y==b.y&&a.x<b.x))
		return true;
	else
		return false;
}

void quicksort ( point pt[] , int low , int high )//����  �ο�http://www.cnblogs.com/asiacao/archive/2012/12/17/2822090.html
{
	if ( low>=high )//�������ֻ��һ�������Ԫ�ؽ����ݹ� 
		return;
	point standard (pt[low].x,pt[low].y);//ѡ���һ����Ϊ��׼ 
	int i = low;
	for ( int j = low + 1 ; j <= high ; j++ )
	{
		if ( cmp ( pt[j] , standard ))//�Ƚϵ�j�������׼�� 
		{
			i++;
			if ( i != j )
			{
				//������i�͵�j���� 
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
				pt[low].y=tmp1.y;//������׼�����i���� 
	quicksort(pt,low,i-1);//�ݹ� 
	quicksort(pt,i+1,high);//�ݹ� 
}

bool onright_oronline ( point a, point b , point c )//c����ab�ұ߻���ab�ӳ�����Ϊtrue 
{
	long long tmp = a.x*b.y-a.y*b.x+b.x*c.y-b.y*c.x+c.x*a.y-c.y*a.x;//�ұ�С��0��
	if ( tmp < 0 ) 
		return true;
	else if ( tmp==0 && ((b.x-a.x)*(c.x-a.x)>0||(b.y-a.y)*(c.y-a.y)>0)&&(abs(c.x-a.x)>abs(b.x-a.x)||abs(c.y-a.y)>abs(b.x-a.x)))//ac��ab�غ���ac����
		return true;
	else
		return false; 
}

int main()
{
	int n = 0;//��¼��ĸ���
//	cin >> n;
	fread(&n, sizeof(int), 1, stdin);
	point * dot = new point[n];
	queue que; //��¼��͹���ϵĵ�
	for ( int i = 0 ; i < n ; i++ )
	{
		fread(&dot[i].x, sizeof(int), 1, stdin);
		fread(&dot[i].y, sizeof(int), 1, stdin);
//		cin>> dot[i].x>>dot[i].y;
	}
	quicksort(dot,0,n-1);//���� 
	point * unique_dot = new point[n];//��¼ȥ�غ������� 
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
	//���ȥ�أ�֮����unique_dot�н���͹������
	bool visit[unique_j];//��¼ÿ�����Ƿ�����˶��� 
	memset(visit,false,sizeof(bool));
	if ( unique_j <= 2 )
	{
		for ( int i = 0 ; i< unique_j ;i++ )
		{
			que.push(unique_dot[i].x,unique_dot[i].y,i);
			visit[i]=true;
		}
	}//ȥ�غ�����С�ڵ���2ʱֱ�Ӱ�˳�������� 
	else
	{
		for ( int i = 0 ; i< 2 ;i++ )//ǰ������������ 
		{
			que.push(unique_dot[i].x,unique_dot[i].y,i);
			visit[i]=true;
		}
		visit[0]=false;//����¼��һ�����Ƿ������е�ָʾ������Ϊfalse�����ں��������Ƿ񹹳�͹�� 
		for ( int i = 2 ; i < unique_j ; i++ )
		{
			que.push(unique_dot[i].x,unique_dot[i].y,i);//��i���������� 
			visit[i]=true;
			while ( true )
			{
				if ( que.getsize() < 3 )//�����е㲻����������ѭ�� 
					break;
		 		node * tmp= que.getlast();
				point tmpc (tmp->x,tmp->y);
				tmp = tmp->pred;
				point tmpb (tmp->x,tmp->y);
				tmp = tmp->pred;
				point tmpa (tmp->x,tmp->y);
				if(onright_oronline(tmpa,tmpb,tmpc))//�Ƚ϶����������������ߵķ����ϵ�������һ������Ե����ڶ�����ת����ɾ�������ڶ����� 
				{
					visit[que.getlast()->pred->num]=false;
					que.popbacksecond();
				}
				else
					break;//�������ѭ�� 
			}
		}
		bool backfirst = false;//��¼����ѭ��ʱ�Ƿ�����˵�һ���� 
		for ( int i = unique_j - 1 ; i >=0 ; i-- ) 
		{
			if ( !visit[i] && !backfirst )//����ѭ��ʱ�����һ���� 
			{
				que.push(unique_dot[i].x,unique_dot[i].y,i);
				visit[i]=true;
				backfirst = true;
			}
			else if ( !visit[i] )//֮�����ͬ���� 
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
	while ( !que.empty() )//˳����Ӳ���� 
	{
		long long x = que.getfirst()->x;
		long long y = que.getfirst()->y;
		que.pop();
		cout << x <<" " << y << endl;
	}
	return 0;
}
