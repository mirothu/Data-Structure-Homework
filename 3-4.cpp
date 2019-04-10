#include<iostream>
#include<cstring>
using namespace std;

struct binnode
{
	char* name;//���� 
	int data;//������ 
	binnode* father;//ָ�򸸽ڵ� 
	binnode* leftchild;//ָ�����ӵĽڵ� 
	binnode* rightchild;//ָ���Һ��ӵĽڵ� 
	binnode* pred;//���ڽ�����ʱ�Ķ����� 
	binnode* succ;//���ڽ�����ʱ�Ķ����� 
	binnode(char* tmp):father(NULL),leftchild(NULL),rightchild(NULL),data(1),pred(NULL),succ(NULL) //��������Ϊtmp�Ľڵ� 
	{
		name = tmp;
	}
	binnode():father(NULL),leftchild(NULL),rightchild(NULL),data(0),pred(NULL),succ(NULL),name(NULL)//Ĭ�Ϲ��캯�� 
	{
	}
	int size()//����������ģ 
	{
		int _s=1;
		if(!leftchild)
			_s+=leftchild->size();
		if(!rightchild)
			_s+=rightchild->size();
		return _s;
	}
	void insertleft(char* t)//�������� 
	{
		leftchild = new binnode(t);
		leftchild->father = this;
	}
	void insertright(char* t)//�����Һ��� 
	{
		rightchild = new binnode(t);
		rightchild->father = this;
	}
};

struct node//binnode��node�࣬����getmax�б���ʱ�Ķ��� 
{
	binnode* bin;
	node* pred;
	node* succ;
	node(binnode* t ):bin(t),pred(NULL),succ(NULL)
	{
	}
};

class queue//������ 
{
	private:
		int size;//��ģ 
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
		void push(binnode* t)//��β��� 
		{
			node* a=new node(t);
			a->succ = trailer;
			a->pred = trailer->pred;
			a->pred->succ = a;
			trailer->pred = a;
			size++;
		}
		node * getfirst()//���ض���Ԫ�� 
		{
			return header->succ;
		}
		int getsize()//���ض��й�ģ 
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
		void pop()//����Ԫ�س��� 
		{
			if ( !empty( ) )//���в���ʱ 
			{
				header->succ->succ->pred = header;
				header->succ = header->succ->succ;
				size--;
			}
		}
};

class bintree//�������� 
{
	private:
		int _size;
		binnode* root;//���ڵ� 
	public:
		bintree():_size(0),root(NULL){
		}
		~bintree(){
		}
		int getsize()//�������Ĺ�ģ 
		{
			return _size;
		}
		void insertroot(char * t)//��t��Ϊ������ 
		{
			binnode* r = new binnode(t);
			root = r;
			_size++;
		}
		binnode* getroot()//�������� 
		{
			return root;
		}
		void insertaslc (binnode * x , char * t)//��t��Ϊx�����Ӳ��� 
		{
			x->insertleft(t);
			_size++;
		}
		void insertasrc (binnode * x , char* t)//��t��Ϊx���Һ��Ӳ��� 
		{
			x->insertright(t);
			_size++;
		}
		void search ( binnode* m , char * tmp )//�ӽڵ�m��ʼ������Ϊtmp�Ľڵ� 
		{
			binnode* x = m;
			if ( strcmp ( tmp,x->name ) == 0 )//����ƥ�� 
			{
				x->data++;//������++ 
			}
			else if ( strcmp ( tmp , x->name ) < 0 )//tmp<x����������������� 
			{
				if ( x->leftchild == NULL )//���ӿ�������½ڵ� 
					insertaslc(x,tmp);
				else
					search ( x->leftchild , tmp );//����ݹ� 
			}
			else if ( strcmp ( tmp , x->name ) > 0 )//ͬ�� 
			{
				if ( x->rightchild == NULL )
					insertasrc(x,tmp);
				else
					search ( x->rightchild , tmp );
			}
		}
		binnode* getmax ( )//��ȡ���ֵ 
		{
			binnode* maxnode=root;//�Ӹ���ʼ 
			queue Q ;
			Q.push(root);//����������� 
			while ( !Q.empty() )//���в���ʱ��α��� 
			{
				node * tmp1 = Q.getfirst(); 
				if ( tmp1->bin->leftchild != NULL )
					Q.push(tmp1->bin->leftchild);
				if ( tmp1->bin->rightchild != NULL )
					Q.push(tmp1->bin->rightchild); 
				if ( tmp1->bin->data > maxnode->data )
				{
					maxnode = tmp1->bin;
				}//����ǰ�Ƚ��������ֵ 
				Q.pop();
			}
		}
};

int main()
{
	bintree B;
	int n=0;
	scanf("%d",&n);//��������� 
	char * first;//�洢��һ������ 
	scanf("%s",first);
	B.insertroot(first);//������Ϊ���ڵ���� 
	for ( int i = 1 ; i < n ; i++ )
	{
		char * tmp;//�洢��������� 
		scanf("%s",tmp); 
		B.search(B.getroot(),tmp);//���Ҹ����ֲ������������� 
	}
	cout << B.getmax()->name << " " << B.getmax()->data<<endl;//��� 
	return 0;
}
