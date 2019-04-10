#include<iostream>
using namespace std;

#define Parent(i)((i-1)>>1)
#define LChild(i)(1+((i)<<1))
#define RChild(i)((1+(i))<<1)
#define  LastInternal(n)   Parent( n - 1 ) //最后一个内部节点（即末节点的父亲）
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  ParentValid(i)    ( 0 < i ) //判断PQ[i]是否有父亲
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( ( PQ[i] < PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
             ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
             ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
             ) \
             ) //相等时父节点优先，如此可避免不必要的交换
             
             
template <class T>
class iVector
{
	protected:
		int _size;//向量最大容量 
		T* _vector;//存储数据的数组 
		int real_size;//实际存入的元素个数 
	public:
		
		iVector( int n  ): _size(n),real_size(0)//构造一个最大容量为n的向量 
		{
			_vector = new T [n] ;
		}
		~iVector()//析构函数 
		{
			delete [] _vector ;
		}
		bool empty ()const //判断是否为空 
		{
			if ( real_size==0 )
				return true;
			else
				return false;
		}
		void push_back(const T&v )//从尾部添加元素 
		{
			if( real_size < _size )
			{
				*(_vector + real_size) = v;
				real_size++;
			}
		}
		T& operator [](int n)//重载操作符[] 
		{
			return _vector [ n ] ;
		}
		void swap (int a , int b )//交换向量中第a个和第b个元素 
		{
			T tmp = _vector[a];
			_vector[a] = _vector[b];
			_vector[b] = tmp;
		}
		void reset (int a, T b)//将第a个元素重置为b 
		{
			_vector[a]=b;
		}
		T getmax()//返回最大值，即向量第0个元素 
		{
			return _vector[0];
		}
		void percolateDown(int n ,int i)//参考讲义10-B3，对前n个元素中的第i个实施下滤 
		{
			int j;
			while ( i!= (j=ProperParent(_vector,n,i)))
			{
				swap(i,j);
				i=j;
			}
		}
};





int main()
{
	int n = 0 , k = 0 ;
/*	scanf("%d",&n);
	scanf("%d",&k);
*/
	fread(&n, sizeof(int), 1, stdin);//读取n 
	fread(&k, sizeof(int), 1, stdin);//读取k 
	iVector<int> vec(k);//创建一个最大空间为k的向量 
	int data = 0;
	int* t_data=new int [k];//临时存储前k个元素的数组 
	fread(t_data, sizeof(int), k, stdin);//读取前k个元素 
	for ( int i = 0 ; i < k ; i++ )
	{
//		scanf("%d",&t_data[i]);
		vec.push_back(t_data[i]);//依次将前k个元素读入向量中 
	}
	for ( int i = LastInternal(k);i>=0;i--)//批量建堆的操作 
	{
		vec.percolateDown(k,i);//自下而上进行下滤 
	}
	delete [] t_data;//释放临时存储数据的数组 
	for ( int i = k ; i < n ; i++ )
	{
//		scanf("%d",&data);
		fread(&data, sizeof(int), 1, stdin);//依次读取其余数据 
		if ( data < vec.getmax() )//若其小于向量中的最大值 
		{
			vec.reset(0,data);//则将数组第一个元素修改为data 
			vec.percolateDown(k,0);//并下滤保持堆序性 
		}		
	}
	cout << vec.getmax()<<endl;//输出结果 
	return 0;
}
