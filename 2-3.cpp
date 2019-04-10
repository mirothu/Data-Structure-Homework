#include<iostream>
using namespace std;

struct binnode
{
	int data;
	binnode* father;//ָ�򸸽ڵ� 
	binnode* leftchild;//ָ�����ӵĽڵ� 
	binnode* rightchild;//ָ���Һ��ӵĽڵ� 
	binnode* pred;//���ڽ�����ʱ�Ķ����� 
	binnode* succ;//���ڽ�����ʱ�Ķ����� 
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
	int size()//����������ģ 
	{
		int _s=1;
		if(!leftchild)
			_s+=leftchild->size();
		if(!rightchild)
			_s+=rightchild->size();
		return _s;
	}
	void insertleft(int t)//�������� 
	{
		leftchild = new binnode(t);
		leftchild->father = this;
	}
	void insertright(int t)//�����Һ��� 
	{
		rightchild = new binnode(t);
		rightchild->father = this;
	}
};

int ht ( binnode * pt )//�жϽڵ�pt�ĸ߶�
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
		int updateheight(binnode * x)//����x�ĸ߶� 
		{
			int tmp = 1 + max ( ht ( x->leftchild),ht(x->rightchild) );
			x->height = tmp;
			return tmp;
		}
		void updateheightabove(binnode*x)//����x���ȵĸ߶� 
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
		int getsize()//�������Ĺ�ģ 
		{
			return _size;
		}
		void insertroot(binnode * r)//��r��Ϊ������ 
		{
			root = r;
		}
		binnode* getroot()//�������� 
		{
			return root;
		}
		void insertaslc (binnode * x , int t)//��t��Ϊx�����Ӳ��� 
		{
			x->insertleft(t);
			updateheightabove(x);
			_size++;
		}
		void insertasrc (binnode * x , int t)//��t��Ϊx���Һ��Ӳ��� 
		{
			x->insertright(t);
			updateheightabove(x);
			_size++;
		}
		void fsttravel ( binnode* x )//�������x�������� 
		{
			if( x== NULL )
				return;
			cout << x->data <<" " ;
			fsttravel ( x->leftchild );
			fsttravel ( x->rightchild );
		}
		void lsttravel ( binnode* x )//�������x�������� 
		{
			if( x== NULL )
				return;
			lsttravel ( x->leftchild );
			lsttravel ( x->rightchild );
			cout << x->data << " ";
		} 
		void insertbst ( binnode*x , int t )//���ö����������Ĺ������t
		{
			if ( t < x->data )//tС��x������ 
			{
				if ( x->leftchild == NULL )//����Ϊ������� 
					insertaslc(x,t);
				else//����ݹ� 
					insertbst ( x->leftchild , t );
			}
			if ( t > x->data )//t����x������ 
			{
				if ( x->rightchild == NULL )//�Һ���Ϊ������� 
					insertasrc(x,t);
				else//����ݹ� 
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
	int sign = 0 ;//sign��¼�Ѳ���Ľڵ��� 
	for ( int i = 0 ; i < n; i++ )
	{
		cin >>dta[i];
	}
	binnode first(dta[0]);//�������ڵ� 
	sign++;
	tree.insertroot(&first);//������ڵ� 
	while(sign<n)
	{
		tree.insertbst(tree.getroot(),dta[sign]);
		sign++;
	}//˳��������нڵ� 
	tree.fsttravel(tree.getroot());//������� 
	cout << endl;
	tree.lsttravel(tree.getroot());//������� 
	cout << endl;
	return 0;
}
