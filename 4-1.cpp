#include<iostream>
#include<cstring>
using namespace std;

struct Segnode
{
		int begin;//������˵� 
		int end;//�����Ҷ˵� 
		Segnode* father;//���ڵ� 
		Segnode* lchild;//���� 
		Segnode* rchild;//�Һ��� 
		int count;//������ 
		Segnode ( int b, int e ):begin(b),end(e),father(NULL),lchild(NULL),rchild(NULL),count(0)
		{
		}	
}; 


class Segtree//�߶��� 
{
	private:
		int scale;//��ģ 
		Segnode root;//���ڵ� 
	public:
		Segtree(int n):scale(n),root(Segnode(1,n))
		{
		}
		~Segtree()
		{
		}
		void construct(Segnode* e)//�ڽڵ�e�·������ӽڵ� ,���ɴ˵ݹ����e������ 
		{
			if ( e->begin!=e->end )//e��Ϊ��������Ҳ��e��ΪҶ�ӽڵ�ʱ���ݹ� 
			{
				int tmp_begin = e->begin;//����begin 
				int tmp_end = e->end;//����end 
				int tmp_mid = (tmp_begin+tmp_end)/2;//��midΪ�� 
				Segnode* lc = new Segnode(tmp_begin,tmp_mid);//�������� 
				Segnode* rc = new Segnode(tmp_mid+1,tmp_end);//�����Һ��� 
				lc->father=e;
				rc->father=e;
				e->lchild = lc;
				e->rchild = rc;
				construct(lc);//�ݹ齨�������� 
				construct(rc);//�Լ��Һ��� 
			}
		}
		void change (int i)//����i��״̬ 
		{
			Segnode* tmp = &root;//��ͷ��ʼ����i 
			while ( tmp->lchild !=NULL || tmp->rchild != NULL )//���Ӻ��Һ��Ӳ�ȫΪ��ʱ�������ҵ�Ҷ�ӽڵ�i 
			{
				if ( tmp->lchild->end>=i )//���������յ���ڵ���e��iΪ���ӵĺ�� 
				{
					tmp = tmp->lchild;//��tmp��Ϊ������ 
					if ( tmp->begin == tmp->end )//begin����end�����ΪҶ�ӽڵ�i����ʱֻ����������丸����count 
					{
						if ( tmp->count == 0 ) //Ϊ0��ͳһ++ 
						{
							Segnode* update_tmp=tmp;
							while ( update_tmp->father!=NULL )
							{
								update_tmp->count++;
								update_tmp = update_tmp->father;	
							}
							root.count++;
						}
						else if(tmp->count==1)//Ϊ1��ͳһ-- 
						{
							Segnode* update_tmp=tmp;
							while ( update_tmp->father!=NULL )
							{
								update_tmp->count--;
								update_tmp = update_tmp->father;	
							}
							root.count--;
						}
					}
				}
				else//�������Һ����в��Ҳ����¸�ֵ 
				{
					tmp = tmp->rchild;
					if ( tmp->begin == tmp->end )//begin����end�����ΪҶ�ӽڵ�i����ʱֻ����������丸����count 
					{
						if ( tmp->count == 0 ) //Ϊ0��ͳһ++ 
						{
							Segnode* update_tmp=tmp;
							while ( update_tmp->father!=NULL )
							{
								update_tmp->count++;
								update_tmp = update_tmp->father;	
							}
							root.count++;
						}
						else if(tmp->count==1)//Ϊ1��ͳһ-- 
						{
							Segnode* update_tmp=tmp;
							while ( update_tmp->father!=NULL )
							{
								update_tmp->count--;
								update_tmp = update_tmp->father;	
							}
							root.count--;
						}
					}
				}
			}
		}
		int query (int i , int j)//�ڱ����������ǽ�����[i,j]��Ϊ���ɸ�����ֱ�ӻ�ȡcount�����䣬��������ӵõ���� 
		{
			return (j-i+1)-fuzhu_query(&root,i,j);
		}
		int fuzhu_query(Segnode* tmpnode , int qstart ,int qend )
		{
			if ( qstart > tmpnode->end || qend < tmpnode->begin )//[qstart,qend]������tmpnode���ཻ���򷵻�0
				return 0;
			if ( qstart <= tmpnode->begin && qend >=tmpnode->end )//[qstart,qend]��������tmpnode,����tmpnode��countֵ 
				return tmpnode->count;
			return fuzhu_query(tmpnode->lchild,qstart,qend)+fuzhu_query(tmpnode->rchild,qstart,qend); //�ݹ� 
		}
		Segnode* getroot()
		{
			return &root;
		}
};






int main()
{
	int n=0 , m = 0;
	scanf("%d",&n);
	scanf("%d",&m);
	char tmp [2];
	Segtree seg(n);//������ģΪn���߶��� 
	seg.construct(seg.getroot());//�Ӹ��ڵ㿪ʼ�ݹ鴴�� 
	for ( int i = 0 ; i < m ; i++ )
	{
		scanf("%s",&tmp);
		if ( tmp[0]=='H' )
		{
			int t = 0;
			scanf("%d",&t);
			seg.change(t);//�ı�t��״̬�����������countֵ 
		}
		else if ( tmp[0]=='Q')
		{
			int tmp_i = 0 , tmp_j = 0 ;
			scanf("%d",&tmp_i);
			scanf("%d",&tmp_j);
			cout << seg.query(tmp_i,tmp_j) << endl ;//���ò�ѯ���� 
		}
	}
	return 0;
}
