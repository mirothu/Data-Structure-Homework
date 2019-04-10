#include<iostream>
#include<cstring>
using namespace std;

struct binnode
{
	char* name;//名字 
	int data;//计数器 
	binnode* father;//指向父节点 
	binnode* leftchild;//指向左孩子的节点 
	binnode* rightchild;//指向右孩子的节点 
	binnode* pred;//用于建立树时的队列中 
	binnode* succ;//用于建立树时的队列中 
	binnode(char* tmp):father(NULL),leftchild(NULL),rightchild(NULL),data(1),pred(NULL),succ(NULL) //创建名字为tmp的节点 
	{
		name = tmp;
	}
	binnode():father(NULL),leftchild(NULL),rightchild(NULL),data(0),pred(NULL),succ(NULL),name(NULL)//默认构造函数 
	{
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
	void insertleft(char* t)//插入左孩子 
	{
		leftchild = new binnode(t);
		leftchild->father = this;
	}
	void insertright(char* t)//插入右孩子 
	{
		rightchild = new binnode(t);
		rightchild->father = this;
	}
};

struct node//binnode的node类，用于getmax中遍历时的队列 
{
	binnode* bin;
	node* pred;
	node* succ;
	node(binnode* t ):bin(t),pred(NULL),succ(NULL)
	{
	}
};

class queue//队列类 
{
	private:
		int size;//规模 
		node* header;
		node* trailer;
	public:
		queue():size(0)
		{
			header->succ=trailer;
			trailer->pred = header;
		}
		~queue()
		{
		}
		void push(binnode* t)//队尾入队 
		{
			node* a=new node(t);
			a->succ = trailer;
			a->pred = trailer->pred;
			a->pred->succ = a;
			trailer->pred = a;
			size++;
		}
		node * getfirst()//返回队首元素 
		{
			return header->succ;
		}
		int getsize()//返回队列规模 
		{
			return size;
		}
		bool empty()
		{
			if ( size == 0 )
				return true;
			else
				return false;
		}
		void pop()//队首元素出队 
		{
			if ( !empty( ) )//队列不空时 
			{
				header->succ->succ->pred = header;
				header->succ = header->succ->succ;
				size--;
			}
		}
};

class bintree//二叉树类 
{
	private:
		int _size;
		binnode* root;//根节点 
	public:
		bintree():_size(0),root(NULL){
		}
		~bintree(){
		}
		int getsize()//返回树的规模 
		{
			return _size;
		}
		void insertroot(char * t)//将t作为根插入 
		{
			binnode* r = new binnode(t);
			root = r;
			_size++;
		}
		binnode* getroot()//返回树根 
		{
			return root;
		}
		void insertaslc (binnode * x , char * t)//把t作为x的左孩子插入 
		{
			x->insertleft(t);
			_size++;
		}
		void insertasrc (binnode * x , char* t)//把t作为x的右孩子插入 
		{
			x->insertright(t);
			_size++;
		}
		void search ( binnode* m , char * tmp )//从节点m开始查找名为tmp的节点 
		{
			binnode* x = m;
			if ( strcmp ( tmp,x->name ) == 0 )//名字匹配 
			{
				x->data++;//计数器++ 
			}
			else if ( strcmp ( tmp , x->name ) < 0 )//tmp<x的名字则进入左子树 
			{
				if ( x->leftchild == NULL )//左孩子空则插入新节点 
					insertaslc(x,tmp);
				else
					search ( x->leftchild , tmp );//否则递归 
			}
			else if ( strcmp ( tmp , x->name ) > 0 )//同上 
			{
				if ( x->rightchild == NULL )
					insertasrc(x,tmp);
				else
					search ( x->rightchild , tmp );
			}
		}
		binnode* getmax ( )//获取最大值 
		{
			binnode* maxnode=root;//从根开始 
			queue Q ;
			Q.push(root);//将根加入队列 
			while ( !Q.empty() )//队列不空时层次遍历 
			{
				node * tmp1 = Q.getfirst(); 
				if ( tmp1->bin->leftchild != NULL )
					Q.push(tmp1->bin->leftchild);
				if ( tmp1->bin->rightchild != NULL )
					Q.push(tmp1->bin->rightchild); 
				if ( tmp1->bin->data > maxnode->data )
				{
					maxnode = tmp1->bin;
				}//出队前比较其计数器值 
				Q.pop();
			}
		}
};

int main()
{
	bintree B;
	int n=0;
	scanf("%d",&n);//读入操作数 
	char * first;//存储第一个名字 
	scanf("%s",first);
	B.insertroot(first);//将其作为根节点插入 
	for ( int i = 1 ; i < n ; i++ )
	{
		char * tmp;//存储输入的名字 
		scanf("%s",tmp); 
		B.search(B.getroot(),tmp);//查找该名字并进行其他操作 
	}
	cout << B.getmax()->name << " " << B.getmax()->data<<endl;//输出 
	return 0;
}
