#include<iostream>
using namespace std;

struct binnode
{
	int data;
	binnode* father;//指向父节点 
	binnode* leftchild;//指向左孩子的节点 
	binnode* rightchild;//指向右孩子的节点 
	binnode* pred;//用于建立树时的队列中 
	binnode* succ;//用于建立树时的队列中 
	binnode(int t):father(NULL),leftchild(NULL),rightchild(NULL),data(t),height(0),pred(NULL),succ(NULL) 
	{
	}
	binnode():father(NULL),leftchild(NULL),rightchild(NULL),height(-1),data(0),pred(NULL),succ(NULL)
	{
	}
	int height;
	void inputdata ( int t )
	{
		data = t;
		height++;
	}
	int size()//返回子树规模 
	{
		int _s=1;
		if(!leftchild)
			_s+=leftchild->size();
		if(!rightchild)
			_s+=rightchild->size();
		return _s;
	}
	void insertleft(int t)//插入左孩子 
	{
		leftchild = new binnode(t);
		leftchild->father = this;
	}
	void insertright(int t)//插入右孩子 
	{
		rightchild = new binnode(t);
		rightchild->father = this;
	}
};

int ht ( binnode * pt )//判断节点pt的高度
{
	if ( pt!=NULL )
		return pt->height;
	else if ( pt == NULL )
		return -1;
}

class bintree
{
	private:
		int _size;
		binnode* root;
		int updateheight(binnode * x)//更新x的高度 
		{
			int tmp = 1 + max ( ht ( x->leftchild),ht(x->rightchild) );
			x->height = tmp;
			return tmp;
		}
		void updateheightabove(binnode*x)//更新x祖先的高度 
		{
			while ( x )
			{
				updateheight ( x );
				x=x->father;
			}
		}
	public:
		bintree():_size(0),root(NULL){
		}
		~bintree(){
		}
		int getsize()//返回树的规模 
		{
			return _size;
		}
		void insertroot(binnode * r)//将r作为根插入 
		{
			root = r;
		}
		binnode* getroot()//返回树根 
		{
			return root;
		}
		void insertaslc (binnode * x , int t)//把t作为x的左孩子插入 
		{
			x->insertleft(t);
			updateheightabove(x);
			_size++;
		}
		void insertasrc (binnode * x , int t)//把t作为x的右孩子插入 
		{
			x->insertright(t);
			updateheightabove(x);
			_size++;
		}
		void fsttravel ( binnode* x )//先序遍历x及其子树 
		{
			if( x== NULL )
				return;
			cout << x->data <<" " ;
			fsttravel ( x->leftchild );
			fsttravel ( x->rightchild );
		}
		void lsttravel ( binnode* x )//后序遍历x及其子树 
		{
			if( x== NULL )
				return;
			lsttravel ( x->leftchild );
			lsttravel ( x->rightchild );
			cout << x->data << " ";
		} 
		void insertbst ( binnode*x , int t )//采用二叉搜索树的规则插入t
		{
			if ( t < x->data )//t小于x的数据 
			{
				if ( x->leftchild == NULL )//左孩子为空则插入 
					insertaslc(x,t);
				else//否则递归 
					insertbst ( x->leftchild , t );
			}
			if ( t > x->data )//t大于x的数据 
			{
				if ( x->rightchild == NULL )//右孩子为空则插入 
					insertasrc(x,t);
				else//否则递归 
					insertbst ( x->rightchild , t );
			} 
		}
};

int main()
{
	int n = 0;
	cin >> n;
	bintree tree;
	int * dta = new int [n];
	int sign = 0 ;//sign记录已插入的节点数 
	for ( int i = 0 ; i < n; i++ )
	{
		cin >>dta[i];
	}
	binnode first(dta[0]);//创建根节点 
	sign++;
	tree.insertroot(&first);//插入根节点 
	while(sign<n)
	{
		tree.insertbst(tree.getroot(),dta[sign]);
		sign++;
	}//顺序插入所有节点 
	tree.fsttravel(tree.getroot());//先序遍历 
	cout << endl;
	tree.lsttravel(tree.getroot());//后序遍历 
	cout << endl;
	return 0;
}
