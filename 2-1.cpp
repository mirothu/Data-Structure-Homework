#include<iostream>
#include<cstring>
using namespace std;

struct node
{
	int data;
	node * succ;
	node * pred;
	node(int m):data(m),succ(NULL),pred(NULL){
	}//初始化data为m的构造函数 
	node():data(0),succ(NULL),pred(NULL){
	}//默认构造函数 
	//默认data为0，读取到栈中的头尾节点也不影响正常进行 
};

class stack
{
	private:
		int size; //记录栈中元素规模 
		int room; //设置栈的大小 
		node trailer;//尾节点，其pred为栈顶元素 
		node header;//头节点，其succ为栈底元素 
	public:
		stack(int t):room(t),size(0)
		{
			trailer.succ=NULL;
			trailer.pred=&header;
			header.pred=NULL;
			header.succ=&trailer;
		}//栈的构造函数 
		~stack(){
		}
		bool empty()//判断栈是否为空 
		{
			if ( size == 0)
				return true;
			else
				return false;
		}
		void push ( int m )//从顶端加入元素 
		{
			node * p = new node (m);
			if(room>size)
			{
				p->pred = trailer.pred;
				trailer.pred = p;
				size++;
			}
		}
		int pop()//弹出栈顶元素 
		{
			int tmp = trailer.pred->data;
			trailer.pred->pred->succ = trailer.pred;
			trailer.pred=trailer.pred->pred;
			delete trailer.pred->succ;
			trailer.pred->succ = NULL;
			size--;
			return tmp;
		}
		int gettop()//返回栈顶元素 
		{
			return trailer.pred->data;
		}
		int getsize()//返回栈中元素个数 
		{
			return size;
		}
		void push_back ( int m )//从栈底添加元素（仅用于初始化A栈中的数据） 
		{
			node *p = new node ( m );
			p->pred = &header;
			header.succ->pred = p;
			header.succ = p;
			size++;
		}
		bool full()//判断栈是否已满 
		{
			if ( size == room )
				return true;
			else
				return false;
		}
};
int in [ 200001 ];//操作的元素的编号 
char action [ 200001 ];
int main()
{
	int m=0,n=0;
	memset(action,'\0',sizeof(action));
	memset(in,0,sizeof(in));
	scanf("%d",&n);
	scanf("%d",&m);
	stack A(n);
	stack B(n);
	stack S(m);
	for ( int i = 0 ; i < n ; i++ )
	{
		scanf("%d",&in[i]);
		A.push_back(in[i]);
	}
	int sign=1; //记录下一个应当进入B栈的元素 
	int action_i=0; //记录当前已操作次数
	bool done = true;//判断是否完成栈混洗
	while ( !A.empty() || !S.empty() )
	{
		int tmpA = A.gettop();
		int tmpS = S.gettop();
		if ( tmpA == sign ) //A栈顶等于sign，直接pop并push进B栈 
		{
			B.push(A.pop());
			in[action_i]=tmpA;
			action[action_i]='P';
			action_i++;
			sign++;
		}
		else if ( tmpS == sign ) //S栈顶等于sign，pop并push进B栈 
		{
			B.push(S.pop());
			in[action_i]=tmpS;
			action[action_i]='O';
			action_i++;
			sign++;
		}
		else if ( tmpA != sign && tmpS != sign && !S.full() && !A.empty() ) //A不空，A、S栈顶均不为sign且S不满，pop A栈顶元素并push入S栈 
		{
			S.push(A.pop());
			in[action_i]=tmpA;
			action[action_i]='I';
			action_i++;
		}
		else /*if( tmpA != sign && tmpS != sign && S.full() ) //A、S栈顶元素均不满足出栈条件且S满，输出no 
		{
			cout << "No" << endl;
			done = false;
			break;
		}
		else if ( A.empty() && tmpS != sign ) //A空且S栈顶不为sign，输出no */
		{
			cout << "No" << endl;
			done = false;
			break;
		}
	}
	if ( done )//完成栈混洗则输出结果 
	{
		for ( int i = 0 ; i < action_i ; i++ )
		{
			 printf("%d",in[i] );
			 printf(" ");
			 printf("%c",action[i]);
			 printf("\n");
		}
	}
	return 0;
}
