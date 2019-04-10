#include<iostream>
using namespace std;

struct node
{
	int offer;
	node* pred;
	node* succ;
	node(int a,node* p = NULL,node*e=NULL):offer(a),pred(p),succ(e){
	}
	node(){
	}
};
class queue
{
	private:
		node header;
		node trailer;
		int _size;
	public:
		queue () : _size(0){
			header.pred = NULL;
			header.succ = &trailer;
			trailer.pred = &header;
			trailer.succ = NULL;
		}
		~queue(){
		}
		node* getfirst()
		{
			return header.succ;
		}
		node* getlast()
		{
			return trailer.pred;
		}
		bool empty()
		{
			if (_size!=0)
				return false;
			else
				return true;
		}
		int getsize()
		{
			return _size;
		}
		void push (node* t)
		{
			trailer.pred->succ = t;
			t->succ = &trailer;
			t->pred = trailer.pred;
			trailer.pred=t;
			_size++;
		}//ÔÚ¶ÓÎ²²åÈë
		void pop ( )
		{
			if ( !empty() )
			{
				int toffer = header.succ->offer;
				header.succ = header.succ->succ;
				header.succ->pred = &header;
				_size--;
			}
		}
};

node of[1000000];
int main()
{
	int num = 0;
	scanf("%d",&num);
	queue stock;
	queue store;
	char tmp[10];
	for ( int i = 0 ; i< num ;i++)
	{
		scanf("%s",&tmp);
		if ( tmp[0] == 'E' )
		{
			scanf("%d",&of[i].offer);
			stock.push(&of[i]);
			node * t = &of[i];
			store.push(t);
			for ( node*x = store.getlast()->pred ; x->pred && x->offer <of[i].offer ; x= x->pred )
			{
				x->offer = of[i].offer;
			}
		}
		if ( tmp[0] == 'D' )
		{
			stock.pop();
			store.pop();
		}
		long long int c = stock.getsize()*store.getfirst()->offer;
		printf("lld",c);
		printf("\n");
	} 
	return 0;
}
