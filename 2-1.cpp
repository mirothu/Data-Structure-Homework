#include<iostream>
#include<cstring>
using namespace std;

struct node
{
	int data;
	node * succ;
	node * pred;
	node(int m):data(m),succ(NULL),pred(NULL){
	}//��ʼ��dataΪm�Ĺ��캯�� 
	node():data(0),succ(NULL),pred(NULL){
	}//Ĭ�Ϲ��캯�� 
	//Ĭ��dataΪ0����ȡ��ջ�е�ͷβ�ڵ�Ҳ��Ӱ���������� 
};

class stack
{
	private:
		int size; //��¼ջ��Ԫ�ع�ģ 
		int room; //����ջ�Ĵ�С 
		node trailer;//β�ڵ㣬��predΪջ��Ԫ�� 
		node header;//ͷ�ڵ㣬��succΪջ��Ԫ�� 
	public:
		stack(int t):room(t),size(0)
		{
			trailer.succ=NULL;
			trailer.pred=&header;
			header.pred=NULL;
			header.succ=&trailer;
		}//ջ�Ĺ��캯�� 
		~stack(){
		}
		bool empty()//�ж�ջ�Ƿ�Ϊ�� 
		{
			if ( size == 0)
				return true;
			else
				return false;
		}
		void push ( int m )//�Ӷ��˼���Ԫ�� 
		{
			node * p = new node (m);
			if(room>size)
			{
				p->pred = trailer.pred;
				trailer.pred = p;
				size++;
			}
		}
		int pop()//����ջ��Ԫ�� 
		{
			int tmp = trailer.pred->data;
			trailer.pred->pred->succ = trailer.pred;
			trailer.pred=trailer.pred->pred;
			delete trailer.pred->succ;
			trailer.pred->succ = NULL;
			size--;
			return tmp;
		}
		int gettop()//����ջ��Ԫ�� 
		{
			return trailer.pred->data;
		}
		int getsize()//����ջ��Ԫ�ظ��� 
		{
			return size;
		}
		void push_back ( int m )//��ջ�����Ԫ�أ������ڳ�ʼ��Aջ�е����ݣ� 
		{
			node *p = new node ( m );
			p->pred = &header;
			header.succ->pred = p;
			header.succ = p;
			size++;
		}
		bool full()//�ж�ջ�Ƿ����� 
		{
			if ( size == room )
				return true;
			else
				return false;
		}
};
int in [ 200001 ];//������Ԫ�صı�� 
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
	int sign=1; //��¼��һ��Ӧ������Bջ��Ԫ�� 
	int action_i=0; //��¼��ǰ�Ѳ�������
	bool done = true;//�ж��Ƿ����ջ��ϴ
	while ( !A.empty() || !S.empty() )
	{
		int tmpA = A.gettop();
		int tmpS = S.gettop();
		if ( tmpA == sign ) //Aջ������sign��ֱ��pop��push��Bջ 
		{
			B.push(A.pop());
			in[action_i]=tmpA;
			action[action_i]='P';
			action_i++;
			sign++;
		}
		else if ( tmpS == sign ) //Sջ������sign��pop��push��Bջ 
		{
			B.push(S.pop());
			in[action_i]=tmpS;
			action[action_i]='O';
			action_i++;
			sign++;
		}
		else if ( tmpA != sign && tmpS != sign && !S.full() && !A.empty() ) //A���գ�A��Sջ������Ϊsign��S������pop Aջ��Ԫ�ز�push��Sջ 
		{
			S.push(A.pop());
			in[action_i]=tmpA;
			action[action_i]='I';
			action_i++;
		}
		else /*if( tmpA != sign && tmpS != sign && S.full() ) //A��Sջ��Ԫ�ؾ��������ջ������S�������no 
		{
			cout << "No" << endl;
			done = false;
			break;
		}
		else if ( A.empty() && tmpS != sign ) //A����Sջ����Ϊsign�����no */
		{
			cout << "No" << endl;
			done = false;
			break;
		}
	}
	if ( done )//���ջ��ϴ�������� 
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
