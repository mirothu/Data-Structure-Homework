#include<iostream>
#include<cstring>
using namespace std;

struct entry
{
	char* name;//记录原本的字符串 
	int num;//记录编号 
	unsigned int key;//hash值 
	int history;//第一次出现的编号 
	entry* pred;//前驱 
	entry* succ;//后继 
	entry ():name(NULL),num(0),key(0),history(0),pred(NULL),succ(NULL){
	}
	void hash(int length);//哈希函数 
};


struct list//链表 
{
	entry* header;//头节点 
	entry* trailer;//尾节点 
	int size;//链表规模 
	list():size(0)
	{
		header = new entry;
		trailer = new entry;
		header->succ = trailer;
		trailer->pred = header;
	}
	int * buildnext(char* P)//创建改进的next表 
	{
		int m = strlen(P),j=0;
		int *N = new int[m];
		int t = N[0] = -1;
		while ( j < m - 1 )
		{
			if ( 0>t||P[j]==P[t])
			{
				j++;
				t++;
				if ( P[j]!=P[t] )
					N[j]=t;
				else
					N[j]=N[t];
			}
			else
				t = N[t];
		}
		return N;
	}
	bool KMP(char* P ,char* T)//KMP函数，P为模式串，返回是否匹配 
	{
		int tmp = strlen(T);
		char * Tn = new char [2*tmp];//首先拷贝T
		for ( int i = 0 ; i < tmp ;i++ )
		{
			Tn[i]=T[i];
		}
		for ( int i = tmp ; i < 2*tmp ;i++ )//使Pn为两个相同的P拼接起来的字符串 
		{
			Tn[i]=T[i-tmp];
		}
		int * next = buildnext(P);//建立next表 
		int n = strlen(Tn) , i = 0 ;
		int m = strlen(P) , j = 0 ;
		while ( j < m && i < n )//进行KMP算法核心操作，不断比对 
		{
			if ( 0 > j || Tn [i] == P [j] )
			{
				i++;
				j++;
			}
			else
				j = next[j];
		}
		delete []next;
		if ( i - j < m )//若i-j<m,即比对成功的初始位置下标小于m，也即成功比对 
			return true;
		else 
			return false;
	}
	
	void add(entry* e)//将节点加入链表中 
	{
		e->succ = trailer;
		e->pred = trailer->pred;
		trailer->pred->succ = e;
		trailer->pred = e;
	}
	void search ( entry *e)//查找是否有循环左移的字符串 
	{
		entry* tmp = header->succ;//从第一个节点开始遍历 
		while ( tmp->succ!= NULL)//到tmp指向尾节点为止 
		{
			if (KMP(tmp->name,e->name))//若比对成功则记录第一次成功的串的编号并结束循环 
			{
				e->history = tmp->num;
				break;
			}
			else//否则继续查找 
			{
				tmp = tmp->succ;
			}
		}
		if ( tmp->succ==NULL)//若tmp指向了尾节点意味着之前的链表中没有该字符串 
		{
			e->history=0;//记为0即可 
		}
	}
};

list lst[10000];

void entry::hash(int length)//哈希函数 
{
	for ( int i = 0 ; i < length ; i++ )
	{
		char tmp_name_i = name[i];
		key = key  + (int)tmp_name_i;//将字符串的各字符ASCii码相加 
	}
	key = key % 10000;//并模10000得到关键码 
	lst[key].search(this);//在有相同关键码的链表中查找是否有循环左移的字符串 
	lst[key].add(this);//将其加入链表中 
}

int main()
{
	int m = 0 , n = 0 ;
	scanf("%d",&n);
	scanf("%d",&m);
	entry* ent = new entry[m];
	for ( int i = 0 ; i < m ; i++ )
	{
		ent[i].name =new char [n+1];
		scanf("%s",ent[i].name);
		ent[i].num = i+1;	 
		ent[i].hash(n);
		cout << ent[i].history << endl; //输出编号 
	}
	return 0;
}
