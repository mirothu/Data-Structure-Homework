#include<iostream>
#include<cstring>
using namespace std;

struct Segnode
{
		int begin;//区间左端点 
		int end;//区间右端点 
		Segnode* father;//父节点 
		Segnode* lchild;//左孩子 
		Segnode* rchild;//右孩子 
		int count;//计数器 
		Segnode ( int b, int e ):begin(b),end(e),father(NULL),lchild(NULL),rchild(NULL),count(0)
		{
		}	
}; 


class Segtree//线段树 
{
	private:
		int scale;//规模 
		Segnode root;//根节点 
	public:
		Segtree(int n):scale(n),root(Segnode(1,n))
		{
		}
		~Segtree()
		{
		}
		void construct(Segnode* e)//在节点e下方创建子节点 ,并由此递归产生e的子树 
		{
			if ( e->begin!=e->end )//e不为单点区间也即e不为叶子节点时，递归 
			{
				int tmp_begin = e->begin;//拷贝begin 
				int tmp_end = e->end;//拷贝end 
				int tmp_mid = (tmp_begin+tmp_end)/2;//以mid为界 
				Segnode* lc = new Segnode(tmp_begin,tmp_mid);//生成左孩子 
				Segnode* rc = new Segnode(tmp_mid+1,tmp_end);//生成右孩子 
				lc->father=e;
				rc->father=e;
				e->lchild = lc;
				e->rchild = rc;
				construct(lc);//递归建立其左孩子 
				construct(rc);//以及右孩子 
			}
		}
		void change (int i)//更改i的状态 
		{
			Segnode* tmp = &root;//从头开始查找i 
			while ( tmp->lchild !=NULL || tmp->rchild != NULL )//左孩子和右孩子不全为空时持续查找到叶子节点i 
			{
				if ( tmp->lchild->end>=i )//左孩子区间终点大于等于e则i为左孩子的后代 
				{
					tmp = tmp->lchild;//将tmp置为其左孩子 
					if ( tmp->begin == tmp->end )//begin等于end代表此为叶子节点i，此时只需更新其与其父辈的count 
					{
						if ( tmp->count == 0 ) //为0则统一++ 
						{
							Segnode* update_tmp=tmp;
							while ( update_tmp->father!=NULL )
							{
								update_tmp->count++;
								update_tmp = update_tmp->father;	
							}
							root.count++;
						}
						else if(tmp->count==1)//为1则统一-- 
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
				else//否则在右孩子中查找并更新各值 
				{
					tmp = tmp->rchild;
					if ( tmp->begin == tmp->end )//begin等于end代表此为叶子节点i，此时只需更新其与其父辈的count 
					{
						if ( tmp->count == 0 ) //为0则统一++ 
						{
							Segnode* update_tmp=tmp;
							while ( update_tmp->father!=NULL )
							{
								update_tmp->count++;
								update_tmp = update_tmp->father;	
							}
							root.count++;
						}
						else if(tmp->count==1)//为1则统一-- 
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
		int query (int i , int j)//在本函数中我们将区间[i,j]分为若干个可以直接获取count的区间，并将其相加得到结果 
		{
			return (j-i+1)-fuzhu_query(&root,i,j);
		}
		int fuzhu_query(Segnode* tmpnode , int qstart ,int qend )
		{
			if ( qstart > tmpnode->end || qend < tmpnode->begin )//[qstart,qend]与区间tmpnode不相交，则返回0
				return 0;
			if ( qstart <= tmpnode->begin && qend >=tmpnode->end )//[qstart,qend]包含区间tmpnode,返回tmpnode的count值 
				return tmpnode->count;
			return fuzhu_query(tmpnode->lchild,qstart,qend)+fuzhu_query(tmpnode->rchild,qstart,qend); //递归 
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
	Segtree seg(n);//创建规模为n的线段树 
	seg.construct(seg.getroot());//从根节点开始递归创建 
	for ( int i = 0 ; i < m ; i++ )
	{
		scanf("%s",&tmp);
		if ( tmp[0]=='H' )
		{
			int t = 0;
			scanf("%d",&t);
			seg.change(t);//改变t的状态，并逐代更新count值 
		}
		else if ( tmp[0]=='Q')
		{
			int tmp_i = 0 , tmp_j = 0 ;
			scanf("%d",&tmp_i);
			scanf("%d",&tmp_j);
			cout << seg.query(tmp_i,tmp_j) << endl ;//调用查询函数 
		}
	}
	return 0;
}
