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

struct vnode//������
{
	int num;//���
	int indegree;//���
	int outdegree;//����
	int topo_num;//���������еı�� 
	vnode * pred;
	vnode * succ;
	vnode ( int n ) : num(n) , indegree(0) , outdegree(0),pred(NULL),succ(NULL)//�������Ϊn�Ķ���
	{
	}
	vnode ( ) : num(0) , indegree(0) , outdegree(0) , pred(NULL),succ(NULL)//Ĭ�Ϲ��캯��
	{
	}
};

struct edge//����
{
	vnode* _in;//ͷ����
	vnode* _out;//β����
	int weight;//Ȩ��
	edge* pred;//�����ڽӱ��е�ǰ��
	edge* succ;//�����ڽӱ��еĺ��
	void set ( vnode* a , vnode* b , int t )//���ñߵ�ͷβ�����Ȩ��
	{
		if ( weight > 0 )//������Ȩ�ش���0���ʾ�ñ��Ѵ��ڣ��µ�Ȩ�ظ��������֮
		{
			if ( t > weight)
				weight = t;
		}
		else//�������øñߵĸ������
		{
			weight = t;
			_in = a;
			_out = b;
		}
	}
	edge () : _in(NULL),_out(NULL),weight(0),pred(NULL),succ(NULL){//Ĭ�Ϲ��캯��
	}
};

class list//�ڽӱ���
{
	private:
		edge* header;//ͷ�ڵ�
		edge* trailer;//β�ڵ�
		int _size;//�ڽӱ��ģ
	public:
		list () : _size(0){//Ĭ�Ϲ��캯��
			header = new edge;
			trailer = new edge;
			header->pred = NULL;//ͷ�ڵ�ǰ��Ϊ��
			header->succ = trailer;//ͷ�ڵ���Ϊβ�ڵ�
			trailer->succ = NULL;//β�ڵ���Ϊ��
			trailer->pred = header;//β�ڵ�ǰ��Ϊͷ�ڵ�
		}
		~list()//��������
		{
		}
		edge* getfirst()//�����б��һ���ڵ�
		{
			return header->succ;
		}
		int getsize()//�����б��ģ
		{
			return _size;
		}
		void push( edge * a )//���б�β�����a��������бߣ������ڽӱ� 
		{
			edge* tmp = header->succ;//�Ӷ���Ԫ�ؿ�ʼ����
			bool flag = true;//���ڼ�¼�Ƿ��Ѵ��ڸñ�
			while ( tmp ->succ != NULL )//tmp�����б�������Ԫ��
			{
				if ( tmp->_out == a->_out )//tmpβ������aβ������ͬ�����ñ��Ѵ���
				{
					flag = false;//�ı�flag
					if (tmp->weight < a->weight)
					{
						tmp->weight = a->weight;
					}
					break;
				}
				tmp = tmp->succ;
			}
			if ( flag )//����ͬ��ʱ����
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

class queue//������ 
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


class graph//ͼ��
{
	private:
		int scale;//ͼ�Ĺ�ģ�����������
		vnode * V;//���������
		list * E;//�ڽӱ������
		list * NE;//���ڽӱ������ 
		int * topo;//���������ĵ��˳��
		int * Vin;
	public:
		graph (int n ):scale(n)//�����ģΪn��ͼ
		{
			V = new vnode[n];//����n������
			E = new list[n];//����n���ڽӱ�
			NE = new list[n];//����n�����ڽӱ� 
			topo = new int[n];
			for ( int i = 0 ; i < scale ; i++ )
			{
				V[i].num=i+1;//�����Ŵ�1��ʼ
			}
		}
		graph():scale(0)
		{
		}
		~graph()//��������
		{
			delete topo;
			delete Vin;
		}
		vnode* getnode(int t)//���ر��Ϊt�Ķ���
		{
			return &V[t-1];
		}
		list getlist(int t )//���ر��Ϊt�Ķ�����ڽӱ�
		{
			return E[t-1];
		}
		list getnlist(int t )//���ر��Ϊt�Ķ�������ڽӱ�
		{
			return NE[t-1];
		}
		void toposort()//�������� 
		{
			queue Q;
			int count = 0;//������ĵ�ļ����� 
			for ( int i = 1 ; i <= scale; i++ )
			{
				if ( getnode(i)->indegree == 0)//���Ϊ0����� 
				{
					Q.enqueue (getnode(i));
				}
			}
			while(!Q.empty())//���в���ʱѭ�� 
			{
				topo[count]=Q.getfirst ()->num;//������Ԫ�صı�Ŵ������������� 
				Q.getfirst() ->topo_num = count;//���������б�Ŵ���õ��� 
				edge* tmp = getlist(topo[count]).getfirst();//�������ڽӱ��е�Ԫ�� 
				count++; 
				while ( tmp->succ!=NULL)
				{
					Vin[tmp->_out->num-1] --;//��֮�ڽӵĶ�������-1 
					if ( Vin[tmp->_out->num-1] == 0 )//��ȼ���0����� 
						Q.enqueue (tmp->_out);
					tmp = tmp->succ;
				}
				Q.dequeue ();//��Ԫ�س��� 
			}
		} 
		void print_topo()
		{
			for ( int i = 0; i < scale; i++ )
			{
				cout << topo[i] << endl;
			}
		}
		void copy_in()//�������ڵ��ʼ�����
		{
			Vin = new int [scale];
			for ( int i = 1; i <= scale; i++)
			{
				Vin[i-1]=getnode(i)->indegree ;
			}
		}
		int getmax()//��������۵�ֵ 
		{
			int tmp = 0 ;
			for ( int i = 0 ; i < scale  ;i++ )
			{
				if ( getnode(topo[i])->indegree != 0 )//���������Ϊ0�ĵ�Ϊ�����бȽ�
				{
					tmp = i;
					break;
				}
			}
			int *tmpmax=new int[tmp];//��¼��Щ��������ֵ 
			for ( int i = 0 ; i < tmp ; i++ )
			{
				tmpmax[i]=max_from(i);//��������ĺ��� 
			}
			return max(tmpmax,tmp); 
		}
		int max_from(int t )//�ο����ϣ�https://blog.csdn.net/revivedsun/article/details/51286777 
		{
			int * tmp_from = new int [scale];
			for ( int i = 0 ; i < scale; i++ )
			{
				tmp_from[i]=-1000000000;//������Ŀ���ݴ�С�����ó�ʼֵΪ����ֵ�ܴ�ĸ��� 
			}
			tmp_from[t]=0;//t��t�ĳ�ʼ����Ϊ0�� 
			for ( int i = t ; i < scale ; i++ )
			{
				edge* tmp_edge = getlist(topo[i]).getfirst();//�����������е�i������ڽӱ� 
				while ( tmp_edge->succ!=NULL)//�����Ǹñ�ָ��ĵ�Ϊ���������е�j�� 
				{
					if ( tmp_from[getnode(tmp_edge->_out->num)->topo_num] < tmp_from[i]+tmp_edge->weight )//����j��t�ľ���С��i��t�ľ����i��j�ľ��������֮ 
						tmp_from[getnode(tmp_edge->_out->num)->topo_num] = tmp_from[i]+tmp_edge->weight;
					tmp_edge = tmp_edge->succ;
				}
			}
			return max(tmp_from,scale);//���������������ֵ��������t�������� 
		}
};

int main()
{
	int m = 0 , n = 0 ;
	scanf("%d",&n);
	scanf("%d",&m);
	graph G ( n );//������n�������ͼ
	edge* ed = new edge[m];//����m����
	for ( int i = 0 ; i < m ; i++ )
	{
		int a = 0 , b = 0 , c = 0 ;
		scanf("%d",&a);
		scanf("%d",&b);
		scanf("%d",&c);//����a,b,c 
		ed[i].set(G.getnode(a),G.getnode(b),c);//���õ�i���ߵ�����
		G.getlist(a).push(&ed[i]);//���ñ߼���a�Ŷ�����ڽӱ���
	}
	G.copy_in();//�������Ϊ����������׼�� 
	G.toposort();//�������� 
	cout << G.getmax() << endl;
	return 0;
} 
