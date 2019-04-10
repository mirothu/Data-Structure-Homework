#include<iostream>
using namespace std;

struct node
{
	int id;
	node* pred;
	node* succ;
	node(int a,node* p = NULL,node*e=NULL):id(a),pred(p),succ(e){
	}
	node(){
	}
};//������Ҫ�ο��˵���ʦ���������������� 

class list
{
	private:
		node header;
		int _size;
	public:
		list () : _size(0){
			header.pred = NULL;
			header.succ = NULL;
		}
		~list(){
		}
		node* getfirst()
		{
			return header.succ;
		}
		int getsize()
		{
			return _size;
		}
		void addfirst(node* t)
		{
			header.succ = t;
			t->succ = t;
			t->pred = t;
			_size++;
		}
		void addnext(node* t, node *e)//�ڽڵ�e֮�����ڵ�t 
		{
			t->pred = e;
			t->succ = e->succ;
			e->succ->pred = t;
			e->succ = t;
			_size++;
		}
		
};
//����ʱ����Ӽ�Ϊÿ��ȡ��̣�˳ʱ������Ϊÿ��ȡǰ�� 

node inter[1000001];
int main()
{
	list interviewee;
	int num = 0;
	int gap = 0;
	cin >> num >> gap;
	node* p = &inter[0]; //��¼���һ������������߽ڵ� 
	for ( int i = 0 ; i < num ; i++ )
	{
		cin >> inter[i].id;
		if ( i == 0 )
			interviewee.addfirst(&inter[i]);
		else
		{
			int tmp = gap - 1;
			while( tmp != 0 )
			{
				p = p->succ ;
				tmp--;
			}
			interviewee.addnext(&inter[i],p);
			p = &inter[i];
		}
	}
	for ( int i = 0 ; i < num ; i++ )
	{
		if ( i != num - 1)
			cout << p->id <<" " ;
		else
			cout << p->id;
		p = p->pred;
	} 
	return 0;
}
