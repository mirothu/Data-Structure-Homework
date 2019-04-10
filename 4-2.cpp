#include<iostream>
using namespace std;

#define Parent(i)((i-1)>>1)
#define LChild(i)(1+((i)<<1))
#define RChild(i)((1+(i))<<1)
#define  LastInternal(n)   Parent( n - 1 ) //���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  ParentValid(i)    ( 0 < i ) //�ж�PQ[i]�Ƿ��и���
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ( ( PQ[i] < PQ[j] ) ? j : i ) //ȡ���ߣ���ʱǰ�����ȣ�
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
             ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
             ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
             ) \
             ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���
             
             
template <class T>
class iVector
{
	protected:
		int _size;//����������� 
		T* _vector;//�洢���ݵ����� 
		int real_size;//ʵ�ʴ����Ԫ�ظ��� 
	public:
		
		iVector( int n  ): _size(n),real_size(0)//����һ���������Ϊn������ 
		{
			_vector = new T [n] ;
		}
		~iVector()//�������� 
		{
			delete [] _vector ;
		}
		bool empty ()const //�ж��Ƿ�Ϊ�� 
		{
			if ( real_size==0 )
				return true;
			else
				return false;
		}
		void push_back(const T&v )//��β�����Ԫ�� 
		{
			if( real_size < _size )
			{
				*(_vector + real_size) = v;
				real_size++;
			}
		}
		T& operator [](int n)//���ز�����[] 
		{
			return _vector [ n ] ;
		}
		void swap (int a , int b )//���������е�a���͵�b��Ԫ�� 
		{
			T tmp = _vector[a];
			_vector[a] = _vector[b];
			_vector[b] = tmp;
		}
		void reset (int a, T b)//����a��Ԫ������Ϊb 
		{
			_vector[a]=b;
		}
		T getmax()//�������ֵ����������0��Ԫ�� 
		{
			return _vector[0];
		}
		void percolateDown(int n ,int i)//�ο�����10-B3����ǰn��Ԫ���еĵ�i��ʵʩ���� 
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
	fread(&n, sizeof(int), 1, stdin);//��ȡn 
	fread(&k, sizeof(int), 1, stdin);//��ȡk 
	iVector<int> vec(k);//����һ�����ռ�Ϊk������ 
	int data = 0;
	int* t_data=new int [k];//��ʱ�洢ǰk��Ԫ�ص����� 
	fread(t_data, sizeof(int), k, stdin);//��ȡǰk��Ԫ�� 
	for ( int i = 0 ; i < k ; i++ )
	{
//		scanf("%d",&t_data[i]);
		vec.push_back(t_data[i]);//���ν�ǰk��Ԫ�ض��������� 
	}
	for ( int i = LastInternal(k);i>=0;i--)//�������ѵĲ��� 
	{
		vec.percolateDown(k,i);//���¶��Ͻ������� 
	}
	delete [] t_data;//�ͷ���ʱ�洢���ݵ����� 
	for ( int i = k ; i < n ; i++ )
	{
//		scanf("%d",&data);
		fread(&data, sizeof(int), 1, stdin);//���ζ�ȡ�������� 
		if ( data < vec.getmax() )//����С�������е����ֵ 
		{
			vec.reset(0,data);//�������һ��Ԫ���޸�Ϊdata 
			vec.percolateDown(k,0);//�����˱��ֶ����� 
		}		
	}
	cout << vec.getmax()<<endl;//������ 
	return 0;
}
