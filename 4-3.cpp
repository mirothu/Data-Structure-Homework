#include<iostream>
#include<cstring>
using namespace std;

struct entry
{
	char* name;//��¼ԭ�����ַ��� 
	int num;//��¼��� 
	unsigned int key;//hashֵ 
	int history;//��һ�γ��ֵı�� 
	entry* pred;//ǰ�� 
	entry* succ;//��� 
	entry ():name(NULL),num(0),key(0),history(0),pred(NULL),succ(NULL){
	}
	void hash(int length);//��ϣ���� 
};


struct list//���� 
{
	entry* header;//ͷ�ڵ� 
	entry* trailer;//β�ڵ� 
	int size;//�����ģ 
	list():size(0)
	{
		header = new entry;
		trailer = new entry;
		header->succ = trailer;
		trailer->pred = header;
	}
	int * buildnext(char* P)//�����Ľ���next�� 
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
	bool KMP(char* P ,char* T)//KMP������PΪģʽ���������Ƿ�ƥ�� 
	{
		int tmp = strlen(T);
		char * Tn = new char [2*tmp];//���ȿ���T
		for ( int i = 0 ; i < tmp ;i++ )
		{
			Tn[i]=T[i];
		}
		for ( int i = tmp ; i < 2*tmp ;i++ )//ʹPnΪ������ͬ��Pƴ���������ַ��� 
		{
			Tn[i]=T[i-tmp];
		}
		int * next = buildnext(P);//����next�� 
		int n = strlen(Tn) , i = 0 ;
		int m = strlen(P) , j = 0 ;
		while ( j < m && i < n )//����KMP�㷨���Ĳ��������ϱȶ� 
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
		if ( i - j < m )//��i-j<m,���ȶԳɹ��ĳ�ʼλ���±�С��m��Ҳ���ɹ��ȶ� 
			return true;
		else 
			return false;
	}
	
	void add(entry* e)//���ڵ���������� 
	{
		e->succ = trailer;
		e->pred = trailer->pred;
		trailer->pred->succ = e;
		trailer->pred = e;
	}
	void search ( entry *e)//�����Ƿ���ѭ�����Ƶ��ַ��� 
	{
		entry* tmp = header->succ;//�ӵ�һ���ڵ㿪ʼ���� 
		while ( tmp->succ!= NULL)//��tmpָ��β�ڵ�Ϊֹ 
		{
			if (KMP(tmp->name,e->name))//���ȶԳɹ����¼��һ�γɹ��Ĵ��ı�Ų�����ѭ�� 
			{
				e->history = tmp->num;
				break;
			}
			else//����������� 
			{
				tmp = tmp->succ;
			}
		}
		if ( tmp->succ==NULL)//��tmpָ����β�ڵ���ζ��֮ǰ��������û�и��ַ��� 
		{
			e->history=0;//��Ϊ0���� 
		}
	}
};

list lst[10000];

void entry::hash(int length)//��ϣ���� 
{
	for ( int i = 0 ; i < length ; i++ )
	{
		char tmp_name_i = name[i];
		key = key  + (int)tmp_name_i;//���ַ����ĸ��ַ�ASCii����� 
	}
	key = key % 10000;//��ģ10000�õ��ؼ��� 
	lst[key].search(this);//������ͬ�ؼ���������в����Ƿ���ѭ�����Ƶ��ַ��� 
	lst[key].add(this);//������������� 
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
		cout << ent[i].history << endl; //������ 
	}
	return 0;
}
