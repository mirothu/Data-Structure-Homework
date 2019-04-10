#include<iostream>
#include<cstring>
using namespace std;

struct bridge
{
	long long P;//��С����ֵ��
	long long V;//��С�����ȣ�
	bool flag;
	bridge():P(0),V(0),flag(false){
	}
	bridge(int a, int b):P(a),V(b),flag(false){
	}
};

struct material
{
	long long H;//���� 
	long long D;//���������� 
	bool flag;
	material():H(0),D(0),flag(false){
	}
	material(int a, int b):H(a),D(b),flag(false){
	}
};

bool cmp(material A, material B)//�����ϵıȽϺ��� 
{
	if ( A.H < B.H || (A.H==B.H && A.D < B.D))//����A�ļ۸����B�����ߵȼ���A�������Ƚϵ��򷵻�true 
		return true;
	else//����false 
		return false;
}

bool cmp(bridge A,bridge B)//���ŵıȽϺ��� 
{
	if ( A.V > B.V || ( A.V== B.V && A.P > B.P ))//��A�������ȸ���B����������ͬ��A�۸�ϸ��򷵻�true 
		return true;
	else
		return false;
}

void quicksort ( material pt[] , int low , int high )//����  �ο�http://www.cnblogs.com/asiacao/archive/2012/12/17/2822090.html
{
	if ( low>=high )//�������ֻ��һ�������Ԫ�ؽ����ݹ� 
		return;
	material standard (pt[low].H,pt[low].D);//ѡ���һ����Ϊ��׼ 
	int i = low;
	for ( int j = low + 1 ; j <= high ; j++ )
	{
		if ( cmp ( pt[j] , standard ))//�Ƚϵ�j�������׼�� 
		{
			i++;
			if ( i != j )
			{
				//������i�͵�j���� 
				material tmp1 (pt[i].H,pt[i].D);
				pt[i].H=pt[j].H;
				pt[i].D=pt[j].D;
				pt[j].H=tmp1.H;
				pt[j].D=tmp1.D;
			}
		}
	}
				material tmp1 (pt[i].H,pt[i].D);
				pt[i].H=pt[low].H;
				pt[i].D=pt[low].D;
				pt[low].H=tmp1.H;
				pt[low].D=tmp1.D;//������׼�����i���� 
	quicksort(pt,low,i-1);//�ݹ� 
	quicksort(pt,i+1,high);//�ݹ� 
}

void quicksort ( bridge pt[] , int low , int high )//����  �ο�http://www.cnblogs.com/asiacao/archive/2012/12/17/2822090.html
{
	if ( low>=high )//�������ֻ��һ�������Ԫ�ؽ����ݹ� 
		return;
	bridge standard (pt[low].P,pt[low].V);//ѡ���һ����Ϊ��׼ 
	int i = low;
	for ( int j = low + 1 ; j <= high ; j++ )
	{
		if ( cmp ( pt[j] , standard ))//�Ƚϵ�j�������׼�� 
		{
			i++;
			if ( i != j )
			{
				//������i�͵�j���� 
				bridge tmp1 (pt[i].P,pt[i].V);
				pt[i].P=pt[j].P;
				pt[i].V=pt[j].V;
				pt[j].P=tmp1.P;
				pt[j].V=tmp1.V;
			}
		}
	}
				bridge tmp1 (pt[i].P,pt[i].V);
				pt[i].P=pt[low].P;
				pt[i].V=pt[low].V;
				pt[low].P=tmp1.P;
				pt[low].V=tmp1.V;//������׼�����i���� 
	quicksort(pt,low,i-1);//�ݹ� 
	quicksort(pt,i+1,high);//�ݹ� 
}

int main()
{
	int n = 0 , m = 0 ;
	long long min_cost = 0 ;
	scanf("%d",&n);
	scanf("%d",&m);
	bridge* Bri=new bridge[n];
	material* Mat=new material[m];
	
	bool* bri_flag = new bool [n];
	bool* mat_flag = new bool [m];
	for ( int i = 0 ; i < n ; i++ )//�����ŵ����� 
	{
		scanf("%d",&Bri[i].P);
		scanf("%d",&Bri[i].V);
		bri_flag[i]=false;
	}

	for ( int j = 0 ; j < m ; j++ )//��ȡ���ϵ����� 
	{
		scanf("%d",&Mat[j].H);
		scanf("%d",&Mat[j].D);
		mat_flag[j] = false;
	}
	quicksort(Bri,0,n-1);//���Ű��������ȴӸߵ������򣨵ڶ��ؼ���Ϊ�۸�Ӹߵ��ͣ� 
	quicksort(Mat,0,m-1);//�����ϰ��ռ۸�ӵ͵������򣨵ڶ��ؼ���Ϊ�����ȴӵ͵��ߣ� 
	int count = 0;
	
	for ( int i = 0 ; i < n ; i++ )//��ÿ���� 
	{
		for ( int j= 0 ; j < m ; j++ )//����ÿ�ֲ��� 
		{
			if ( mat_flag[j]==false && Mat[j].H >= Bri[i].P && Mat[j].D >= Bri[i].V )//������������������֮ 
			{
				long long tmp = Mat[j].H;
				min_cost +=tmp;//���»��� 
				mat_flag[j]=true;
				break;//����ѭ�� 
			}
		}
	}
	cout << min_cost << endl; 
	return 0;
}
