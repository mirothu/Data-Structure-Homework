#include<iostream>
#include<cstring>
using namespace std;
#define NINF INT_MIN

int max ( int * a , int n )
{
	int m = a[0] ; 
	for ( int i = 1 ; i < n ; i++ )
	{
		if ( a[i]>a[0] )
			m = a [i];
	}
	return m;
}

struct vnode//顶点类
{
	int num;//编号
	int indegree;//入度
	int outdegree;//出度
	int topo_num;//拓扑序列中的编号 
	vnode * pred;
	vnode * succ;
	vnode ( int n ) : num(n) , indegree(0) , outdegree(0),pred(NULL),succ(NULL)//创建编号为n的顶点
	{
	}
	vnode ( ) : num(0) , indegree(0) , outdegree(0) , pred(NULL),succ(NULL)//默认构造函数
	{
	}
};

struct edge//边类
{
	vnode* _in;//头顶点
	vnode* _out;//尾顶点
	int weight;//权重
	edge* pred;//用于邻接表中的前驱
	edge* succ;//用于邻接表中的后继
	void set ( vnode* a , vnode* b , int t )//设置边的头尾顶点和权重
	{
		if ( weight > 0 )//若已有权重大于0则表示该边已存在，新的权重更大则更新之
		{
			if ( t > weight)
				weight = t;
		}
		else//否则设置该边的各项参数
		{
			weight = t;
			_in = a;
			_out = b;
		}
	}
	edge () : _in(NULL),_out(NULL),weight(0),pred(NULL),succ(NULL){//默认构造函数
	}
};

class list//邻接表类
{
	private:
		edge* header;//头节点
		edge* trailer;//尾节点
		int _size;//邻接表规模
	public:
		list () : _size(0){//默认构造函数
			header = new edge;
			trailer = new edge;
			header->pred = NULL;//头节点前驱为空
			header->succ = trailer;//头节点后继为尾节点
			trailer->succ = NULL;//尾节点后继为空
			trailer->pred = header;//尾节点前驱为头节点
		}
		~list()//析构函数
		{
		}
		edge* getfirst()//返回列表第一个节点
		{
			return header->succ;
		}
		int getsize()//返回列表规模
		{
			return _size;
		}
		void push( edge * a )//从列表尾加入边a或更新已有边，用于邻接表 
		{
			edge* tmp = header->succ;//从队首元素开始操作
			bool flag = true;//用于记录是否已存在该边
			while ( tmp ->succ != NULL )//tmp遍历列表中所有元素
			{
				if ( tmp->_out == a->_out )//tmp尾顶点与a尾顶点相同，即该边已存在
				{
					flag = false;//改变flag
					if (tmp->weight < a->weight)
					{
						tmp->weight = a->weight;
					}
					break;
				}
				tmp = tmp->succ;
			}
			if ( flag )//无相同边时加入
			{		
				trailer->pred->succ = a;
				a->pred = trailer->pred;
				trailer->pred = a;
				a->succ = trailer;
				_size++;
				a->_out->indegree++;
				a->_in->outdegree++;
			}
		}
};

class queue//队列类 
{
	private:
		int scale;
		vnode* header;
		vnode* trailer;
	public:
		queue():scale(0)
		{
			header = new vnode;
			trailer = new vnode;
			header->succ=trailer;
			trailer->pred=header;
			header->pred=NULL;
			trailer->succ=NULL;
		}
		~queue(){}
		void enqueue ( vnode* a)
		{
			trailer->pred->succ = a;
			a->pred = trailer->pred;
			trailer->pred = a;
			a->succ = trailer;
			scale++;
		}
		void dequeue ()
		{
			header->succ = header->succ->succ;
			header->succ->pred = header;
			scale--;
		}
		vnode* getfirst()
		{
			return header->succ;
		}
		bool empty()
		{
			if ( scale != 0 )
				return false;
			else 
				return true;
		}
};


class graph//图类
{
	private:
		int scale;//图的规模，即顶点个数
		vnode * V;//顶点的数组
		list * E;//邻接表的数组
		list * NE;//逆邻接表的数组 
		int * topo;//拓扑排序后的点的顺序
		int * Vin;
	public:
		graph (int n ):scale(n)//构造规模为n的图
		{
			V = new vnode[n];//创建n个顶点
			E = new list[n];//创建n个邻接表
			NE = new list[n];//创建n个逆邻接表 
			topo = new int[n];
			for ( int i = 0 ; i < scale ; i++ )
			{
				V[i].num=i+1;//顶点编号从1开始
			}
		}
		graph():scale(0)
		{
		}
		~graph()//析构函数
		{
			delete topo;
			delete Vin;
		}
		vnode* getnode(int t)//返回编号为t的顶点
		{
			return &V[t-1];
		}
		list getlist(int t )//返回编号为t的顶点的邻接表
		{
			return E[t-1];
		}
		list getnlist(int t )//返回编号为t的顶点的逆邻接表
		{
			return NE[t-1];
		}
		void toposort()//拓扑排序 
		{
			queue Q;
			int count = 0;//已排序的点的计数器 
			for ( int i = 1 ; i <= scale; i++ )
			{
				if ( getnode(i)->indegree == 0)//入度为0则入队 
				{
					Q.enqueue (getnode(i));
				}
			}
			while(!Q.empty())//队列不空时循环 
			{
				topo[count]=Q.getfirst ()->num;//将队首元素的编号存入拓扑序列中 
				Q.getfirst() ->topo_num = count;//将拓扑序列编号存入该点中 
				edge* tmp = getlist(topo[count]).getfirst();//遍历其邻接表中的元素 
				count++; 
				while ( tmp->succ!=NULL)
				{
					Vin[tmp->_out->num-1] --;//与之邻接的顶点的入度-1 
					if ( Vin[tmp->_out->num-1] == 0 )//入度减至0则入队 
						Q.enqueue (tmp->_out);
					tmp = tmp->succ;
				}
				Q.dequeue ();//该元素出队 
			}
		} 
		void print_topo()
		{
			for ( int i = 0; i < scale; i++ )
			{
				cout << topo[i] << endl;
			}
		}
		void copy_in()//拷贝各节点初始的入度
		{
			Vin = new int [scale];
			for ( int i = 1; i <= scale; i++)
			{
				Vin[i-1]=getnode(i)->indegree ;
			}
		}
		int getmax()//返回最大差价的值 
		{
			int tmp = 0 ;
			for ( int i = 0 ; i < scale  ;i++ )
			{
				if ( getnode(topo[i])->indegree != 0 )//以所有入度为0的点为起点进行比较
				{
					tmp = i;
					break;
				}
			}
			int *tmpmax=new int[tmp];//记录这些点的最大差价值 
			for ( int i = 0 ; i < tmp ; i++ )
			{
				tmpmax[i]=max_from(i);//调用下面的函数 
			}
			return max(tmpmax,tmp); 
		}
		int max_from(int t )//参考资料：https://blog.csdn.net/revivedsun/article/details/51286777 
		{
			int * tmp_from = new int [scale];
			for ( int i = 0 ; i < scale; i++ )
			{
				tmp_from[i]=-1000000000;//根据题目数据大小，设置初始值为绝对值很大的负数 
			}
			tmp_from[t]=0;//t到t的初始距离为0； 
			for ( int i = t ; i < scale ; i++ )
			{
				edge* tmp_edge = getlist(topo[i]).getfirst();//遍历拓扑序列第i个点的邻接表 
				while ( tmp_edge->succ!=NULL)//不妨记该边指向的点为拓扑序列中第j个 
				{
					if ( tmp_from[getnode(tmp_edge->_out->num)->topo_num] < tmp_from[i]+tmp_edge->weight )//若点j到t的距离小于i到t的距离加i到j的距离则更新之 
						tmp_from[getnode(tmp_edge->_out->num)->topo_num] = tmp_from[i]+tmp_edge->weight;
					tmp_edge = tmp_edge->succ;
				}
			}
			return max(tmp_from,scale);//返回这个数组的最大值，即到点t的最大距离 
		}
};

int main()
{
	int m = 0 , n = 0 ;
	scanf("%d",&n);
	scanf("%d",&m);
	graph G ( n );//创建有n个顶点的图
	edge* ed = new edge[m];//创建m条边
	for ( int i = 0 ; i < m ; i++ )
	{
		int a = 0 , b = 0 , c = 0 ;
		scanf("%d",&a);
		scanf("%d",&b);
		scanf("%d",&c);//读入a,b,c 
		ed[i].set(G.getnode(a),G.getnode(b),c);//设置第i条边的数据
		G.getlist(a).push(&ed[i]);//将该边加入a号顶点的邻接表中
	}
	G.copy_in();//拷贝入度为拓扑排序做准备 
	G.toposort();//拓扑排序 
	cout << G.getmax() << endl;
	return 0;
} 
